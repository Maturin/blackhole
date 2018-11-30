#pragma once

#include "blackhole/record.hpp"

namespace blackhole {
inline namespace v1 {

struct record_t::inner_t {
    std::reference_wrapper<const string_view> message;
    std::reference_wrapper<const string_view> formatted;

    severity_t severity;
    time_point timestamp;

    std::uint64_t lwp;

#ifdef _MSC_VER
    std::thread::id tid;
#else
    std::thread::native_handle_type tid;
#endif
    char __pad[8];

    std::reference_wrapper<const attribute_pack> attributes;
};

}  // namespace v1
}  // namespace blackhole
