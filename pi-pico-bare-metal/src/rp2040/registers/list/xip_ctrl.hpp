#pragma once

#include "rp2040/registers/access_modifiers.hpp"
#include "rp2040/registers/base_addresses.hpp"
#include "rp2040/registers/register.hpp"

// TODO: generate full register list using cmsis-svd-parser & jinja2

namespace rp2040::registers::xip
{

/* Cache control */
struct ctrl :
    public hw_register<
        base_addresses::XIP,
        0x00U,
        hw_register_field<bool, 3, 1, access_modifiers::read_write>,
        hw_register_field<bool, 1, 1, access_modifiers::write_only>,
        hw_register_field<bool, 0, 1, access_modifiers::read_only>>
{
    /**
     * When 1, the cache memories are powered down. They retain state,
     * but can not be accessed. This reduces static power dissipation.
     * Writing 1 to this bit forces CTRL_EN to 0, i.e. the cache cannot
     * be enabled when powered down.
     * Cache-as-SRAM accesses will produce a bus error response when
     * the cache is powered down.
     */
    using power_down = hw_register_field<bool, 3, 1, access_modifiers::read_write>;
    /**
     * When 1, writes to any alias other than 0x0 (caching, allocating) will produce a bus fault.
     * When 0, these writes are silently ignored.
     * In either case, writes to the 0x0 alias will deallocate on tag match, as usual.
     */
    using err_badwrite = hw_register_field<bool, 1, 1, access_modifiers::write_only>;
    /**
     * When 1, enable the cache. When the cache is disabled, all XIP accesses
     * will go straight to the flash, without querying the cache.
     * When enabled, cacheable XIP accesses will query the cache, and the flash will
     * not be accessed if the tag matches and the valid bit is set.
     * If the cache is enabled, cache-as-SRAM accesses have no effect on the
     * cache data RAM, and will produce a bus error response.
     */
    using en = hw_register_field<bool, 0, 1, access_modifiers::read_only>;
};

using test = hw_register_field<bool, 1, 1, access_modifiers::write_only>;

}  // namespace rp2040::registers::xip
