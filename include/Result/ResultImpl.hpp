/**
 * @file      ResultImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Alternative to exception based error handling. Inspired by Rusts "Result".
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

#ifndef RESULT_IMPL_HPP_20180923151521
#define RESULT_IMPL_HPP_20180923151521

#include <variant>
#include <optional>
#include "Ok.hpp"
#include "Err.hpp"
#include "Detail.hpp"

namespace simons_lib::result
{

/**
 * @brief Alternative to exception based error handling.
 * @tparam T   Type associated with a successful Result.
 * @tparam E   Type associated with a failed Result.
 */
template<typename T, typename E>
class [[nodiscard]] Result
{
public:
    /// @brief Value type contained in successful results.
    using OkValueType = T;
    /// @brief Value type contained in faulty results.
    using ErrValueType = E;
    /// @brief Type holding a successful result.
    using OkType = Ok<OkValueType>;
    /// @brief Type holding a failed result.
    using ErrType = Err<ErrValueType>;
    /// @brief Type holding a either and successful or a failed result.
    using OutcomeType = std::variant<OkType, ErrType>;

    /**
     * @brief Construct Result.
     * @param[in] result   Either Ok<T> indicating as successful result
     *                     or Err<E> in case of a failed result.
     */
    explicit Result(OutcomeType result)
        : m_result(std::move(result))
    {
    }

    /**
     * @brief Check if result contains a success value.
     * @returns true in case the Result contains a success, otherwise false.
     */
    bool isOk() const
    {
        return std::visit(detail::IsVisitor<OkType, ErrType>(), m_result);
    }

    /**
     * @brief Check if result contains an error value.
     * @returns true in case the Result contains an error, otherwise false.
     */
    bool isErr() const
    {
        return std::visit(detail::IsVisitor<ErrType, OkType>(), m_result);
    }

    /**
     * @brief Get stored success value.
     * @returns std::optional<T> holding the value stored in Ok<T>, if
     *          the result holds Ok<T>. Otherwise std::nullopt is returned.
     */
    std::optional<OkValueType> getOk() const
    {
        return std::visit(detail::GetVisitor<OkType, ErrType>(), m_result);
    }

    /**
     * @brief Get stored error value.
     * @returns std::optional<E> holding the value stored in Err<E>, if
     *          the result holds Err<E>. Otherwise std::nullopt is returned.
     */
    std::optional<ErrValueType> getErr() const
    {
        return std::visit(detail::GetVisitor<ErrType, OkType>(), m_result);
    }

    /**
     * @brief Get value stored in Ok<T> (held by the Result) directly.
     * @note Terminates application in case the result holds an Err<E>.
     */
    OkValueType unwrap() const
    {
        auto fn = [] (ErrValueType const&) -> OkValueType
        {
            detail::abort("Critical Error: unwrap() contained Err<T>");
        };
        return std::visit(detail::UnwrapVisitor<OkType, ErrType>(fn), m_result);
    }

    /**
     * @brief Get value stored in Err<E> (held by the Result) directly.
     * @note Terminates application in case the result holds an Ok<T>.
     */
    ErrValueType unwrapErr() const
    {
        auto fn = [] (OkValueType const&) -> ErrValueType
        {
            detail::abort("Critical Error: unwrapErr() contained Ok<T>");
        };
        return std::visit(detail::UnwrapVisitor<ErrType, OkType>(fn), m_result);
    }

    /**
     * @brief Get value stored in Ok<T> (held by the Result) or return given default value.
     * @param[in] val   Default value if result holds Err<E> instead of Ok<T>.
     * @returns Value stored in Ok<T>  or @p val.
     */
    OkValueType unwrapOrDefault(OkValueType const& val) const
    {
        auto fn = [&val] (auto const&)
        {
            return val;
        };
        return std::visit(detail::UnwrapVisitor<OkType, ErrType>(fn), m_result);
    }

    /**
     * @brief Get value stored in Ok<T> or apply given function on the value stored on Err<T>.
     * @param[in] fn   Function to apply on value contained in Err<E> in case the result
     *                 contains Err<E>.
     * @returns Value stored in Ok<T> or return value of @p fn.
     */
    OkValueType unwrapOrElse(std::function<OkValueType(ErrValueType const&)> fn) const
    {
        return std::visit(detail::UnwrapVisitor<OkType, ErrType>(fn), m_result);
    }
private:
    OutcomeType m_result;
};

/**
 * @brief Compare two results for equality.
 * @tparam T   Type contained in a successful result.
 * @tparam E   Type contained in a failed result.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if the contained values of @p lhs and @p rhs are equal, otherwise false.
 */
template<typename T, typename E>
bool operator == (Result<T, E> const& lhs, Result<T, E> const& rhs)
{
    auto lhsOk = lhs.isOk();
    if (lhsOk == rhs.isOk())
    {
        if (lhsOk)
        {
            return (lhs.unwrap() == rhs.unwrap());
        }
        return (lhs.unwrapErr() == rhs.unwrapErr());
    }
    return false;
}

/**
 * @brief Compare two results for inequality.
 * @tparam T   Type contained in a successful result.
 * @tparam E   Type contained in a failed result.
 * @param[in] lhs   left hand side of operator.
 * @param[in] rhs   right hand side of operator.
 * @returns true if the contained values of @p lhs and @p rhs are not equal, otherwise false.
 */
template<typename T, typename E>
bool operator != (Result<T, E> const& lhs, Result<T, E> const& rhs)
{
    return !(lhs == rhs);
}
} // namespace simons_lib::result
#endif // RESULT_IMPL_HPP_20180923151521
