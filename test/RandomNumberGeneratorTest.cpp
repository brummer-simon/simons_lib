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
