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