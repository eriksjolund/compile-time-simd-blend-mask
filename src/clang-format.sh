#!/bin/sh

# The clang-format-7 command makes use of the configuration file
# compile-time-simd-blend-mask/src/.clang-format

files="blend256.h
calculate_int_for_blend_epi32.h
check_num_bytes_mask.h
convert_tuplemask_to_mm256i.h
main.cc
to_tuple_partition_combinebytes.h
tuplemask_for_bigger_integers.h
verify_blend_result.h
"

for i in $files; do 
  if [ ! -w $i ]; then
     echo "file $i does not exist"
     exit 1
  fi
  clang-format-7 -i $i
done
