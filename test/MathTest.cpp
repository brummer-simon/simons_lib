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
#include <Math.hpp>

using simons_lib::math::ModuloUnsigned;

TEST(ModuloUnsignedTest, Constructors)
{
    // Test Default Constructor
    ASSERT_EQ(static_cast<unsigned>(ModuloUnsigned<1u>()), 0u);
    ASSERT_EQ(static_cast<unsigned>(ModuloUnsigned<2u>()), 0u);
    ASSERT_EQ(static_cast<unsigned>(ModuloUnsigned<3u>()), 0u);

    // Test Constructor
    ASSERT_EQ(static_cast<unsigned>(ModuloUnsigned<1u>(1u)), 0u);
    ASSERT_EQ(static_cast<unsigned>(ModuloUnsigned<2u>(1u)), 1u);
    ASSERT_EQ(static_cast<unsigned>(ModuloUnsigned<2u>(3u)), 1u);

    // Play around
    ASSERT_EQ( static_cast<unsigned>(ModuloUnsigned<128u>(0u))
             , static_cast<unsigned>(ModuloUnsigned<128u>(128u))
             );
    ASSERT_EQ( static_cast<unsigned>(ModuloUnsigned<128u>(127u))
             , static_cast<unsigned>(ModuloUnsigned<128u>(255u))
             );
    ASSERT_EQ( static_cast<unsigned>(ModuloUnsigned<128u>(129u))
             , static_cast<unsigned>(ModuloUnsigned<128u>(257u))
             );
}

TEST(ModuloUnsignedTest, prefix_plusplus)
{
    // Test Normal Operation
    ASSERT_EQ(++ModuloUnsigned<128u>(0u), ModuloUnsigned<128u>(1u));
    ASSERT_EQ(++++ModuloUnsigned<128u>(0u), ModuloUnsigned<128u>(2u));
    ASSERT_EQ(++++++ModuloUnsigned<128u>(0u), ModuloUnsigned<128u>(3u));
    ASSERT_EQ(++++++++ModuloUnsigned<128u>(0u), ModuloUnsigned<128u>(4u));

    // Test Overflow
    ASSERT_EQ(++ModuloUnsigned<128u>(127u), ModuloUnsigned<128u>(0u));
}

