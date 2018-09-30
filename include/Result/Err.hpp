/**
 * @file      Err.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Contains the error value of a failed result.
 * @copyright 2018 Simon Brummer. All rights reserved.\n
 *            This project is released under the BSD 3-Clause License.
 */

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

#ifndef ERR_HPP_20180923151521
#define ERR_HPP_20180923151521

namespace simons_lib::result
{

/**
 * @brief Type holding a failed result.
 * @tparam E   Type contained within the failed result.
 */
template<typename E>
class Err
{
public:
    /// @brief Type contained in a failed result.
    using ValueType = E;
    /// @brief Ref to type contained in a failed result.
    using Reference = ValueType &;
        /// @brief Const ref to type contained in a failed result.
    using ConstReference = ValueType const&;

    /**
     * @brief Constructs a failed Result.
     * @param[in] value   Error value contained within the failed result.
     */
    explicit Err(ValueType value)
        : m_value(std::move(value))
    {
    }

    /**
     * @brief Get contained value.
     * @returns Copy of contained value.
     */
    ValueType getValue() const
    {
        return m_value;
    }

    /**
     * @brief Get const reference to contained value.
     * @returns Const reference to contained value.
     */
    ConstReference getConstRef() const
    {
        return m_value;
    }

    /**
     * @brief Get reference to contained value.
     * @returns Reference to contained value.
     */
    Reference getRef()
    {
        return m_value;
    }

private:
    ValueType m_value;
};

/**
 * @brief Compare two failed outcomes for equality.
 * @tparam T   Type contained in a failed result.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if the contained values of @p lhs and @p rhs are equal, otherwise false.
 */
template<typename E>
bool operator == (Err<E> const& lhs, Err<E> const& rhs)
{
    return lhs.getConstRef() == rhs.getConstRef();
}

/**
 * @brief Compare two failed outcomes for inequality.
 * @tparam T   Type contained in a failed result.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if the contained values of @p lhs and @p rhs are not equal, otherwise false.
 */
template<typename E>
bool operator != (Err<E> const& lhs, Err<E> const& rhs)
{
    return !(lhs == rhs);
}
} // namespace simons_lib::result

#endif // ERR_HPP_20180923151521
