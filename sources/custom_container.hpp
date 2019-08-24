#pragma once
#include <vector>

namespace containers {

template<typename T, typename A = std::allocator<T>>
class custom_container {
    A alloc_;
    std::vector<T*> items_;
    static constexpr size_t requested_elems_size = 1;

public:
    custom_container() = default;
    ~custom_container() {
        
        const auto sz = size();

        if ( sz > 0 ) {
            for ( size_t i = sz-1; i > 0; --i ) {
                auto item = items_[i];
                alloc_.destroy(item);
                alloc_.deallocate(item, requested_elems_size);
            }
        }
    }

    void push_back(const T& item) {
        T* buf = alloc_.allocate(requested_elems_size);
        alloc_.construct(buf, item);
        items_.push_back(buf);
    }

    const T& get(std::size_t ind) const {
        if (ind >= size()) {
            throw std::out_of_range( "incorrect index passed" );
        }
        return *items_[ind];
    }

    size_t size() const {
        return items_.size();
    }
};

} // namespace containers