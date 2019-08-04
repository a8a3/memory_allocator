cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(allocator VERSION 0.0.1)
endif()

find_package(Threads REQUIRED)
find_package(GTest   REQUIRED)

add_executable(allocator       sources/allocator.cpp)
add_executable(allocator_gtest tests/allocator_gtest.cpp)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(allocator_gtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)

target_link_libraries(allocator_gtest 
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(allocator_gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(allocator_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexpoligon@mail.ru)

include(CPack)

enable_testing()

add_test(allocator_gtest allocator_gtest)

add_custom_command(
    TARGET allocator_gtest
    POST_BUILD 
    COMMAND ./allocator_gtest
    COMMENT "Run allocator test..."
)