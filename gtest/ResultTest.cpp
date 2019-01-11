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

#include <type_traits>
#include <gtest/gtest.h>
#include <Defines.hpp>
#include <Result.hpp>
#include <NullTypes/NullObjImpl.hpp>

using namespace simons_lib::result;
using simons_lib::null_types::NullObj;

template<typename T, typename E>
Result<T, E> implcitConvertOk()
{
    if constexpr (std::is_same<T, void>::value)
    {
        return Ok<void>();
    }
    else
    {
        return Ok<T>(T());
    }
}

template<typename T, typename E>
Result<T, E> implcitConvertErr()
{
    if constexpr (std::is_same<E, void>::value)
    {
        return Err<void>();
    }
    else
    {
        return Err<E>(E());
    }
}

// Tests for results success type
TEST(OkTest, Behavior)
{
    // Construct Ok with different types and values. Compare results.
    ASSERT_EQ(Ok<void>(),              Ok<void>());
    ASSERT_EQ(Ok<NullObj>(NullObj()),  Ok<NullObj>(NullObj()));
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

TEST(OkTest, operatorEquality)
{
    ASSERT_EQ(Ok<void>()              == Ok<void>(), true);
    ASSERT_EQ(Ok<int>(0)              == Ok<int>(0), true);
    ASSERT_EQ(Ok<int>(0)              == Ok<int>(1), false);
    ASSERT_EQ(Ok<char const *>("Foo") == Ok<char const *>("Foo"), true);
    ASSERT_EQ(Ok<char const *>("Foo") == Ok<char const *>("Bar"), false);
}

TEST(OkTest, operatorInequality)
{
    ASSERT_EQ(Ok<void>()              != Ok<void>(), false);
    ASSERT_EQ(Ok<int>(0)              != Ok<int>(0), false);
    ASSERT_EQ(Ok<int>(0)              != Ok<int>(1), true);
    ASSERT_EQ(Ok<char const *>("Foo") != Ok<char const *>("Foo"), false);
    ASSERT_EQ(Ok<char const *>("Foo") != Ok<char const *>("Bar"), true);
}

// Tests for results error type
TEST(ErrTest, Behavior)
{
    // Construct Err with different types and values. Compare results.
    ASSERT_EQ(Err<void>(),              Err<void>());
    ASSERT_EQ(Err<NullObj>(NullObj()),  Err<NullObj>(NullObj()));
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

TEST(ErrTest, operatorEquality)
{
    ASSERT_EQ(Err<void>()              == Err<void>(), true);
    ASSERT_EQ(Err<int>(0)              == Err<int>(0), true);
    ASSERT_EQ(Err<int>(0)              == Err<int>(1), false);
    ASSERT_EQ(Err<char const *>("Foo") == Err<char const *>("Foo"), true);
    ASSERT_EQ(Err<char const *>("Foo") == Err<char const *>("Bar"), false);
}

TEST(ErrTest, operatorInequality)
{
    ASSERT_EQ(Err<void>()              != Err<void>(), false);
    ASSERT_EQ(Err<int>(0)              != Err<int>(0), false);
    ASSERT_EQ(Err<int>(0)              != Err<int>(1), true);
    ASSERT_EQ(Err<char const *>("Foo") != Err<char const *>("Foo"), false);
    ASSERT_EQ(Err<char const *>("Foo") != Err<char const *>("Bar"), true);
}

// Tests for result type
TEST(ResultTest, isOk)
{
    // Test isOk() for all specializations of Ok<T>
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_EQ(ok.isOk(), true);
    }
    {
        auto ok = Result<int, void>(Ok<int>(0));
        ASSERT_EQ(ok.isOk(), true);
    }
    {
        auto ok = Result<void, int>(Ok<void>());
        ASSERT_EQ(ok.isOk(), true);
    }
    {
        auto ok = Result<void, void>(Ok<void>());
        ASSERT_EQ(ok.isOk(), true);
    }

    // Test isOk() for all specializations of Err<T>
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_EQ(err.isOk(), false);
    }
    {
        auto err = Result<int, void>(Err<void>());
        ASSERT_EQ(err.isOk(), false);
    }
    {
        auto err = Result<void, int>(Err<int>(0));
        ASSERT_EQ(err.isOk(), false);
    }
    {
        auto err = Result<void, void>(Err<void>());
        ASSERT_EQ(err.isOk(), false);
    }
}

