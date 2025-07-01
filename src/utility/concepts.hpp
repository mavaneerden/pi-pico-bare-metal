#pragma once

#include <type_traits>

namespace pi_pico_bare_metal::utility
{

template<typename T0, typename... Ts>
constexpr std::size_t type_count_in_list_v = (std::is_same_v<T0, Ts> + ...);

template<typename... Ts>
concept are_types_not_repeating = sizeof...(Ts) == (type_count_in_list_v<Ts, Ts...> + ...);

}  // namespace pi_pico_bare_metal::utility
