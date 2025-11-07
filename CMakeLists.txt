cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 20)

project(physmech)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wunused-const-variable
    -Wlogical-op
    -Wduplicated-cond
    -Wredundant-decls
    -Wnon-virtual-dtor
    -Woverloaded-virtual
    -Wsuggest-override
    -Wzero-as-null-pointer-constant
    -Wsign-promo
    -Wfloat-equal
    -Wcast-qual
    -Wcast-align
    -Wmissing-field-initializers
    -Werror
)

add_subdirectory(TVD)

