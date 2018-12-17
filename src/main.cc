#include <immintrin.h>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <boost/hana.hpp>

#include "blend256.h"

namespace hana = boost::hana;
using namespace hana::literals;

int main() {
#ifdef mask_1100_0011_0000_0000_1100_0011_0000_0000
  // clang-format off
  auto mask = hana::make_tuple(
      hana::true_c,  hana::true_c,
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c,
      hana::true_c,  hana::true_c, 

      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 

      hana::true_c,  hana::true_c,
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::true_c,  hana::true_c,

      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c
 );
  // clang-format on
#endif

#ifdef mask_1111_0000_1111_0000_0000_0000_0000_0000
  // clang-format off
  auto mask = hana::make_tuple(
      hana::true_c,  hana::true_c,
      hana::true_c,  hana::true_c,
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 

      hana::true_c,  hana::true_c,
      hana::true_c,  hana::true_c,
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 

      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 

      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c
 );
  // clang-format on
#endif

#ifdef mask_1000_0000_0000_0000_0000_0000_0000_0000
  // clang-format off
  auto mask = hana::make_tuple(
      hana::true_c,  hana::false_c,
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 

      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 

      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 

      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c, 
      hana::false_c, hana::false_c
 );
  // clang-format on
#endif

  __m256i a = _mm256_set1_epi8(0);
  // clang-format off
  __m256i b = _mm256_setr_epi8( 1,  2,  3,  4,  5,  6,  7,  8,
                                9, 10, 11, 12, 13, 14, 15, 16,
                               17, 18, 19, 20, 21, 22, 23, 24,
                               25, 26, 27, 28, 29, 30, 31, 32);
  // clang-format on
  auto blend_result = blend256(a, b, mask);

  int return_value = EXIT_SUCCESS;
  try {
    verify_blend_result(blend_result, a, b, mask);
  } catch (const std::runtime_error& e) {
    std::cerr << "std::runtime_error = " << e.what() << std::endl;
    return_value = EXIT_FAILURE;
  } catch (...) {
    assert(false);  // Should never happen
  }
  return return_value;
}
