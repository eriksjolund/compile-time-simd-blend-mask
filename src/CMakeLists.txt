cmake_minimum_required(VERSION 3.11)
project(minitesthana LANGUAGES CXX)

find_package(Hana)

function(mask_example_executable name)
    add_executable(${name})
    target_sources(${name} PRIVATE main.cc)
    target_link_libraries(${name} hana)

    target_compile_options(${name} PRIVATE
	$<$<CXX_COMPILER_ID:GNU>:-mavx -mavx2>
	$<$<CXX_COMPILER_ID:Clang>:-mavx -mavx2>
	$<$<CXX_COMPILER_ID:MSVC>:/arch:AVX>
    )

    target_compile_features(${name} PRIVATE cxx_std_17)
    target_compile_options(${name} PRIVATE -save-temps=obj)

    target_compile_definitions(${name} PRIVATE
      ${name}
    )
endfunction()

mask_example_executable(mask_1111_0000_1111_0000_0000_0000_0000_0000)
mask_example_executable(mask_1100_0011_0000_0000_1100_0011_0000_0000)
mask_example_executable(mask_1000_0000_0000_0000_0000_0000_0000_0000)
