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
#include <Math.hpp>

TEST(MathTest, isPowOfTwo)
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