#pragma once

#include <iostream>

template<typename T, std::size_t N>
struct reserving_allocator {
    using value_type = T;
   
    template<typename U>
    struct rebind {
        using other = reserving_allocator<U, N>;
    };
    std::size_t chunk_pos{0};
    T*          chunk    {nullptr};
 
    static T* reserve(std::size_t n) {
        static_assert( N > 0, "count of reserved elements must by greater than 0" );
        auto p = reinterpret_cast<T*>( std::malloc(n * sizeof(T)));

        if (!p) {
            throw std::bad_alloc();
        }
        return p;
    }

    T* allocate(std::size_t) {
        if (chunk_pos == N) {
            throw std::overflow_error("no free space available in container");
        }
        if (!chunk) {
            chunk = reserve(N);
        }

        auto p = chunk + chunk_pos;
        ++chunk_pos;
        return p;
    }

    void deallocate(T*, std::size_t) {
        std::free(chunk);
        chunk = nullptr;
        chunk_pos = 0;
    }

    template<typename ...Args>
    void construct(T* p, Args&& ...args) {
        ::new(p) T(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }
};