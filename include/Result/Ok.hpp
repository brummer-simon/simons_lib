/**
 * @file      Ok.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Contains the value of a successful result.
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

#ifndef OK_HPP_20180923151521
#define OK_HPP_20180923151521

#include <type_traits>

namespace simons_lib::result
{

/**
 * @brief Type holding a successful result.
 * @tparam T   Type contained within the successful result.
 */
template<typename T>
class Ok
{
public:
    /// @brief Type contained in a successful result.
    using ValueType = T;
    /// @brief Ref to type contained in a successful result.
    using Reference = ValueType &;
    /// @brief Const ref to type contained in a successful result.
    using ConstReference = ValueType const&;

    /**
     * @brief Construct successful Result with default value type.
     * @note Given T must be no-throw default constructible.
     */
    explicit Ok(void) noexcept
        : m_value()
    {
        static_assert(std::is_nothrow_default_constructible<ValueType>::value);
    }

    /**
     * @brief Constructs a successful Result.
     * @note Type of @p value must be either no-throw-move-construct able
     *       or no-throw-copy-construct able.
     * @param[in] value   Value contained within the successful result.
     */
    explicit Ok(ValueType&& value) noexcept
        : m_value(std::forward<decltype(value)>(value))
    {
        static_assert( std::is_nothrow_move_constructible<ValueType>::value
                    || std::is_nothrow_copy_constructible<ValueType>::value
                     );
    }

    /**
     * @brief Get contained value.
     * @returns Copy of contained value.
     */
    ValueType getValue(void) const noexcept
    {
        return m_value;
    }

    /**
     * @brief Get const reference to contained value.
     * @returns Const reference to contained value.
     */
    ConstReference getConstRef(void) const noexcept
    {
        return m_value;
    }

    /**
     * @brief Get reference to contained value.
     * @returns Reference to contained value.
     */
    Reference getRef(void) noexcept
    {
        return m_value;
    }

private:
    ValueType m_value;
};

/**
 * @brief Type indicating a successful Result but contains no value.
 */
template <>
class Ok<void>
{
};

/**
 * @brief Compare two successful outcomes for equality.
 * @tparam T   Type contained in a successful result.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if the contained values of @p lhs and @p rhs are equal, otherwise false.
 */
template<typename T>
bool operator == (Ok<T> const& lhs, Ok<T> const& rhs)
{
    if constexpr (std::is_void<T>::value)
    {
        return true;
    }
    else
    {
        return lhs.getConstRef() == rhs.getConstRef();
    }
}

/**
 * @brief Compare two successful outcomes for inequality.
 * @tparam T   Type contained in a successful result.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if the contained values of @p lhs and @p rhs are not equal, otherwise false.
 */
template<typename T>
bool operator != (Ok<T> const& lhs, Ok<T> const& rhs)
{
    return !(lhs == rhs);
}
} // namespace simons_lib::result

#endif // OK_HPP_20180923151521
