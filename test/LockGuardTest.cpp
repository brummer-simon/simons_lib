/**
 * BSD 3-Clause License
 *
 * Copyright (c) 2018, Simon Brummer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
