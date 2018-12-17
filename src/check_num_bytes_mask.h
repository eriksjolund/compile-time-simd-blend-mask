#ifndef CHECK_NUM_BYTES_MASK_H
#define CHECK_NUM_BYTES_MASK_H

#include <boost/hana.hpp>
#include "to_tuple_partition_combinebytes.h"

namespace hana = boost::hana;
using namespace hana::literals;

BOOST_HANA_CONSTEXPR_LAMBDA auto allsame = [](auto a) {
  return hana::all(a) or hana::none(a);
};

template <std::size_t num, typename Tuple>
constexpr auto check_num_bytes_mask(Tuple&& tuple) {
  auto divided =
      to_tuple_partition_combinebytes<4, Tuple>(std::forward<Tuple>(tuple));
  return hana::all_of(divided, allsame);
}

template <std::size_t num, typename Tuple>
constexpr auto check_num_bytes_mask2(Tuple&& tuple) {
  auto divided =
      to_tuple_partition_combinebytes<2, Tuple>(std::forward<Tuple>(tuple));
  return hana::all_of(divided, allsame);
}

BOOST_HANA_CONSTANT_CHECK(
    check_num_bytes_mask<4>(hana::make_tuple(hana::true_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::true_c)) == hana::true_c);

BOOST_HANA_CONSTANT_CHECK(
    check_num_bytes_mask<4>(hana::make_tuple(hana::false_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::false_c)) == hana::true_c);

BOOST_HANA_CONSTANT_CHECK(
    check_num_bytes_mask<4>(hana::make_tuple(hana::false_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::true_c)) == hana::true_c);

BOOST_HANA_CONSTANT_CHECK(
    check_num_bytes_mask<4>(hana::make_tuple(hana::false_c,
                                             hana::false_c,
                                             hana::true_c,
                                             hana::true_c,
                                             hana::false_c,
                                             hana::false_c,
                                             hana::true_c,
                                             hana::true_c)) == hana::false_c);

#endif  // CHECK_NUM_BYTES_MASK_H
