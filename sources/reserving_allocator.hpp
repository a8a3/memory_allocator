#pragma once

namespace {

template<typename T, size_t N>
T* reserve() {
    static_assert( N > 0, "count of reserved elements must by greater than 0" );
    auto p = reinterpret_cast<T*>( std::malloc(N * sizeof(T)));

    if (!p) {
        throw std::bad_alloc();
    }
    return p;
}

} // namespace

namespace allocators {

template<typename T, std::size_t N>
class reserving_allocator {
   T*             chunk_         {nullptr};
   std::ptrdiff_t next_chunk_pos_{0};
 
public:
    using value_type = T;
   
    template<typename U>
    struct rebind {
        using other = reserving_allocator<U, N>;
    };

    ~reserving_allocator() {
        std::free( chunk_ );
    }

    T* allocate(std::size_t n) {
        T* p{nullptr};

        if (!chunk_) {
            if (n > N) {
                throw std::length_error("no free space available in container");
            }
            chunk_ = reserve<T, N>();
            p = chunk_;
            next_chunk_pos_ += n;
        } 
        else {
            if (next_chunk_pos_ + n > N) {
                throw std::overflow_error("no free space available in container");
            }
            p = chunk_ + next_chunk_pos_;
            next_chunk_pos_ += n;
        }
        return p;
    }

    void deallocate(T*, std::size_t) {
        if (chunk_ == nullptr) {
            throw std::logic_error("attempt to deallocate unreserved memory");
        }
    }

    template<typename ...Args>
    void construct(T* p, Args&& ...args) {
        ::new(p) T(std::forward<Args>(args)...);
    }
 
    void destroy(T* p) {
        p->~T();
    }
};

} // namespace allocators