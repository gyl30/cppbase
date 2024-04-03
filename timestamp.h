#ifndef LEAF_TIMESTAMP_H
#define LEAF_TIMESTAMP_H

#include <string>
#include <chrono>

namespace leaf
{
class timestamp
{
   private:
    timestamp() = default;
    explicit timestamp(std::chrono::time_point<std::chrono::system_clock> point) : point_(point){};

   public:
    uint64_t nanoseconds() const;
    uint64_t milliseconds() const;
    uint64_t microseconds() const;
    uint64_t seconds() const;

   public:
    static timestamp now();
    static timestamp from_nanoseconds(uint64_t nanoseconds);
    static timestamp from_microseconds(uint64_t microseconds);
    static timestamp from_milliseconds(uint64_t milliseconds);
    static timestamp from_seconds(uint64_t seconds);

   private:
    std::chrono::time_point<std::chrono::system_clock> point_;
};
}    // namespace leaf

#endif