TEST(ResultTest, isErr)
{
    // Test isErr() for all specializations of Err<T>
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_EQ(err.isErr(), true);
    }
    {
        auto err = Result<int, void>(Err<void>());
        ASSERT_EQ(err.isErr(), true);
    }
    {
        auto err = Result<void, int>(Err<int>(0));
        ASSERT_EQ(err.isErr(), true);
    }
    {
        auto err = Result<void, void>(Err<void>());
        ASSERT_EQ(err.isErr(), true);
    }

    // Test isErr() for all specializations of Ok<T>
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_EQ(ok.isErr(), false);
    }
    {
        auto ok = Result<int, void>(Ok<int>(0));
        ASSERT_EQ(ok.isErr(), false);
    }
    {
        auto ok = Result<void, int>(Ok<void>());
        ASSERT_EQ(ok.isErr(), false);
    }
    {
        auto ok = Result<void, void>(Ok<void>());
        ASSERT_EQ(ok.isErr(), false);
    }
}

TEST(ResultTest, getOk)
{
    // Test getOk() for all specializations of Ok<T>
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_EQ(ok.getOk(), 0);
    }
    {
        auto ok = Result<int, void>(Ok<int>(0));
        ASSERT_EQ(ok.getOk(), 0);
    }

    // Test getOk() for all specializations of Err<E>
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_EQ(err.getOk(), std::nullopt);
    }
    {
        auto err = Result<int, void>(Err<void>());
        ASSERT_EQ(err.getOk(), std::nullopt);
    }

    // Commenting in getOk() must lead to compilation errors
    {
        [[maybe_unused]] auto ok = Result<void, int>(Ok<void>());
        //ok.getOk();
    }
    {
        [[maybe_unused]] auto ok = Result<void, void>(Ok<void>());
        //ok.getOk();
    }
    {
        [[maybe_unused]] auto err = Result<void, int>(Err<int>(0));
        //err.getOk();
    }
    {
        [[maybe_unused]] auto err = Result<void, void>(Err<void>());
        //err.getOk();
    }
}

TEST(ResultTest, getErr)
{
    // Test getErr() for all specializations of Err<E>
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_EQ(err.getErr(), 0);
    }
    {
        auto err = Result<void, int>(Err<int>(0));
        ASSERT_EQ(err.getErr(), 0);
    }

    // Test getErr() for all specializations of Ok<T>
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_EQ(ok.getErr(), std::nullopt);
    }
    {
        auto ok = Result<void, int>(Ok<void>());
        ASSERT_EQ(ok.getErr(), std::nullopt);
    }

    // Commenting in getOk() must lead to compilation errors
    {
        [[maybe_unused]] auto ok = Result<int, void>(Ok<int>(0));
        //ok.getErr();
    }
    {
        [[maybe_unused]] auto ok = Result<void, void>(Ok<void>());
        //ok.getErr();
    }
    {
        [[maybe_unused]] auto err = Result<int, void>(Err<void>());
        //err.getErr();
    }
    {
        [[maybe_unused]] auto err = Result<void, void>(Err<void>());
        //err.getErr();
    }
}

