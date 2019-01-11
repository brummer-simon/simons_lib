/*
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
#include <array>
#include <thread>
#include <mutex>
#include <CachedCallable.hpp>

using simons_lib::cached_callable::CachedCallable;

namespace
{
int testFunc(void)
{
    return 42;
}
}

TEST(CachedCallableTest, UseLambda)
{
    auto expected = 42;
    auto func = [expected] ()
    {
        return expected;
    };
    auto testObj = CachedCallable<decltype(expected)>(func);
    ASSERT_EQ(expected, testObj());
}

TEST(CachedCallableTest, UseFunction)
{
    auto expected = 42;
    auto testObj  = CachedCallable<decltype(expected)>(testFunc);
    ASSERT_EQ(expected, testObj());
}

TEST(CachedCallableTest, UseFunctionObject)
{
    auto expected = 42;
    struct funcObj
    {
        decltype(expected) operator () (void)
        {
            return 42;
        }
    };
    auto testObj = CachedCallable<decltype(expected)>(funcObj());
    ASSERT_EQ(expected, testObj());
}

TEST(CachedCallableTest, reset)
{
    auto expected = 1;
    auto func = [] ()
    {
        static auto execCnt = 0;
        return (++execCnt);
    };
    auto testObj = CachedCallable<decltype(expected)>(func);

    // Execute multiple times. There should be no reevaluation
    ASSERT_EQ(expected, testObj());
    ASSERT_EQ(expected, testObj());
    ASSERT_EQ(expected, testObj());

    // Clear cache, next evaluation has to deliver a different result
    testObj.reset();
    ASSERT_EQ(++expected, testObj());
}

TEST(CachedCallableTest, synchronized)
{
    auto expected = 10;
    auto func = [] ()
    {
        static auto execCnt = 0;
        return (++execCnt);
    };
    auto testObj = CachedCallable<decltype(expected), std::mutex>(func);

    // Spawn 10 threads to reset and call the TestObject.
    // As a result: The counter should have reached 10
    auto threadfunc = [&testObj] ()
    {
        testObj.reset();
        testObj();
    };

    auto threads = std::array<std::thread, 10>();

    for (auto& handle : threads)
    {
        handle = std::thread(threadfunc);
    }

    for (auto& handle : threads)
    {
        handle.join();
    }

    ASSERT_EQ(expected, testObj());
}
