/**
 * Copyright (C) 2018 Simon Brummer <simon.brummer@posteo.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * See the file LICENSE in the top level directory for more details.
 */

#include <gtest/gtest.h>
#include <LockGuard.hpp>
#include <DummyMutex.hpp>
#include <mutex>

using simons_lib::lock::LockGuard;
using simons_lib::lock::DummyMutex;

TEST(LockGuardTest, behavior)
{
    auto expected = 2;
    struct TestBasicLocable
    {
        int cnt = 0;

        void lock(void)
        {
            ++cnt;
        };

        void unlock(void)
        {
            ++cnt;
        };
    };
    
    auto lock = TestBasicLocable();
    {
        auto guard = LockGuard<decltype(lock)>(lock);
    }

    ASSERT_EQ(expected, lock.cnt);
}

TEST(LockGuardTest, guard_with_std_mutex)
{
    auto lock = std::mutex();
    auto guard = LockGuard<decltype(lock)>(lock);
}

TEST(LockGuardTest, guard_width_dummy_mutex)
{
    auto lock = DummyMutex();
    auto guard = LockGuard<decltype(lock)>(lock);
}
