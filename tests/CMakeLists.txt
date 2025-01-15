include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
  OVERRIDE_FIND_PACKAGE
)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
include_directories(${gtest_SOURCE_DIR}/include)

add_executable(list_tests
    demangle.cpp
    demangle.hpp
    helper.cpp
    helper.hpp
    list_tests.cpp
    operations_tests.cpp
    test_lists.hpp
    test_operations.hpp
    tuple_tests.cpp
)

target_link_libraries(list_tests PUBLIC
    gtest
    gmock_main
)

include(AddMetaTest)
add_meta_test(list_tests)
