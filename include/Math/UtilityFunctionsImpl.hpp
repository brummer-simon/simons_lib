/**
 * @file      UtilityFunctionsImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Small collections of math related utility functions.
 * @copyright 2018 Simon Brummer. All rights reserved.\n
 *            This project is released under the GNU Lesser General Public License.
 */

/*
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

#ifndef UTILITY_FUNCTIONS_IMPL_HPP_20180923091648
#define UTILITY_FUNCTIONS_IMPL_HPP_20180923091648

#include <type_traits>

namespace simons_lib::math
{

/**
 * @brief Test if given integer is a power of two.
 * @tparam    intType   Type of @p i. Must be an unsigned integer.
 * @param[in] i         The value to test.
 * @returns   true if @p i as a power of two, otherwise false.
 */
template<typename intType>
constexpr bool isPowOfTwo(intType i)
{
    static_assert(std::is_unsigned<intType>::value, "Type has to be an unsigned integer");

    auto bitCnt = 0;
    while (i) 
    {
        if (i & 1)
        {
            ++bitCnt;
        }
        i >>= 1;
    }
    return (bitCnt == 1);
}

} // namespace simons_lib::math

#endif // UTILITY_FUNCTIONS_IMPL_HPP_20180923091648