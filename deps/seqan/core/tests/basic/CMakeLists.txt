# ===========================================================================
#                  SeqAn - The Library for Sequence Analysis
# ===========================================================================
# File: /core/tests/basic/CMakeLists.txt
#
# CMakeLists.txt file for the basic module tests.
# ===========================================================================

cmake_minimum_required (VERSION 2.8.2)
project (seqan_core_tests_basic)
message (STATUS "Configuring core/tests/basic")

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Search SeqAn and select dependencies.
set (SEQAN_FIND_DEPENDENCIES NONE)
find_package (SeqAn REQUIRED)

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

# Add include directories.
include_directories (${SEQAN_INCLUDE_DIRS})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Update the list of file names below if you add source files to your test.
add_executable (
  test_basic_metaprogramming
  test_basic_metaprogramming.cpp
  test_basic_metaprogramming_logic.h
  test_basic_metaprogramming_type.h)
target_link_libraries (test_basic_metaprogramming ${SEQAN_LIBRARIES})

add_executable (
  test_basic_fundamental
  test_basic_fundamental.cpp
  test_basic_fundamental_helpers.h
  test_basic_fundamental_tags.h
  test_basic_fundamental_metafunctions.h
  test_basic_fundamental_transport.h
  test_basic_fundamental_comparison.h
  test_basic_fundamental_conversion.h
  test_basic_array_construct_destruct.h
  test_basic_hosted_type_interface.h)
target_link_libraries (test_basic_fundamental ${SEQAN_LIBRARIES})

add_executable (
  test_basic_concept
  test_basic_concept.cpp
  test_basic_fundamental_concepts.h)
target_link_libraries (test_basic_concept ${SEQAN_LIBRARIES})

add_executable (
  test_basic_alphabet
  test_basic_alphabet.cpp
  test_basic_alphabet_adapt_builtins.h
  test_basic_alphabet_bio.h
  test_basic_alphabet_concepts.h
  test_basic_alphabet_math.h
  test_basic_alphabet_profile.h
  test_basic_alphabet_qualities.h
  test_basic_alphabet_residue.h
  test_basic_alphabet_storage.h
  test_basic_fundamental_helpers.h)
target_link_libraries (test_basic_alphabet ${SEQAN_LIBRARIES})

add_executable (
  test_basic_aggregate
  test_basic_aggregate.cpp
  test_basic_aggregate.h)
target_link_libraries (test_basic_aggregate ${SEQAN_LIBRARIES})

add_executable (
  test_basic_allocator
  test_basic_allocator.cpp
  test_basic_allocator.h)
target_link_libraries (test_basic_allocator ${SEQAN_LIBRARIES})

add_executable (
  test_basic_parallelism
  test_basic_parallelism.cpp
  test_basic_parallelism.h)
target_link_libraries (test_basic_parallelism ${SEQAN_LIBRARIES})

add_executable (
  test_basic_math
  test_basic_math.cpp
  test_basic_math.h)
target_link_libraries (test_basic_math ${SEQAN_LIBRARIES})

add_executable (
  test_basic_smart_pointer
  test_basic_smart_pointer.cpp
  test_basic_smart_pointer_holder.h)
target_link_libraries (test_basic_smart_pointer ${SEQAN_LIBRARIES})

add_executable (
  test_basic_container
  test_basic_container.cpp)
target_link_libraries (test_basic_container ${SEQAN_LIBRARIES})

add_executable (
  test_basic_proxy
  test_basic_proxy.cpp
  test_basic_proxy.h)
target_link_libraries (test_basic_proxy ${SEQAN_LIBRARIES})

add_executable (
  test_basic_iterator
  test_basic_iterator.cpp
  test_basic_iterator.h)
target_link_libraries (test_basic_iterator ${SEQAN_LIBRARIES})

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

# ----------------------------------------------------------------------------
# Register with CTest
# ----------------------------------------------------------------------------

add_test (NAME test_test_basic_metaprogramming COMMAND $<TARGET_FILE:test_basic_metaprogramming>)
add_test (NAME test_test_basic_fundamental COMMAND $<TARGET_FILE:test_basic_fundamental>)
add_test (NAME test_test_basic_concept COMMAND $<TARGET_FILE:test_basic_concept>)
add_test (NAME test_test_basic_alphabet COMMAND $<TARGET_FILE:test_basic_alphabet>)
add_test (NAME test_test_basic_aggregate COMMAND $<TARGET_FILE:test_basic_aggregate>)
add_test (NAME test_test_basic_allocator COMMAND $<TARGET_FILE:test_basic_allocator>)
add_test (NAME test_test_basic_parallelism COMMAND $<TARGET_FILE:test_basic_parallelism>)
add_test (NAME test_test_basic_math COMMAND $<TARGET_FILE:test_basic_math>)
add_test (NAME test_test_basic_smart_pointer COMMAND $<TARGET_FILE:test_basic_smart_pointer>)
add_test (NAME test_test_basic_container COMMAND $<TARGET_FILE:test_basic_container>)
add_test (NAME test_test_basic_proxy COMMAND $<TARGET_FILE:test_basic_proxy>)
add_test (NAME test_test_basic_iterator COMMAND $<TARGET_FILE:test_basic_iterator>)

