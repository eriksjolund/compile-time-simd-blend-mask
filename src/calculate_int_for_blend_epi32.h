#ifndef CALCULATE_BLEND_INTEGER_MASK_H
#define CALCULATE_BLEND_INTEGER_MASK_H

#include <boost/hana.hpp>

namespace hana = boost::hana;
using namespace hana::literals;

// Could be used for
//
// _mm256_blend_epi16()
// _mm256_blend_epi32()

constexpr decltype(auto) calculate_blend_integer_mask = [](auto tuple) {
  auto power2_bit = [tuple](auto i) {
    if (hana::at(tuple, i)) {
      return (1 << decltype(i)::value);
    } else {
      return 0;
    };
  };
  return hana::unpack(
      hana::make_range(hana::size_c<0>, hana::size_c<7>),
      [power2_bit](auto... i) { return (power2_bit(i) | ...); });
};

static_assert(calculate_blend_integer_mask(hana::make_tuple(hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c)) ==
              0);

static_assert(calculate_blend_integer_mask(hana::make_tuple(hana::true_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c)) ==
              1);

static_assert(calculate_blend_integer_mask(hana::make_tuple(hana::true_c,
                                                            hana::false_c,
                                                            hana::true_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c,
                                                            hana::false_c)) ==
              5);

#endif  // CALCULATE_BLEND_INTEGER_MASK_H
