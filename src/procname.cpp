#include "procname.hpp"

#ifdef __linux__
#   include <sys/types.h>
#elif __APPLE__
#   include <libproc.h>
#endif


#ifdef _MSC_VER
#include <io.h>
#include <process.h>
#else
#include <unistd.h>
#endif 

#include <cstring>

#include "blackhole/stdext/string_view.hpp"

namespace blackhole {
inline namespace v1 {

namespace {

#ifdef _MSC_VER
auto procname(int pid) -> stdext::string_view {
  (void)pid;
  // MTD: Implement a Windows version. GetModuleName() should do the trick.
  const char undefined_name[] = "Unknown Program Name";
  return stdext::string_view(undefined_name, ::strlen(undefined_name));
}
#else
auto procname(pid_t pid) -> stdext::string_view {
#ifdef __linux__
    (void)pid;
    return stdext::string_view(program_invocation_short_name, ::strlen(program_invocation_short_name));
#elif __APPLE__
    static char path[PROC_PIDPATHINFO_MAXSIZE];

    if (::proc_name(pid, path, sizeof(path)) > 0) {
        return stdext::string_view(path, ::strlen(path));
    } else {
        const auto nwritten = ::snprintf(path, sizeof(path), "%d", pid);
        return stdext::string_view(path, static_cast<std::size_t>(nwritten));
    }
#endif
}
#endif
} // namespace

auto procname() -> stdext::string_view {
#ifdef _MSC_VER
    static const stdext::string_view name = procname(::_getpid());
#else
    static const stdext::string_view name = procname(::getpid());
#endif
    return name;
}

} // namespace v1
} // namespace blackhole
