#pragma once

#include "field.hpp"
#include "rp2040/registers/access_modifiers.hpp"
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
 * @tparam BaseAddress
 * @tparam Offset
 * @tparam Fields
 */
template<hw_register_address_t BaseAddress, hw_register_address_t Offset, typename... Fields>
    requires(is_field<Fields> && ...)
class hw_register
{
protected:
    using access_modifier_t = access_modifiers::add<typename Fields::access_modifier_t...>::type;

    static constexpr hw_register_address_t          BASE_ADDRESS = BaseAddress;
    static constexpr hw_register_address_t          OFFSET       = Offset;
    static volatile constexpr hw_register_address_t POINTER      = BASE_ADDRESS + OFFSET;

    static auto reference() [[always_inline]] -> auto&
    {
        return *reinterpret_cast<hw_register_ptr_t>(POINTER);  // NOLINT
    }

    static auto const_reference() [[always_inline]] -> const auto&
    {
        return *reinterpret_cast<hw_register_ptr_t>(POINTER);  // NOLINT
    }

public:
    hw_register()                                      = delete;
    hw_register(hw_register&&)                         = delete;
    hw_register(const hw_register&)                    = delete;
    auto operator=(hw_register&&) -> hw_register&      = delete;
    auto operator=(const hw_register&) -> hw_register& = delete;
    ~hw_register()                                     = delete;

    [[nodiscard]] static auto get() -> hw_register_value_t
    {
        static_assert(access_modifiers::is_readable<access_modifier_t>, "Register is not readable.");

        return const_reference();
    }

    /**
     * @brief Get the value of the given field.
     *
     * @tparam Field
     * @return Field::value_t
     */
    template<typename Field>
        requires field_exists<Field, Fields...> && is_field_readable<Field>
    [[nodiscard]] static auto get_field() [[always_inline]] -> Field::value_t
    {
        return static_cast<Field::value_t>((get() & Field::get_bitmask()) >> Field::START_BIT);
    }

    static auto set(const hw_register_value_t value) [[always_inline]]
    {
        static_assert(access_modifiers::is_writable<access_modifier_t>, "Register is not writable.");

        reference() = value;
    }

    static auto clear() [[always_inline]]
    {
        static_assert(access_modifiers::is_writable<access_modifier_t>, "Register is not writable.");

        set(0U);
    }

    template<typename Field>
        requires field_exists<Field, Fields...> && is_field_writable<Field>
    static auto set_field(const Field::value_t value) [[always_inline]]
    {
        clear_field<Field>();
        set(((static_cast<hw_register_value_t>(value) << Field::START_BIT) & Field::get_bitmask()) | get());
    }

    template<typename... FieldsToSet>
        requires(field_exists<FieldsToSet, Fields...> && ...) && (is_field_writable<FieldsToSet> && ...) &&
                pi_pico_bare_metal::utility::are_types_not_repeating<FieldsToSet...>
    static auto set_fields(const typename FieldsToSet::value_t... values) [[always_inline]]
    {
        /* Clear fields. */
        set(~((FieldsToSet::get_bitmask()) | ...) & get());
        /* Set fields. */
        set((
            ((static_cast<hw_register_value_t>(values) << FieldsToSet::START_BIT) & FieldsToSet::get_bitmask()) | ...));
    }

    template<typename... FieldsToSet>
        requires(field_exists<FieldsToSet, Fields...> && ...) && (is_field_writable<FieldsToSet> && ...) &&
                pi_pico_bare_metal::utility::are_types_not_repeating<FieldsToSet...>
    static auto set_fields_overwrite(const typename FieldsToSet::value_t... values) [[always_inline]]
    {
        set((
            ((static_cast<hw_register_value_t>(values) << FieldsToSet::START_BIT) & FieldsToSet::get_bitmask()) | ...));
    }

    template<typename Field>
        requires field_exists<Field, Fields...> && is_field_writable<Field>
    static auto clear_field() [[always_inline]]
    {
        set(~Field::get_bitmask() & get());
    }
};

}  // namespace rp2040::registers
