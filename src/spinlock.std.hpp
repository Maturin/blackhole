#pragma once

#include <atomic>

namespace blackhole {
inline namespace v1 {

class spinlock_t {
    std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;

public:
    spinlock_t() { }

    ~spinlock_t() {  }

    auto lock() noexcept -> void {
        while (lock_flag.test_and_set());
    }

    auto unlock() noexcept -> void {
        lock_flag.clear();
    }
};

} // namespace v1
} // namespace blackhole