TEST(ModuloUnsignedTest, operator_assign_plus)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += 1u, ModuloUnsigned<128u>(1u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += 2u, ModuloUnsigned<128u>(2u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += 3u, ModuloUnsigned<128u>(3u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += 4u, ModuloUnsigned<128u>(4u));

    // Test Overflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += 128, ModuloUnsigned<128u>(0u));
}

TEST(ModuloUnsignedTest, operator_assign_plus_ModuloUnsigned)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += ModuloUnsigned<128u>(1u), ModuloUnsigned<128u>(1u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += ModuloUnsigned<128u>(2u), ModuloUnsigned<128u>(2u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += ModuloUnsigned<128u>(3u), ModuloUnsigned<128u>(3u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += ModuloUnsigned<128u>(4u), ModuloUnsigned<128u>(4u));

    // Test Overflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) += ModuloUnsigned<128u>(128), ModuloUnsigned<128u>(0u));
}

TEST(ModuloUnsignedTest, operator_plus)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + 1u, ModuloUnsigned<128u>(1u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + 2u, ModuloUnsigned<128u>(2u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + 3u, ModuloUnsigned<128u>(3u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + 4u, ModuloUnsigned<128u>(4u));

    // Test Overflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + 128, ModuloUnsigned<128u>(0u));
}

TEST(ModuloUnsignedTest, operator_plus_ModuloUnsigned)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + ModuloUnsigned<128u>(1u), ModuloUnsigned<128u>(1u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + ModuloUnsigned<128u>(2u), ModuloUnsigned<128u>(2u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + ModuloUnsigned<128u>(3u), ModuloUnsigned<128u>(3u));
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + ModuloUnsigned<128u>(4u), ModuloUnsigned<128u>(4u));

    // Test Overflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) + ModuloUnsigned<128u>(128u), ModuloUnsigned<128u>(0u));
}

TEST(ModuloUnsignedTest, prefix_minusminus)
{
    // Test Normal Operation
    ASSERT_EQ(--ModuloUnsigned<128u>(127u), ModuloUnsigned<128u>(126u));
    ASSERT_EQ(----ModuloUnsigned<128u>(127u), ModuloUnsigned<128u>(125u));
    ASSERT_EQ(------ModuloUnsigned<128u>(127u), ModuloUnsigned<128u>(124u));
    ASSERT_EQ(--------ModuloUnsigned<128u>(127u), ModuloUnsigned<128u>(123u));

    // Test Underflow
    ASSERT_EQ(--ModuloUnsigned<128u>(0u), ModuloUnsigned<128u>(127u));
}

TEST(ModuloUnsignedTest, operator_assign_minus)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= 1, ModuloUnsigned<128u>(126u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= 2, ModuloUnsigned<128u>(125u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= 3, ModuloUnsigned<128u>(124u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= 4, ModuloUnsigned<128u>(123u));

    // Test Underflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) -= 1, ModuloUnsigned<128u>(127u));
}

TEST(ModuloUnsignedTest, operator_assign_minus_ModuloUnsgined)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= ModuloUnsigned<128u>(1), ModuloUnsigned<128u>(126u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= ModuloUnsigned<128u>(2), ModuloUnsigned<128u>(125u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= ModuloUnsigned<128u>(3), ModuloUnsigned<128u>(124u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) -= ModuloUnsigned<128u>(4), ModuloUnsigned<128u>(123u));

    // Test Underflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) -= ModuloUnsigned<128u>(1), ModuloUnsigned<128u>(127u));
}

TEST(ModuloUnsignedTest, operator_minus)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - 1, ModuloUnsigned<128u>(126u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - 2, ModuloUnsigned<128u>(125u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - 3, ModuloUnsigned<128u>(124u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - 4, ModuloUnsigned<128u>(123u));

    // Test Underflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) - 1, ModuloUnsigned<128u>(127u));
}

TEST(ModuloUnsignedTest, operator_minus_ModuloUnsigned)
{
    // Test Normal Operation
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - ModuloUnsigned<128u>(1), ModuloUnsigned<128u>(126u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - ModuloUnsigned<128u>(2), ModuloUnsigned<128u>(125u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - ModuloUnsigned<128u>(3), ModuloUnsigned<128u>(124u));
    ASSERT_EQ(ModuloUnsigned<128u>(127u) - ModuloUnsigned<128u>(4), ModuloUnsigned<128u>(123u));

    // Test Underflow
    ASSERT_EQ(ModuloUnsigned<128u>(0u) - ModuloUnsigned<128u>(1), ModuloUnsigned<128u>(127u));
}

TEST(ModuloUnsignedTest, operator_equality)
{
    ASSERT_EQ(ModuloUnsigned<16u>(0u) == ModuloUnsigned<16u>(16u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(15u) == ModuloUnsigned<16u>(31u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) == ModuloUnsigned<16u>(33u), true);

    ASSERT_EQ(ModuloUnsigned<16u>(0u) == ModuloUnsigned<16u>(33u), false);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) == ModuloUnsigned<16u>(34u), false);
    ASSERT_EQ(ModuloUnsigned<16u>(2u) == ModuloUnsigned<16u>(35u), false);
}

TEST(ModuloUnsignedTest, operator_inequality)
{
    ASSERT_EQ(ModuloUnsigned<16u>(0u) != ModuloUnsigned<16u>(1u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) != ModuloUnsigned<16u>(2u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(2u) != ModuloUnsigned<16u>(3u), true);

    ASSERT_EQ(ModuloUnsigned<16u>(0u) != ModuloUnsigned<16u>(16u), false);
    ASSERT_EQ(ModuloUnsigned<16u>(15u) != ModuloUnsigned<16u>(31u), false);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) != ModuloUnsigned<16u>(33u), false);
}

TEST(ModuloUnsignedTest, operators_compare)
{
    // Test: <
    ASSERT_EQ(ModuloUnsigned<16u>(0u) <  ModuloUnsigned<16u>(1u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) <  ModuloUnsigned<16u>(0u), false);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) <  ModuloUnsigned<16u>(1u), false);

    // Test: <=
    ASSERT_EQ(ModuloUnsigned<16u>(0u) <= ModuloUnsigned<16u>(0u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(0u) <= ModuloUnsigned<16u>(1u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) <= ModuloUnsigned<16u>(0u), false);

    // Test: >
    ASSERT_EQ(ModuloUnsigned<16u>(1u) >  ModuloUnsigned<16u>(0u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(0u) >  ModuloUnsigned<16u>(1u), false);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) >  ModuloUnsigned<16u>(1u), false);
    // Test: >=
    ASSERT_EQ(ModuloUnsigned<16u>(0u) >= ModuloUnsigned<16u>(0u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(1u) >= ModuloUnsigned<16u>(0u), true);
    ASSERT_EQ(ModuloUnsigned<16u>(0u) >= ModuloUnsigned<16u>(1u), false);
}

TEST(UtilityFunctionsTest, mod)
{
    // Test some trivial cases
    ASSERT_EQ(simons_lib::math::mod(0u, 1u), 0u);
    ASSERT_EQ(simons_lib::math::mod(1u, 1u), 0u);
    ASSERT_EQ(simons_lib::math::mod(2u, 1u), 0u);

    ASSERT_EQ(simons_lib::math::mod(0u, 2u), 0u);
    ASSERT_EQ(simons_lib::math::mod(1u, 2u), 1u);
    ASSERT_EQ(simons_lib::math::mod(2u, 2u), 0u);
    ASSERT_EQ(simons_lib::math::mod(3u, 2u), 1u);

    ASSERT_EQ(simons_lib::math::mod(0u, 64u), simons_lib::math::mod(128u, 64u));
    ASSERT_EQ(simons_lib::math::mod(1u, 64u), simons_lib::math::mod(129u, 64u));
    ASSERT_EQ(simons_lib::math::mod(2u, 64u), simons_lib::math::mod(130u, 64u));
}

TEST(UtilityFunctionsTest, isPowOfTwo)
{
    // Test for all powers of two in uint64_t. Result must be true.
    for (auto i = 0; i < 64; ++i)
    {
        ASSERT_EQ(true, simons_lib::math::isPowOfTwo(std::uint64_t(1ll << i)));
    }

    // Test for other values. Result must be false.
    for (auto i = 0; i < 62; ++i)
    {
        ASSERT_EQ(false, simons_lib::math::isPowOfTwo(std::uint64_t(5ll << i)));
    }
}

