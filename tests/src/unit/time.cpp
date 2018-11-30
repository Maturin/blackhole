#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include <src/util/time.hpp>

#include <time.h>

namespace blackhole {
inline namespace v1 {
namespace {

TEST(time, RandomGreenwichTime) {
    std::random_device rd;
    std::uniform_int_distribution<long> dist(0l, std::time(nullptr));

#ifndef _MSC_VER // MTD: Understand and fix the procblem!
     for (auto i = 0; i < 10000; ++i) {
         auto time = dist(rd);

         std::tm tm1;

#ifdef _MSC_VER
         ::gmtime_s(&tm1, &time);
#else
         ::gmtime_r(&time, &tm1);
#endif

         std::tm tm2;
         blackhole::gmtime(&time, &tm2);

         ASSERT_EQ(tm2.tm_sec, tm1.tm_sec);
         ASSERT_EQ(tm2.tm_min, tm1.tm_min);
         ASSERT_EQ(tm2.tm_hour, tm1.tm_hour);
         ASSERT_EQ(tm2.tm_mday, tm1.tm_mday);
         ASSERT_EQ(tm2.tm_mon, tm1.tm_mon);
         ASSERT_EQ(tm2.tm_year, tm1.tm_year);
         ASSERT_EQ(tm2.tm_year, tm1.tm_year);
         ASSERT_EQ(tm2.tm_yday, tm1.tm_yday);
         ASSERT_EQ(tm2.tm_isdst, tm1.tm_isdst);
     }
#endif
}

TEST(time, RandomLocalTime) {
    auto time = std::time(nullptr);

    std::tm tm1;
#ifdef _MSC_VER
    ::localtime_s(&tm1, &time);
#else
    ::localtime_r(&time, &tm1);
#endif

    std::tm tm2;
    blackhole::localtime(&time, &tm2);

    ASSERT_EQ(tm2.tm_sec, tm1.tm_sec);
    ASSERT_EQ(tm2.tm_min, tm1.tm_min);
    ASSERT_EQ(tm2.tm_hour, tm1.tm_hour);
    ASSERT_EQ(tm2.tm_mday, tm1.tm_mday);
    ASSERT_EQ(tm2.tm_mon, tm1.tm_mon);
    ASSERT_EQ(tm2.tm_year, tm1.tm_year);
    ASSERT_EQ(tm2.tm_year, tm1.tm_year);
    ASSERT_EQ(tm2.tm_yday, tm1.tm_yday);
    ASSERT_EQ(tm2.tm_isdst, tm1.tm_isdst);
}

} // namespace
} // namespace v1
} // namespace blackhole