TEST(ResultTest, unwrap)
{
    // Test unwrap() for all specializations of Ok<T>
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_EQ(ok.unwrap(), 0);
    }
    {
        auto ok = Result<int, void>(Ok<int>(0));
        ASSERT_EQ(ok.unwrap(), 0);
    }

    // Commenting in unwrap() must lead to compilation errors
    {
        [[maybe_unused]] auto ok = Result<void, int>(Ok<void>());
        //ok.unwrap();
    }
    {
        [[maybe_unused]] auto ok = Result<void, void>(Ok<void>());
        //ok.unwrap();
    }
    {
        [[maybe_unused]] auto err = Result<void, int>(Err<int>(0));
        //err.unwrap();
    }
    {
        [[maybe_unused]] auto err = Result<void, void>(Err<void>());
        //err.unwrap();
    }
}

TEST(ResultDeathTest, unwrap)
{
#ifndef SIMONS_LIB_DISABLE_EXIT
    // Test unwrap() for all specializations of Err<E>. Those must lead to a hard abort
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_DEATH(err.unwrap(), "");
    }
    {
        auto err = Result<int, void>(Err<void>());
        ASSERT_DEATH(err.unwrap(), "");
    }
#endif
}

TEST(ResultTest, unwrapErr)
{
    // Test unwrapErr() for all specializations of Err<T>
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_EQ(err.unwrapErr(), 0);
    }
    {
        auto err = Result<void, int>(Err<int>(0));
        ASSERT_EQ(err.unwrapErr(), 0);
    }

    // Commenting in unwrap() must lead to compilation errors
    {
        [[maybe_unused]] auto ok = Result<int, void>(Ok<int>(0));
        //ok.unwrapErr();
    }
    {
        [[maybe_unused]] auto ok = Result<void, void>(Ok<void>());
        //ok.unwrapErr();
    }
    {
        [[maybe_unused]] auto err = Result<int, void>(Err<void>());
        //err.unwrapErr();
    }
    {
        [[maybe_unused]] auto err = Result<void, void>(Err<void>());
        //err.unwrapErr();
    }
}

TEST(ResultDeathTest, unwrapErr)
{
#ifndef SIMONS_LIB_DISABLE_EXIT
    // Test unwrapErr() for all specializations of Ok<T>. Those must lead to a hard abort
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_DEATH(ok.unwrapErr(), "");
    }
    {
        auto ok = Result<void, int>(Ok<void>());
        ASSERT_DEATH(ok.unwrapErr(), "");
    }
#endif
}

TEST(ResultTest, unwrapOrDefault)
{
    // Test unwrapOrDefault() for all specializations of Ok<T>
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_EQ(ok.unwrapOrDefault(1), 0);
    }
    {
        auto ok = Result<int, void>(Ok<int>(0));
        ASSERT_EQ(ok.unwrapOrDefault(1), 0);
    }

    // Test unwrapOrDefault() for all specializations of Err<E>.
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_EQ(err.unwrapOrDefault(1), 1);
    }
    {
        auto err = Result<int, void>(Err<void>());
        ASSERT_EQ(err.unwrapOrDefault(1), 1);
    }

    // Commenting in unwrapOrDefault() must lead to compilation errors
    {
        [[maybe_unused]] auto ok = Result<void, int>(Ok<void>());
        //ok.unwrapOrDefault(0);
    }
    {
        [[maybe_unused]] auto ok = Result<void, void>(Ok<void>());
        //ok.unwrapOrDefault(0);
    }
    {
        [[maybe_unused]] auto err = Result<void, int>(Err<int>(0));
        //err.unwrapOrDefault(0);
    }
    {
        [[maybe_unused]] auto err = Result<void, void>(Err<void>());
        //err.unwrapOrDefault(0);
    }
}

