#pragma once

#pragma once

#include <concepts>
#include <type_traits>

#include "access_modifiers.hpp"
#include "types.hpp"

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
    std::semiregular      ValueType,
    hw_register_address_t StartBit,
    hw_register_address_t LengthInBits,
    typename AccessModifier>
    requires access_modifiers::is_access_modifier<AccessModifier>
class hw_register_field
{
public:
    /* Use decay_t here, it removes any references & const/volatile specifiers. */
    using value_t           = std::decay_t<ValueType>;
    using access_modifier_t = AccessModifier;

    static constexpr auto START_BIT      = StartBit;
    static constexpr auto LENGTH_IN_BITS = LengthInBits;

    hw_register_field()                                            = delete;
    hw_register_field(hw_register_field&&)                         = delete;
    hw_register_field(const hw_register_field&)                    = delete;
    auto operator=(hw_register_field&&) -> hw_register_field&      = delete;
    auto operator=(const hw_register_field&) -> hw_register_field& = delete;
    ~hw_register_field()                                           = delete;

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
};

/* This struct is used for the is_field concept. */
template<typename T>
struct is_hw_register_field : std::false_type
{};

/* This struct is used for the is_field concept. */
template<
    std::semiregular      ValueType,
    hw_register_address_t StartBit,
    hw_register_address_t LengthInBits,
    typename AccessModifier>
struct is_hw_register_field<hw_register_field<ValueType, StartBit, LengthInBits, AccessModifier>> : std::true_type
{};

/**
 * @brief Concept for checking if a type is a field type or not.
 *
 * @tparam FieldCandidate Potential field type.
 */
template<typename FieldCandidate>
concept is_field = is_hw_register_field<FieldCandidate>::value;

template<typename Field>
concept is_field_writable =
    is_hw_register_field<Field>::value && access_modifiers::is_writable<typename Field::access_modifier_t>;

template<typename Field>
concept is_field_readable =
    is_hw_register_field<Field>::value && access_modifiers::is_readable<typename Field::access_modifier_t>;

/**
 * @brief Concept for checking if a field exists inside a register.
 *
 * @tparam Field Field to check.
 * @tparam Fields Fields inside the register.
 */
template<typename Field, typename... Fields>
concept field_exists = (std::same_as<Field, Fields> || ...);

}  // namespace rp2040::registers
