/**
 * @file      UtilityFunctionsImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Small collections of math related utility functions.
 * @copyright 2018 Simon Brummer. All rights reserved.\n
 *            This project is released under the BSD 3-Clause License.
 */

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

#ifndef UTILITY_FUNCTIONS_IMPL_HPP_20180923091648
#define UTILITY_FUNCTIONS_IMPL_HPP_20180923091648

#include <type_traits>
#include "../Defines.hpp"

namespace simons_lib::math
{
/**
 * @brief Test if given integer is a power of two.
 * @tparam    T   Type of @p i. Must be an unsigned integer.
 * @param[in] i   The value to test.
 * @returns   true if @p i as a power of two, otherwise false.
 */
template<typename T>
constexpr bool isPowOfTwo(T i)
{
    static_assert(std::is_unsigned<T>::value);

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

/// @brief Tag type: Use normal % operator in mod()
struct ModAlgoOperatorMod {};
/// @brief Tag type: Use subtraction loop in mod()
struct ModAlgoLoop {};

/**
 * @brief Configurable modulo operator for unsigned types.
 * @tparam    T   Type of @p i. Must be an unsigned integer.
 * @tparam    Algo   Algorithm to use in function.
 * @param[in] lhs   Left hand side.
 * @param[in] rhs   Right hand side.
 * @returns   @p lhs % @p rhs.
 */
#ifndef SIMONS_LIB_DISABLE_OPERATOR_MOD
template<typename T, typename Algo = ModAlgoOperatorMod>
#else
template<typename T, typename Algo = ModAlgoLoop>
#endif
constexpr T mod (T const& lhs, T const& rhs)
{
    static_assert(std::is_unsigned<T>::value);

    if constexpr (std::is_same<Algo, ModAlgoOperatorMod>::value)
    {
        return lhs % rhs;
    }

    if constexpr (std::is_same<Algo, ModAlgoLoop>::value)
    {
        auto tmp = lhs;
        while (rhs <= tmp)
        {
            tmp -= rhs;
        }
        return tmp;
    }
}

} // namespace simons_lib::math

#endif // UTILITY_FUNCTIONS_IMPL_HPP_20180923091648

