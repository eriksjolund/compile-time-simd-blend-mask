# compile-time-simd-blend-mask
Compile-time blend masks that unifies _mm256_blend_epi8, _mm256_blend_epi16, _mm256_blend_epi32
by using the C++ library boost::hana

## Introduction

The intrinsics functions

* __m256i _mm256_blendv_epi8(__m256i v1, __m256i v2, __m256i mask)
* __m256i _mm256_blend_epi16(__m256i a, __m256i b, const int imm8)
* __m256i _mm256_blend_epi32(__m256i a, __m256i b, const int imm8)

serve similar purpose, but they take different arguments. The first function encodes the blend mask in the SIMD vector __256i, 
but the two latter encode the blend mask in an **int**.

## Creating a common API

This project implements a common API that can be used like this

```C++
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
    __m256i a = _mm256_set1_epi8(0);
    __m256i b = _mm256_setr_epi8( 1,  2,  3,  4,  5,  6,  7,  8,
                                  9, 10, 11, 12, 13, 14, 15, 16,
                                 17, 18, 19, 20, 21, 22, 23, 24,
                                 25, 26, 27, 28, 29, 30, 31, 32);
  auto blend_result = blend256(a, b, mask);
```

The implementation makes use of http://boostorg.github.io/hana
