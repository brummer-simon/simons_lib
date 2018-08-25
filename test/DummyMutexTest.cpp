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
#include <DummyMutex.hpp>
#include <mutex>

using simons_lib::lock::DummyMutex;

/**
 * @note: This tests are a success then there are no errors during compilation.
 *        There is not much to test because is only the interface.
 */
TEST(DummyMutexTest, use_with_lock_guard)
{
   auto mtx  = DummyMutex();
   auto lock = std::lock_guard<decltype(mtx)>(mtx);
}

TEST(DummyMutexTest, use_with_lock)
{
   auto mtx  = DummyMutex();
   auto lock = std::unique_lock<decltype(mtx)>(mtx);

   lock.unlock();
   lock.lock();
   lock.unlock();
}
