#ifndef VERIFY_BLEND_RESULT_H
#define VERIFY_BLEND_RESULT_H

#include <stdexcept>
#include <sstream>

#include <immintrin.h>
#include <boost/hana.hpp>

namespace hana = boost::hana;

constexpr decltype(auto) verify_blend_result = [](__m256i blend_res,
                                                  __m256i a,
                                                  __m256i b,
                                                  auto mask) {
  BOOST_HANA_CONSTANT_CHECK(hana::length(mask) == hana::size_c<32>);
  auto checkelement = [mask, blend_res, a, b](auto i) {
    auto correct_answer = hana::equal(hana::at(mask, i), hana::true_c)
                              ? _mm256_extract_epi8(b, decltype(i)::value)
                              : _mm256_extract_epi8(a, decltype(i)::value);

    auto blend_res_answer = _mm256_extract_epi8(blend_res, decltype(i)::value);

    if (correct_answer != blend_res_answer) {
      std::stringstream stream;
      stream << "blend256() gives the wrong result at pos " << decltype(i)::value
             << " hana::equal(hana::at(mask, i), hana::true_c)  = "
             << hana::equal(hana::at(mask, i), hana::true_c)
             << "  correct answer = " << correct_answer
             << "  blend_res_answer = " << blend_res_answer
             << " : programming error";

      throw std::runtime_error(stream.str());
    }
    return;
  };
  return hana::unpack(hana::make_range(hana::size_c<0>, hana::size_c<32>),
                      [checkelement](auto... i) { (checkelement(i), ...); });
};

#endif  // VERIFY_BLEND_RESULT_H
