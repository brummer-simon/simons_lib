/**
 * @file      ModuloUnsignedImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Unsigned Integer implementing modulo arithmetic on each operator.
 * @copyright 2018 Simon Brummer. All rights reserved.
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

#ifndef MODULO_UNSIGNED_IMPL_HPP_20181004182318
#define MODULO_UNSIGNED_IMPL_HPP_20181004182318

#include <type_traits>
#include "UtilityFunctionsImpl.hpp"

namespace simons_lib::math
{

/**
 * @brief Unsigned following basic modular arithmetic operations.
 * @tparam V   Divisor applied implicitly on all arithmetic operations.
 *             Type of V can be any unsigned Integer.
 */
template<auto V>
class ModuloUnsigned
{
public:
    /// @brief Type of given unsigned Integer
    using UnsignedType = decltype(V);

    /// @brief Default Constructor.
    explicit ModuloUnsigned()
        : ModuloUnsigned(UnsignedType(0))
    {
    }

    /**
     * @brief Constructor.
     * @param[in] val   initial value for ModuloUnsigned.
     */
    explicit ModuloUnsigned(UnsignedType val)
        : m_val(mod(val, V))
    {
        // Perform some sanity checking
        static_assert(1 <= V);
        static_assert(std::is_unsigned<UnsignedType>::value);
    }

    /**
     * @brief Conversion given unsigned Type
     * @returns Value of ModuloUnsigned.
     */
    explicit operator UnsignedType () const
    {
        return m_val;
    }

    /**
     * @brief Add one from ModuloUnsigned.
     * @returns Ref to self.
     */
    ModuloUnsigned& operator ++ ()
    {
        // Handle overflow
        ++m_val;
        if (V <= m_val)
        {
            m_val = 0;
        }
        return *this;
    }

    /**
     * @brief Add assignment of Unsigned Integer
     * @param[in] rhs   Right hand side.
     * @returns Ref to self.
     */
    ModuloUnsigned& operator += (UnsignedType rhs)
    {
        while (rhs)
        {
            ++(*this);
            --rhs;
        }
        return *this;
    }

    /**
     * @brief Add assignment of ModuloUnsigned
     * @param[in] rhs   Right hand side.
     * @returns Ref to self.
     */
    ModuloUnsigned& operator += (ModuloUnsigned rhs)
    {
        return ((*this) += static_cast<UnsignedType>(rhs));
    }

    /**
     * @brief Subtract one from ModuloUnsigned.
     * @returns Ref to self.
     */
    ModuloUnsigned& operator -- ()
    {
        // Handle underflow
        if (m_val <= 0)
        {
            m_val = V;
        }
        --m_val;
        return *this;
    }

    /**
     * @brief Subtract assignment of Unsigned Integer
     * @param[in] rhs   Right hand side.
     * @returns Ref to self.
     */
    ModuloUnsigned& operator -= (UnsignedType rhs)
    {
        while (rhs)
        {
            --(*this);
            --rhs;
        }
        return *this;
    }

    /**
     * @brief Subtract assignment of ModuloUnsigned
     * @param[in] rhs   Right hand side.
     * @returns Ref to self.
     */
    ModuloUnsigned& operator -= (ModuloUnsigned rhs)
    {
        return ((*this) -= static_cast<UnsignedType>(rhs));
    }

private:
    UnsignedType m_val;
};

/**
 * @brief Add ModuloUnsigned and an unsigned.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns (lhs + rhs) % V.
 */
template<auto V>
ModuloUnsigned<V> operator + (ModuloUnsigned<V> const& lhs, decltype(V) const& rhs)
{
    return ModuloUnsigned(lhs) += rhs;
}

/**
 * @brief Add two ModuloUnsigned Objects.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns (lhs + rhs) % V.
 */
template<auto V>
ModuloUnsigned<V> operator + (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return lhs + static_cast<decltype(V)>(rhs);
}

/**
 * @brief Subtract ModuloUnsigned and an unsigned.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns (lhs - rhs) % V.
 */
template<auto V>
ModuloUnsigned<V> operator - (ModuloUnsigned<V> const& lhs, decltype(V) const& rhs)
{
    return ModuloUnsigned(lhs) -= rhs;
}

/**
 * @brief Subtract two ModuloUnsigned Objects from each other.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns (lhs - rhs) % V.
 */
template<auto V>
ModuloUnsigned<V> operator - (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return lhs - static_cast<decltype(V)>(rhs);
}

/**
 * @brief Compare two ModuloUnsigned for equality.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if @p lhs and @p rhs are equal, otherwise false.
 */
template<auto V>
bool operator == (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return (static_cast<decltype(V)>(lhs) == static_cast<decltype(V)>(rhs));
}

/**
 * @brief Compare two ModuloUnsigned for inequality.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if @p lhs and @p rhs are unequal, otherwise false.
 */
template<auto V>
bool operator != (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return (static_cast<decltype(V)>(lhs) != static_cast<decltype(V)>(rhs));
}

/**
 * @brief Compares @p lhs and @p rhs lexicographically.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if @p lhs < @p rhs, otherwise false.
 */
template<auto V>
bool operator < (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return (static_cast<decltype(V)>(lhs) < static_cast<decltype(V)>(rhs));
}

/**
 * @brief Compares @p lhs and @p rhs lexicographically.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if @p lhs <= @p rhs, otherwise false.
 */
template<auto V>
bool operator <= (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return (static_cast<decltype(V)>(lhs) <= static_cast<decltype(V)>(rhs));
}

/**
 * @brief Compares @p lhs and @p rhs lexicographically.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if @p lhs > @p rhs, otherwise false.
 */
template<auto V>
bool operator > (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return (static_cast<decltype(V)>(lhs) > static_cast<decltype(V)>(rhs));
}

/**
 * @brief Compares @p lhs and @p rhs lexicographically.
 * @tparam V   Type and Value of div factor of ModuloUnsigned.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if @p lhs >= @p rhs, otherwise false.
 */
template<auto V>
bool operator >= (ModuloUnsigned<V> const& lhs, ModuloUnsigned<V> const& rhs)
{
    return (static_cast<decltype(V)>(lhs) >= static_cast<decltype(V)>(rhs));
}
} // namespace simons_lib::math

#endif //  MODULO_UNSIGNED_IMPL_HPP_20181004182318
