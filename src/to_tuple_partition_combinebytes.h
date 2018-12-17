#ifndef TO_TUPLE_PARTITION_COMBINEBYTES_H
#define TO_TUPLE_PARTITION_COMBINEBYTES_H

#include <boost/hana.hpp>

namespace hana = boost::hana;
using namespace hana::literals;

namespace detail {
template <std::size_t num, typename Tuple, std::size_t... Is>
constexpr auto to_tuple_partition_combinebytes(Tuple&& tuple,
                                               std::index_sequence<Is...>) {
  return hana::make_tuple(
      hana::slice_c<Is * num, (Is + 1) * num>(std::forward<Tuple>(tuple))...);
}
}  // namespace detail

template <std::size_t num, typename Tuple>
constexpr auto to_tuple_partition_combinebytes(Tuple&& tuple) {
  return detail::to_tuple_partition_combinebytes<num>(
      std::forward<Tuple>(tuple),
      std::make_index_sequence<decltype(hana::length(tuple))::value / num>());
}

BOOST_HANA_CONSTANT_CHECK(
    to_tuple_partition_combinebytes<4>(hana::make_tuple(hana::true_c,
                                                        hana::true_c,
                                                        hana::false_c,
                                                        hana::false_c,
                                                        hana::true_c,
                                                        hana::true_c,
                                                        hana::true_c,
                                                        hana::true_c)) ==
    hana::make_tuple(hana::make_tuple(hana::true_c,
                                      hana::true_c,
                                      hana::false_c,
                                      hana::false_c),
                     hana::make_tuple(hana::true_c,
                                      hana::true_c,
                                      hana::true_c,
                                      hana::true_c)));

#endif
