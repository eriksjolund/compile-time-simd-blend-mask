#ifndef BLEND256_H
#define BLEND256_H

#include <immintrin.h>
#include <boost/hana.hpp>

#include "calculate_int_for_blend_epi32.h"
#include "check_num_bytes_mask.h"
#include "convert_tuplemask_to_mm256i.h"
#include "tuplemask_for_bigger_integers.h"
#include "verify_blend_result.h"

namespace hana = boost::hana;
using namespace hana::literals;

constexpr decltype(
    auto) blend256 = [](__m256i a, __m256i b, auto tuplemask_8bit) {
  BOOST_HANA_CONSTANT_CHECK(hana::length(tuplemask_8bit) == hana::size_c<32>);
  if constexpr (hana::equal(check_num_bytes_mask<4>(tuplemask_8bit),
                            hana::true_c)) {
    // For the case
    //
    // intrinsics: __m256i _mm256_blend_epi32(__m256i a, __m256i b, const int
    // imm8) assembly instuction : vpblendd

    constexpr auto tuplemask_32bit =
        tuplemask_for_bigger_integers<4>(tuplemask_8bit);
    constexpr auto mask_num = calculate_blend_integer_mask(tuplemask_32bit);
    return _mm256_blend_epi32(a, b, mask_num);
  } else if constexpr (hana::equal(check_num_bytes_mask2<2>(tuplemask_8bit),
                                   hana::true_c) &&
                       hana::equal(hana::slice_c<0, 16>(tuplemask_8bit),
                                   hana::slice_c<16, 32>(tuplemask_8bit))) {
    // For the case
    //
    // intrinsics: __m256i _mm256_blend_epi16(__m256i a, __m256i b, const int
    // imm8) assembly instuction : vpblendw

    constexpr auto tuplemask_16bit =
        tuplemask_for_bigger_integers<2>(tuplemask_8bit);
    constexpr auto mask_int = calculate_blend_integer_mask(tuplemask_16bit);
    return _mm256_blend_epi16(a, b, mask_int);
  } else {
    // For the case
    //
    // intrinsics: __m256i _mm256_blendv_epi8(__m256i v1, __m256i v2, __m256i
    // mask) assembly instuction : vpblendvb

    // This could be improved.
    // If blend256() is used multiple times with the same mask we would only
    // want convert_tuplemask_to_mm256i() to be run one time. How could this be
    // achieved? Maybe a hana::mask could be used?
    return _mm256_blendv_epi8(b, a,
                              convert_tuplemask_to_mm256i(tuplemask_8bit));
  }
};

#endif  // BLEND256_H
