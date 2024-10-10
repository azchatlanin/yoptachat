#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <forward_list>
#include <string_view>

#include <concepts>

// Набор концептов, используется при логировании
namespace hack::concepts
{
  template<typename T>
  concept is_map = std::same_as<T, std::map<typename T::key_type, typename T::mapped_type, typename T::key_compare, typename T::allocator_type>> ||
                   std::same_as<T, std::unordered_map<typename T::key_type, typename T::mapped_type, typename T::hasher, typename T::key_equal, typename T::allocator_type>>;

  template<typename T>
  concept is_tuple = requires (T t) { std::tuple_cat(t, std::make_tuple(1, "tuple")); };

  template<typename T>
  concept is_set = std::same_as<T, std::set<typename T::key_type, typename T::key_compare, typename T::allocator_type>>;

  template<typename T>
  concept is_unordered_set = std::same_as<T, std::unordered_set<typename T::key_type>>;

  template<typename T>
  concept is_forward_list = std::same_as<T, std::forward_list<typename T::value_type>>;

  template<typename T>
  concept is_string = std::is_convertible_v<T, std::string_view>;

  template<typename T, std::size_t N = 0>
  concept is_sequence_container = std::same_as<T, std::vector<typename T::value_type>> || std::same_as<T, std::list<typename T::value_type>> || (std::is_array_v<T> && N > 0);

  template<typename T>
  concept is_associative_container = is_map<T> || is_tuple<T> || is_set<T> || is_unordered_set<T>;


  template<typename T>
  concept not_defined = !std::enable_if_t<!(std::integral<T> || 
                                            is_sequence_container<T> || 
                                            is_map<T> || 
                                            is_tuple<T> || 
                                            is_set<T> ||
                                            is_unordered_set<T> ||
                                            is_forward_list<T> ||
                                            std::is_array<T>() ||
                                            is_string<T>), bool>() ==  true;

}
