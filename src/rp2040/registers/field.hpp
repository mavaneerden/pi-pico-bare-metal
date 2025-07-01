#pragma once

#include <concepts>
#include <cstdint>
#include <type_traits>

#include "rp2040/registers/access_modifiers.hpp"
#include "rp2040/registers/types.hpp"

namespace rp2040::registers
{

/**
 * @brief Struct for a specific field inside a register.
 *
 * @tparam ValueType        Type of the value of the field, can be an integral or enum type (std::semiregular).
 * @tparam StartBit         Start bit of the field inside the register.
 * @tparam LengthInBits     Length of the field in bits.
 */
template<
    typename Register,
    std::semiregular      ValueType,
    hw_register_address_t StartBit,
    hw_register_address_t LengthInBits,
    typename AccessModifierField,
    uint64_t PassKeyField = 0ULL>
    requires access_modifiers::is_access_modifier<AccessModifierField>
class hw_register_field
{
    template<hw_register_address_t BaseAddress, hw_register_address_t Offset, typename AccessModifier, uint64_t PassKey>
        requires access_modifiers::is_access_modifier<AccessModifier>
    friend class hw_register;

public:
    hw_register_field()                                            = delete;
    hw_register_field(hw_register_field&&)                         = delete;
    hw_register_field(const hw_register_field&)                    = delete;
    auto operator=(hw_register_field&&) -> hw_register_field&      = delete;
    auto operator=(const hw_register_field&) -> hw_register_field& = delete;
    ~hw_register_field()                                           = delete;

    /* Use decay_t here, it removes any references & const/volatile specifiers.
     * This MUST be public, otherwise gcc will fail to compile.
     * It thinks it cannot use a private type in a function parameter in a friend class.
     * Clang and MSVC compile it fine, so it must be a bug in gcc (or gcc is the only one doing it right).
     */
    using value = std::decay_t<ValueType>;

private:
    static constexpr uint64_t PASS_KEY = 0x5C9BBF8A4E16A95DULL;
    static_assert(PassKeyField == PASS_KEY, "Do not use the 'hw_register_field' class directly!");

    using register_t = Register;

    static constexpr auto START_BIT      = StartBit;
    static constexpr auto LENGTH_IN_BITS = LengthInBits;

    static constexpr auto IS_READABLE = access_modifiers::is_readable<AccessModifierField>;
    static constexpr auto IS_WRITABLE = access_modifiers::is_writable<AccessModifierField>;

    /**
     * @brief Get the bitmask of the register field.
     *
     * @return hw_register_value_t Register field bitmask.
     */
    static consteval auto get_bitmask() -> hw_register_value_t
    {
        static constexpr hw_register_value_t BITS     = ~0U;
        static constexpr auto                NUM_BITS = sizeof(hw_register_value_t) * 8U;
        /**
         * Right shift is done to get the correct \em number of bits required for the mask.
         * For example, if we want the mask 00111000, the right shift would be 8 - 3 = 5:
         * 11111111 >> 5 = 00000111
         */
        static constexpr hw_register_value_t RIGHT_SHIFT = NUM_BITS - LENGTH_IN_BITS;
        /**
         * Left shift is done to put the number of bits acquired from the right shift in the correct \em position.
         * For example, if we want the mask 00111000, left shift would be 3:
         * 11111111 >> 5 = 00000111;
         * 00000111 << 3 = 00111000
         */
        static constexpr hw_register_value_t LEFT_SHIFT = START_BIT;

        return (BITS >> RIGHT_SHIFT) << LEFT_SHIFT;
    }

public:
    [[nodiscard]] static auto get() -> value
        requires IS_READABLE
    {
        return static_cast<value>((Register::get() & get_bitmask()) >> START_BIT);
    }

    static auto set(const value value)
        requires IS_WRITABLE
    {
        const auto cleared_field = ~get_bitmask() & Register::get();
        Register::set(((static_cast<hw_register_value_t>(value) << START_BIT) & get_bitmask()) | cleared_field);
    }

    static auto clear()
        requires IS_WRITABLE
    {
        Register::set(~get_bitmask() & Register::get());
    }
};

/* This struct is used for the is_field concept. */
template<typename T>
struct is_hw_register_field : std::false_type
{};

/* This struct is used for the is_field concept. */
template<
    typename Register,
    std::semiregular      ValueType,
    hw_register_address_t StartBit,
    hw_register_address_t LengthInBits,
    typename AccessModifier,
    uint64_t PassKey>
struct is_hw_register_field<hw_register_field<Register, ValueType, StartBit, LengthInBits, AccessModifier, PassKey>> :
    std::true_type
{};

/**
 * @brief Concept for checking if a type is a field type or not.
 *
 * @tparam FieldCandidate Potential field type.
 */
template<typename FieldCandidate>
concept is_field = is_hw_register_field<FieldCandidate>::value;

template<typename Field, typename Register>
concept field_belongs_to_register = std::derived_from<typename Field::register_t, Register>;

}  // namespace rp2040::registers