TEST(ResultTest, unwrapOrElse)
{
    auto fn = [] (int const& i)
    {
        return i + 1;
    };

    // Test unwrapOrElse() Ok<T> and Err<E> where T,E is non void
    {
        auto ok = Result<int, int>(Ok<int>(0));
        ASSERT_EQ(ok.unwrapOrElse(fn), 0);
    }
    {
        auto err = Result<int, int>(Err<int>(0));
        ASSERT_EQ(err.unwrapOrElse(fn), 1);
    }

    // Commenting in unwrapOrElse() must lead to compilation errors
    {
        [[maybe_unused]] auto ok = Result<void, int>(Ok<void>());
        //ok.unwrapOrElse(fn);
    }
    {
        [[maybe_unused]] auto err = Result<void, int>(Err<int>(0));
        //err.unwrapOrElse(fn);
    }
    {
        [[maybe_unused]] auto ok = Result<int, void>(Ok<int>(0));
        //ok.unwrapOrElse();
    }
    {
        [[maybe_unused]] auto err = Result<int, void>(Err<void>());
        //err.unwrapOrElse();
    }
    {
        [[maybe_unused]] auto ok = Result<void, void>(Ok<void>());
        //ok.unwrapOrElse(fn);
    }
    {
        [[maybe_unused]] auto err = Result<void, void>(Err<void>());
        //err.unwrapOrElse(fn);
    }
}

TEST(ResultTest, implicitConversionOk)
{
    // Test implicit conversion of Ok<T> for all specializations
    {
        auto ok = implcitConvertOk<int, int>();
        ASSERT_TRUE(ok.isOk());
    }
    {
        auto ok = implcitConvertOk<void, int>();
        ASSERT_TRUE(ok.isOk());
    }
    {
        auto ok = implcitConvertOk<int, void>();
        ASSERT_TRUE(ok.isOk());
    }
    {
        auto ok = implcitConvertOk<void, void>();
        ASSERT_TRUE(ok.isOk());
    }
}

TEST(ResultTest, implicitConversionErr)
{
    // Test implicit conversion of Err<E> for all specializations
    {
        auto err = implcitConvertErr<int, int>();
        ASSERT_TRUE(err.isErr());
    }
    {
        auto err = implcitConvertErr<void, int>();
        ASSERT_TRUE(err.isErr());
    }
    {
        auto err = implcitConvertErr<int, void>();
        ASSERT_TRUE(err.isErr());
    }
    {
        auto err = implcitConvertErr<void, void>();
        ASSERT_TRUE(err.isErr());
    }
}

TEST(ResultTest, operatorEquality)
{
    {
        auto ok  = Result<void, void>(Ok<void>());
        auto err = Result<void, void>(Err<void>());

        ASSERT_EQ(ok == ok,  true);
        ASSERT_EQ(ok == err, false);
    }
    {
        auto ok   = Result<void, int>(Ok<void>());
        auto err0 = Result<void, int>(Err<int>(0));
        auto err1 = Result<void, int>(Err<int>(1));

        ASSERT_EQ(ok == ok,     true);
        ASSERT_EQ(err0 == err0, true);
        ASSERT_EQ(err1 == err1, true);

        ASSERT_EQ(ok == err0,   false);
        ASSERT_EQ(ok == err1,   false);
        ASSERT_EQ(err0 == ok,   false);
        ASSERT_EQ(err0 == err1, false);
        ASSERT_EQ(err1 == ok,   false);
        ASSERT_EQ(err1 == err0, false);
    }

    {
        auto ok0 = Result<int, void>(Ok<int>(0));
        auto ok1 = Result<int, void>(Ok<int>(1));
        auto err = Result<int, void>(Err<void>());

        ASSERT_EQ(ok0 == ok0, true);
        ASSERT_EQ(ok1 == ok1, true);
        ASSERT_EQ(err == err, true);

        ASSERT_EQ(ok0 == err, false);
        ASSERT_EQ(ok0 == ok1, false);
        ASSERT_EQ(ok1 == ok0, false);
        ASSERT_EQ(ok1 == err, false);
        ASSERT_EQ(err == ok0, false);
        ASSERT_EQ(err == ok1, false);
    }

        {
        auto ok0  = Result<int, int>(Ok<int>(0));
        auto ok1  = Result<int, int>(Ok<int>(1));
        auto err0 = Result<int, int>(Err<int>(0));
        auto err1 = Result<int, int>(Err<int>(1));

        ASSERT_EQ(ok0 == ok0,   true);
        ASSERT_EQ(ok1 == ok1,   true);
        ASSERT_EQ(err0 == err0, true);
        ASSERT_EQ(err1 == err1, true);

        ASSERT_EQ(ok0 == ok1,   false);
        ASSERT_EQ(ok0 == err0,  false);
        ASSERT_EQ(ok0 == err1,  false);
        ASSERT_EQ(ok1 == ok0,   false);
        ASSERT_EQ(ok1 == err0,  false);
        ASSERT_EQ(ok1 == err1,  false);
        ASSERT_EQ(err0 == ok0,  false);
        ASSERT_EQ(err0 == ok1,  false);
        ASSERT_EQ(err0 == err1, false);
        ASSERT_EQ(err1 == ok0,  false);
        ASSERT_EQ(err1 == ok1,  false);
        ASSERT_EQ(err1 == err0, false);
    }
}

