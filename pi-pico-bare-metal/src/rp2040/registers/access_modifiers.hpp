#pragma once

#include <type_traits>

namespace rp2040::registers::access_modifiers
{

struct read_only
{};

struct write_only
{};

struct read_write
{};

template<typename AccessModifierCandidate>
concept is_access_modifier =
    std::is_same_v<AccessModifierCandidate, read_only> || std::is_same_v<AccessModifierCandidate, write_only> ||
    std::is_same_v<AccessModifierCandidate, read_write>;

template<typename AccessModifier>
concept is_read_only = std::is_same_v<AccessModifier, read_only>;

template<typename AccessModifier>
concept is_write_only = std::is_same_v<AccessModifier, write_only>;

template<typename AccessModifier>
concept is_read_write = std::is_same_v<AccessModifier, read_write>;

template<typename AccessModifier>
concept is_readable = std::is_same_v<AccessModifier, read_only> || std::is_same_v<AccessModifier, read_write>;

template<typename AccessModifier>
concept is_writable = std::is_same_v<AccessModifier, write_only> || std::is_same_v<AccessModifier, read_write>;

template<typename... AccessModifiers>
struct add
{
    using type = std::conditional_t<
        (is_read_only<AccessModifiers> && ...),
        read_only,
        std::conditional_t<(is_write_only<AccessModifiers> && ...), write_only, read_write>>;
};

}  // namespace rp2040::registers::access_modifiers
