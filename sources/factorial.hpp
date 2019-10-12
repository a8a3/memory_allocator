#pragma once

namespace math {

constexpr size_t factorial(size_t n) {
    if (n == 0) {
        return 1;
    }

    if (n <= 2) {
        return n;
    }

    size_t result = 1;
    for ( size_t i = 1; i <= n; ++i ) {
        result *= i;
    }
    return result;
}

} // namespace math