TEST(ResultTest, operatorInequality)
{
    {
        auto ok  = Result<void, void>(Ok<void>());
        auto err = Result<void, void>(Err<void>());

        ASSERT_EQ(ok != ok,  false);
        ASSERT_EQ(ok != err, true);
    }
    {
        auto ok   = Result<void, int>(Ok<void>());
        auto err0 = Result<void, int>(Err<int>(0));
        auto err1 = Result<void, int>(Err<int>(1));

        ASSERT_EQ(ok != ok,     false);
        ASSERT_EQ(err0 != err0, false);
        ASSERT_EQ(err1 != err1, false);

        ASSERT_EQ(ok != err0,   true);
        ASSERT_EQ(ok != err1,   true);
        ASSERT_EQ(err0 != ok,   true);
        ASSERT_EQ(err0 != err1, true);
        ASSERT_EQ(err1 != ok,   true);
        ASSERT_EQ(err1 != err0, true);
    }

    {
        auto ok0 = Result<int, void>(Ok<int>(0));
        auto ok1 = Result<int, void>(Ok<int>(1));
        auto err = Result<int, void>(Err<void>());

        ASSERT_EQ(ok0 != ok0, false);
        ASSERT_EQ(ok1 != ok1, false);
        ASSERT_EQ(err != err, false);

        ASSERT_EQ(ok0 != err, true);
        ASSERT_EQ(ok0 != ok1, true);
        ASSERT_EQ(ok1 != ok0, true);
        ASSERT_EQ(ok1 != err, true);
        ASSERT_EQ(err != ok0, true);
        ASSERT_EQ(err != ok1, true);
    }

    {
        auto ok0  = Result<int, int>(Ok<int>(0));
        auto ok1  = Result<int, int>(Ok<int>(1));
        auto err0 = Result<int, int>(Err<int>(0));
        auto err1 = Result<int, int>(Err<int>(1));

        ASSERT_EQ(ok0 != ok0,   false);
        ASSERT_EQ(ok1 != ok1,   false);
        ASSERT_EQ(err0 != err0, false);
        ASSERT_EQ(err1 != err1, false);

        ASSERT_EQ(ok0 != ok1,   true);
        ASSERT_EQ(ok0 != err0,  true);
        ASSERT_EQ(ok0 != err1,  true);
        ASSERT_EQ(ok1 != ok0,   true);
        ASSERT_EQ(ok1 != err0,  true);
        ASSERT_EQ(ok1 != err1,  true);
        ASSERT_EQ(err0 != ok0,  true);
        ASSERT_EQ(err0 != ok1,  true);
        ASSERT_EQ(err0 != err1, true);
        ASSERT_EQ(err1 != ok0,  true);
        ASSERT_EQ(err1 != ok1,  true);
        ASSERT_EQ(err1 != err0, true);
    }
}
