#pragma once

#include <bit>

#include "rp2040/registers/access_modifiers.hpp"
#include "rp2040/registers/field.hpp"
#include "rp2040/registers/types.hpp"
#include "utility/concepts.hpp"

namespace rp2040::registers
{

/**
 * @brief Represents a compile-time hardware register.
 *
 * @details Every register has a base address, offset from that base address, and zero or more fields (see \b
 * rp2040::registers::hw_register_field ). The access modifier of the register is inferred from the access modifiers of
 * the fields (see \b rp2040::registers::access_modifiers::add ).
 *
 * @tparam BaseAddress Base address of the register.
 * @tparam Offset Register offset from the base address.
 * @tparam AccessModifier Access modifier for this register.
 */
template<
    hw_register_address_t BaseAddress,
    hw_register_address_t Offset,
    typename AccessModifier,
    uint64_t PassKey = 0ULL>
    requires access_modifiers::is_access_modifier<AccessModifier>
class hw_register
{
private:
    static constexpr uint64_t PASS_KEY = 0xE27CAA8E98BBCF14ULL;
    static_assert(PassKey == PASS_KEY, "Do not use the 'hw_register' class directly!");

    static constexpr hw_register_address_t REGISTER_ADDRESS = BaseAddress + Offset;

protected:
    static constexpr auto IS_READABLE = access_modifiers::is_readable<AccessModifier>;
    static constexpr auto IS_WRITABLE = access_modifiers::is_writable<AccessModifier>;

    /* Defining a static register pointer here saves some instructions
     * compared to keeping the bit_cast inside the reference/const reference functions.
     */
    static hw_register_ptr_t REGISTER_POINTER;

    [[nodiscard]] static auto reference() -> auto&
    {
        return *REGISTER_POINTER;
    }

    [[nodiscard]] static auto const_reference() -> const auto&
    {
        return *REGISTER_POINTER;
    }

public:
    hw_register()                                      = delete;
    hw_register(hw_register&&)                         = delete;
    hw_register(const hw_register&)                    = delete;
    auto operator=(hw_register&&) -> hw_register&      = delete;
    auto operator=(const hw_register&) -> hw_register& = delete;
    ~hw_register()                                     = delete;

    [[nodiscard]] static auto get() -> hw_register_value_t
        requires IS_READABLE
    {
        return const_reference();
    }

    static auto set(const hw_register_value_t value)
        requires IS_WRITABLE
    {
        reference() = value;
    }

    static auto clear()
        requires IS_WRITABLE
    {
        set(0U);
    }

    template<typename... FieldsToSet>
        requires(is_field<FieldsToSet> && ...) &&
                pi_pico_bare_metal::utility::are_types_not_repeating<FieldsToSet...> &&
                (field_belongs_to_register<FieldsToSet, hw_register<BaseAddress, Offset, AccessModifier, PassKey>> &&
                 ...) &&
                (FieldsToSet::IS_WRITABLE && ...)
    static auto set_fields(const typename FieldsToSet::value... values)
    {
        const auto cleared_fields = ~((FieldsToSet::get_bitmask()) | ...) & get();
        set((((static_cast<hw_register_value_t>(values) << FieldsToSet::START_BIT) & FieldsToSet::get_bitmask()) |
             ...) |
            cleared_fields);
    }

    template<typename... FieldsToSet>
        requires(is_field<FieldsToSet> && ...) &&
                pi_pico_bare_metal::utility::are_types_not_repeating<FieldsToSet...> &&
                (field_belongs_to_register<FieldsToSet, hw_register<BaseAddress, Offset, AccessModifier, PassKey>> &&
                 ...) &&
                (FieldsToSet::IS_WRITABLE && ...)
    static auto set_fields_overwrite(const typename FieldsToSet::value... values)
    {
        set((
            ((static_cast<hw_register_value_t>(values) << FieldsToSet::START_BIT) & FieldsToSet::get_bitmask()) | ...));
    }
};

template<hw_register_address_t BaseAddress, hw_register_address_t Offset, typename AccessModifier, uint64_t PassKey>
    requires access_modifiers::is_access_modifier<AccessModifier>
hw_register_ptr_t hw_register<BaseAddress, Offset, AccessModifier, PassKey>::REGISTER_POINTER =
    std::bit_cast<hw_register_ptr_t>(hw_register<BaseAddress, Offset, AccessModifier, PassKey>::REGISTER_ADDRESS);

}  // namespace rp2040::registers
