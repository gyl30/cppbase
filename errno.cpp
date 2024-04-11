#include <cstring>

#include "error.h"

namespace leaf
{
std::string errno_to_str()
{
    char buf[BUFSIZ] = {0};
#ifdef _GNU_SOURCE
    char* ret = strerror_r(errno, buf, sizeof buf);
    return ret;
#else
    const int ret = strerror_r(errno, buf, sizeof buf);
    if (ret != 0)
    {
        return "unknown error";
    }
    return buf;
#endif
}
}    // namespace leaf
