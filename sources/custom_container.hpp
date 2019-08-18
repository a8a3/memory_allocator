#pragma once
#include <vector>

template<typename T, typename A = std::allocator<T>>
struct custom_container {
    A alloc;
    std::vector<T*> items;

    custom_container() = default;
    ~custom_container() {
        for ( size_t i = 0, sz = size(); i < sz; ++i ) {
            auto& item = items[i];
            alloc.destroy(item);
            alloc.deallocate(item, 1);
        }
    }

    void push_back(const T& item) {
        T* buf = alloc.allocate(1);
        alloc.construct(buf, item);
        items.push_back(buf);
    }

    const T& get(std::size_t ind) const {
        if (ind >= size()) {
            throw std::out_of_range( "incorrect index passed" );
        }
        return *items[ind];
    }

    size_t size() const {
        return items.size();
    }
};