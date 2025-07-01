#pragma once

#include "rp2040/registers/access_modifiers.hpp"
#include "rp2040/registers/base_addresses.hpp"
#include "rp2040/registers/register.hpp"

// TODO: generate full register list using cmsis-svd-parser & jinja2

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

namespace rp2040::registers
{

namespace xip
{

/* Cache control */
class ctrl : public hw_register<base_addresses::XIP, 0x00U, access_modifiers::read_write, 0xE27CAA8E98BBCF14ULL>
{
private:
public:
    /**
     * When 1, the cache memories are powered down. They retain state,
     * but can not be accessed. This reduces static power dissipation.
     * Writing 1 to this bit forces CTRL_EN to 0, i.e. the cache cannot
     * be enabled when powered down.
     * Cache-as-SRAM accesses will produce a bus error response when
     * the cache is powered down.
     */
    using power_down = hw_register_field<ctrl, bool, 3, 1, access_modifiers::read_write, 0x5C9BBF8A4E16A95DULL>;
    /**
     * When 1, writes to any alias other than 0x0 (caching, allocating) will produce a bus fault.
     * When 0, these writes are silently ignored.
     * In either case, writes to the 0x0 alias will deallocate on tag match, as usual.
     */
    using err_badwrite = hw_register_field<ctrl, bool, 1, 1, access_modifiers::write_only, 0x5C9BBF8A4E16A95DULL>;
    /**
     * When 1, enable the cache. When the cache is disabled, all XIP accesses
     * will go straight to the flash, without querying the cache.
     * When enabled, cacheable XIP accesses will query the cache, and the flash will
     * not be accessed if the tag matches and the valid bit is set.
     * If the cache is enabled, cache-as-SRAM accesses have no effect on the
     * cache data RAM, and will produce a bus error response.
     */
    using en = hw_register_field<ctrl, bool, 0, 1, access_modifiers::read_only, 0x5C9BBF8A4E16A95DULL>;
};

}  // namespace xip

namespace test
{

/* Cache control */
class test_reg : public hw_register<base_addresses::XIP, 0x04U, access_modifiers::read_write, 0xE27CAA8E98BBCF14ULL>
{
private:
    enum class test_field_value_t
    {
        this_is_a_value,
        another_value
    };

public:
    /**
     * When 1, the cache memories are powered down. They retain state,
     * but can not be accessed. This reduces static power dissipation.
     * Writing 1 to this bit forces CTRL_EN to 0, i.e. the cache cannot
     * be enabled when powered down.
     * Cache-as-SRAM accesses will produce a bus error response when
     * the cache is powered down.
     */
    using test_field =
        hw_register_field<test_reg, test_field_value_t, 3, 8, access_modifiers::read_write, 0x5C9BBF8A4E16A95DULL>;
};

}  // namespace test

}  // namespace rp2040::registers

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
