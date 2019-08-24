#include <gtest/gtest.h>

#include "factorial.hpp"
#include "custom_container.hpp"
#include "reserving_allocator.hpp"

// ------------------------------------------------------------------
TEST(FactorialTest, FactorialTest) {
    ASSERT_EQ(math::factorial( 0), 0);
    ASSERT_EQ(math::factorial( 1), 1);
    ASSERT_EQ(math::factorial( 2), 2);
    ASSERT_EQ(math::factorial( 5), 120);
    ASSERT_EQ(math::factorial(10), 3'628'800);
}

// ------------------------------------------------------------------
TEST(ReservingAllocatorTest, ReservingAllocatorTest) {
    constexpr size_t size = 5;
    constexpr size_t overflow_size = 6;

    allocators::reserving_allocator<int, size> ra;
    ASSERT_NO_THROW(ra.allocate(size));
    ASSERT_THROW(ra.allocate(1), std::overflow_error);

    allocators::reserving_allocator<int, size> ra_1;
    ASSERT_THROW(ra_1.allocate(overflow_size), std::length_error);
}

// ------------------------------------------------------------------
TEST(CustomContainerTest, CustomContainerTest) {
    constexpr size_t container_size  = 5;
    constexpr size_t unbounded_index = 10;

    containers::custom_container<size_t, allocators::reserving_allocator<size_t, container_size>> cc;
    ASSERT_EQ(cc.size(), 0);

    for (size_t i = 0; i < container_size; ++i) {
        cc.push_back(i);
    }
    ASSERT_THROW(cc.push_back(0), std::overflow_error);

    ASSERT_EQ(cc.size(), container_size);

    for (size_t i = 0; i < container_size; ++i) {
        ASSERT_EQ(cc.get(i), i);
    }
    ASSERT_THROW(cc.get(unbounded_index), std::out_of_range);
}

// ------------------------------------------------------------------
int main( int argc, char* argv[] ) {
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}