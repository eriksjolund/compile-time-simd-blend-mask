#ifndef CONVERT_TUPLEMASK_TO_MM256I_H
#define CONVERT_TUPLEMASK_TO_MM256I_H

#include <immintrin.h>
#include <boost/hana.hpp>

namespace hana = boost::hana;

constexpr decltype(auto) convert_tuplemask_to_mm256i = [](auto tuple) {
  BOOST_HANA_CONSTANT_CHECK(hana::length(tuple) == hana::size_c<32>);
  auto elem_num = [tuple](auto i) {
    // It's not clear to me about what numbers to choose.
    // Anyway the numbers 127 and -127 work. /Erik Sjolund
    if (hana::at(tuple, i)) {
      return 127;
    } else {
      return -127;
    };
  };
  return hana::unpack(
      hana::make_range(hana::size_c<0>, hana::size_c<32>),
      [elem_num](auto... i) { return _mm256_setr_epi8(elem_num(i)...); });
};

#endif  // CONVERT_TUPLEMASK_TO_MM256I_H
