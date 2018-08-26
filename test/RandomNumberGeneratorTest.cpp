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
#include <thread>
#include <mutex>
#include <RandomNumberGenerator.hpp>

using simons_lib::random_number_generator::RandomNumberGenerator;

using RngI     = RandomNumberGenerator<std::default_random_engine, std::uniform_int_distribution<int>>;
using RngFSync = RandomNumberGenerator<std::default_random_engine, std::uniform_real_distribution<float>, std::mutex>;

TEST(RandomNumberGeneratorTest, setBoundries)
{
    auto rng = RngI(0);
    auto lBound = -10;
    auto uBound =  10;

    // Valid Input result must be true
    ASSERT_TRUE(rng.setBoundries(lBound, uBound));

    // Generate a 100000 Numbers and check if they stay in the interval
    auto cycles = 100000;
    for (auto i = 0; i < cycles; ++i)
    {
        auto val = rng();
        ASSERT_TRUE(lBound <= val && val <= uBound);
    }
}

TEST(RandomNumberGeneratorTest, setBoundriesInvalidInput)
{
    auto rng = RngI(std::random_device()());
    auto lBound = 10;
    auto uBound = -10;

    ASSERT_FALSE(rng.setBoundries(lBound, uBound));
}

TEST(RandomNumberGeneratorTest, synchronized)
{
    auto rng = RngFSync(std::random_device()());

    // Spawn a few threads and let them get values from the rng.
    auto threadfunc = [&rng] ()
    {
        auto val = rng();
        (void) val;
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

}