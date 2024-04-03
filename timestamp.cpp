#include "timestamp.h"

using leaf::timestamp;

uint64_t timestamp::nanoseconds() const { return std::chrono::time_point_cast<std::chrono::nanoseconds>(point_).time_since_epoch().count(); }
uint64_t timestamp::milliseconds() const { return std::chrono::time_point_cast<std::chrono::milliseconds>(point_).time_since_epoch().count(); }
uint64_t timestamp::microseconds() const { return std::chrono::time_point_cast<std::chrono::microseconds>(point_).time_since_epoch().count(); }
uint64_t timestamp::seconds() const { return std::chrono::time_point_cast<std::chrono::seconds>(point_).time_since_epoch().count(); }

timestamp timestamp::from_nanoseconds(uint64_t nanoseconds) { return timestamp(std::chrono::time_point<std::chrono::system_clock>(std::chrono::nanoseconds(nanoseconds))); }
timestamp timestamp::from_microseconds(uint64_t microseconds) { return timestamp(std::chrono::time_point<std::chrono::system_clock>(std::chrono::microseconds(microseconds))); }
timestamp timestamp::from_milliseconds(uint64_t milliseconds) { return timestamp(std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(milliseconds))); }
timestamp timestamp::from_seconds(uint64_t seconds) { return timestamp(std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(seconds))); }
