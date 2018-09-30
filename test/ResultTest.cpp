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
#include <Result.hpp>

using namespace simons_lib::result;

// Tests for results success type
TEST(OkTest, behavior)
{
    // Construct Ok with different types and values. Compare results.
    ASSERT_EQ(Ok<int>(-1),             Ok<int>(-1));
    ASSERT_EQ(Ok<unsigned>(1),         Ok<unsigned>(1));
    ASSERT_EQ(Ok<char>('A'),           Ok<char>('A'));
    ASSERT_EQ(Ok<char const *>("Foo"), Ok<char const *>("Foo"));
    ASSERT_EQ(Ok<std::string>("Foo"),  Ok<std::string>("Foo"));

    ASSERT_NE(Ok<int>(-1),             Ok<int>(1));
    ASSERT_NE(Ok<unsigned>(1),         Ok<unsigned>(-1));
    ASSERT_NE(Ok<char>('A'),           Ok<char>('B'));
    ASSERT_NE(Ok<char const *>("Foo"), Ok<char const *>("Bar"));
    ASSERT_NE(Ok<std::string>("Foo"),  Ok<std::string>("Bar"));

    // Testing methods
    auto toTest = Ok<int>(42);
    ASSERT_EQ(toTest.getValue(), 42);
    ASSERT_EQ(toTest.getConstRef(), 42);
    ASSERT_EQ(toTest.getRef(), 42);

    toTest.getRef() = 23;
    ASSERT_EQ(toTest.getConstRef(), 23);
}

// Tests for results error type
TEST(ErrTest, behavior)
{
    // Construct Err with different types and values. Compare results.
    ASSERT_EQ(Err<int>(-1),             Err<int>(-1));
    ASSERT_EQ(Err<unsigned>(1),         Err<unsigned>(1));
    ASSERT_EQ(Err<char>('A'),           Err<char>('A'));
    ASSERT_EQ(Err<char const *>("Foo"), Err<char const *>("Foo"));
    ASSERT_EQ(Err<std::string>("Foo"),  Err<std::string>("Foo"));

    ASSERT_NE(Err<int>(-1),             Err<int>(1));
    ASSERT_NE(Err<unsigned>(1),         Err<unsigned>(-1));
    ASSERT_NE(Err<char>('A'),           Err<char>('B'));
    ASSERT_NE(Err<char const *>("Foo"), Err<char const *>("Bar"));
    ASSERT_NE(Err<std::string>("Foo"),  Err<std::string>("Bar"));

    // Testing methods
    auto toTest = Err<int>(42);
    ASSERT_EQ(toTest.getValue(), 42);
    ASSERT_EQ(toTest.getConstRef(), 42);
    ASSERT_EQ(toTest.getRef(), 42);

    toTest.getRef() = 23;
    ASSERT_EQ(toTest.getConstRef(), 23);
}

// Tests for result type
TEST(ResultTest, isOk)
{
    auto ok = Result<int, int>(Ok<int>(0));
    ASSERT_EQ(ok.isOk(), true);

    auto err = Result<int, int>(Err<int>(0));
    ASSERT_EQ(err.isOk(), false);
}

TEST(ResultTest, isErr)
{
    auto err = Result<int, int>(Err<int>(0));
    ASSERT_EQ(err.isErr(), true);

    auto ok = Result<int, int>(Ok<int>(0));
    ASSERT_EQ(ok.isErr(), false);
}

TEST(ResultTest, getOk)
{
    auto ok = Result<int, int>(Ok<int>(0));
    ASSERT_EQ(ok.getOk(), std::optional<int>(0));
    ASSERT_EQ(ok.getOk(), 0);

    auto err = Result<int, int>(Err<int>(0));
    ASSERT_EQ(err.getOk(), std::nullopt);
}

TEST(ResultTest, getErr)
{

    auto err = Result<int, int>(Err<int>(0));
    ASSERT_EQ(err.getErr(), std::optional<int>(0));
    ASSERT_EQ(err.getErr(), 0);

    auto ok = Result<int, int>(Ok<int>(0));
    ASSERT_EQ(ok.getErr(), std::nullopt);
}

TEST(ResultTest, unwrap)
{
    auto ok = Result<int, int>(Ok<int>(0));
    ASSERT_EQ(ok.unwrap(), 0);
    // ASSERT_EQ(ok.unwrapErr(), 0);
}

TEST(ResultTest, unwrapErr)
{
    auto err = Result<int, int>(Err<int>(0));
    ASSERT_EQ(err.unwrapErr(), 0);
    // ASSERT_EQ(err.unwrap(), 0);
}

TEST(ResultTest, unwrapOrDefault)
{
    auto ok = Result<int, int>(Ok<int>(0));
    ASSERT_EQ(ok.unwrapOrDefault(0), 0);

    auto err = Result<int, int>(Err<int>(0));
    ASSERT_EQ(err.unwrapOrDefault(1), 1);
}

TEST(ResultTest, unwrapOrElse)
{
    auto fn = [] (int const& i)
    {
        return i +1;
    };

    auto ok = Result<int, int>(Ok<int>(0));
    ASSERT_EQ(ok.unwrapOrElse(fn), 0);

    auto err = Result<int, int>(Err<int>(0));
    ASSERT_EQ(err.unwrapOrElse(fn), 1);
}
