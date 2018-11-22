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
class Result
{
public:
    /// @brief Value type contained in successful results.
    using OkTypeValue = T;
    /// @brief Type holding a successful result.
    using OkType = Ok<OkTypeValue>;
    /// @brief Value type contained in faulty results.
    using ErrTypeValue = E;
    /// @brief Type holding a failed result.
    using ErrType = Err<ErrTypeValue>;
    /// @brief Type holding a either and successful or a failed result.
    using Outcome = std::variant<OkType, ErrType>;

    /**
     * @brief Construct Result.
     * @param[in] outcome   Either Ok<T> indicating as successful result
     *                      or Err<E> in case of a failed result.
     */
    explicit Result(Outcome outcome) noexcept
        : m_outcome(std::move(outcome))
        , m_fnBase(m_outcome)
        , m_fnOkNotVoid(m_outcome)
        , m_fnErrNotVoid(m_outcome)
        , m_fnAllNotVoid(m_outcome)
    {
    }

    /**
     * @brief Conversion Constructor. Converts Ok<T> implicitly to Result<T, E>.
     * @param[in] ok   Positive outcome to build result from.
     */
    Result(OkType ok) noexcept
        : Result(static_cast<Outcome>(ok))
    {
    }

    /**
     * @brief Conversion Constructor. Converts Err<E> implicitly to Result<T, E>.
     * @param[in] err   Negative outcome to build result.
     */
    Result(ErrType err) noexcept
        : Result(static_cast<Outcome>(err))
    {
    }

    /**
     * @brief Accessors to the internal variant holding the Results Outcome.
     * @returns const ref to internal outcome.
     */
    Outcome const& getOutcome(void) const
    {
        return m_fnBase.getOutcome();
    }

    /**
     * @brief Check if result contains a success value.
     * @returns true in case the Result contains a success, otherwise false.
     */
    bool isOk(void) const
    {
        return m_fnBase.isOk();
    }

    /**
     * @brief Check if result contains an error value.
     * @returns true in case the Result contains an error, otherwise false.
     */
    bool isErr(void) const
    {
        return m_fnBase.isErr();
    }

    /**
     * @brief Get stored success value.
     * @returns std::optional<T> holding the value stored in Ok<T>, if
     *          the result holds Ok<T>. Otherwise std::nullopt is returned.
     */
    std::optional<OkTypeValue> getOk(void) const
    {
        return m_fnOkNotVoid.getOk();
    }

    /**
     * @brief Get stored error value.
     * @returns std::optional<E> holding the value stored in Err<E>, if
     *          the result holds Err<E>. Otherwise std::nullopt is returned.
     */
    std::optional<ErrTypeValue> getErr(void) const
    {
        return m_fnErrNotVoid.getErr();
    }

    /**
     * @brief Get value stored in Ok<T> (held by the Result) directly.
     * @note Terminates application in case the result holds an Err<E>.
     */
    OkTypeValue unwrap(void) const
    {
        return m_fnOkNotVoid.unwrap();
    }

    /**
     * @brief Get value stored in Err<E> (held by the Result) directly.
     * @note Terminates application in case the result holds an Ok<T>.
     */
    ErrTypeValue unwrapErr(void) const
    {
        return m_fnErrNotVoid.unwrapErr();
    }

    /**
     * @brief Get value stored in Ok<T> (held by the Result) or return given default value.
     * @param[in] val   Default value if result holds Err<E> instead of Ok<T>.
     * @returns Value stored in Ok<T> or @p val.
     */
    OkTypeValue unwrapOrDefault(OkTypeValue const& val) const
    {
        return m_fnOkNotVoid.unwrapOrDefault(val);
    }

    /**
     * @brief Get value stored in Ok<T> or apply given function on the value stored on Err<T>.
     * @param[in] fn   Function to apply on value contained in Err<E> in case the result contains Err<E>.
     * @returns Value stored in Ok<T> or return value of @p fn.
     */
    OkTypeValue unwrapOrElse(std::function<OkTypeValue(ErrTypeValue const&)> fn) const
    {
        return m_fnAllNotVoid.unwrapOrElse(fn);
    }

private:
    Outcome                      m_outcome;
    detail::FuncBase<T, E>       m_fnBase;
    detail::FuncOkNotVoid<T, E>  m_fnOkNotVoid;
    detail::FuncErrNotVoid<T, E> m_fnErrNotVoid;
    detail::FuncAllNotVoid<T, E> m_fnAllNotVoid;
};

/**
 * @brief Alternative to exception based error handling.
 * @tparam E   Type associated with a failed Result.
 */
template<typename E>
class Result<void, E>
{
public:
    /// @brief Type holding a successful result.
    using OkType = Ok<void>;
    /// @brief Value type contained in faulty results.
    using ErrTypeValue = E;
    /// @brief Type holding a failed result.
    using ErrType = Err<ErrTypeValue>;
    /// @brief Type holding a either and successful or a failed result.
    using Outcome = std::variant<OkType, ErrType>;

    /**
     * @brief Construct Result.
     * @param[in] outcome   Either Ok<T> indicating as successful result
     *                      or Err<E> in case of a failed result.
     */
    explicit Result(Outcome outcome) noexcept
        : m_outcome(std::move(outcome))
        , m_fnBase(m_outcome)
        , m_fnErrNotVoid(m_outcome)
    {
    }

    /**
     * @brief Conversion Constructor. Converts Ok<T> implicitly to Result<T, E>.
     * @param[in] ok   Positive outcome to build result from.
     */
    Result(OkType ok) noexcept
        : Result(static_cast<Outcome>(ok))
    {
    }

    /**
     * @brief Conversion Constructor. Converts Err<E> implicitly to Result<T, E>.
     * @param[in] err   Negative outcome to build result.
     */
    Result(ErrType err) noexcept
        : Result(static_cast<Outcome>(err))
    {
    }

    /**
     * @brief Accessors to the internal variant holding the Results Outcome.
     * @returns const ref to internal outcome.
     */
    Outcome const& getOutcome(void) const
    {
        return m_fnBase.getOutcome();
    }

    /**
     * @brief Check if result contains a success value.
     * @returns true in case the Result contains a success, otherwise false.
     */
    bool isOk(void) const
    {
        return m_fnBase.isOk();
    }

    /**
     * @brief Check if result contains an error value.
     * @returns true in case the Result contains an error, otherwise false.
     */
    bool isErr(void) const
    {
        return m_fnBase.isErr();
    }

    /**
     * @brief Get stored error value.
     * @returns std::optional<E> holding the value stored in Err<E>, if
     *          the result holds Err<E>. Otherwise std::nullopt is returned.
     */
    std::optional<ErrTypeValue> getErr(void) const
    {
        return m_fnErrNotVoid.getErr();
    }

    /**
     * @brief Get value stored in Err<E> (held by the Result) directly.
     * @note Terminates application in case the result holds an Ok<T>.
     */
    ErrTypeValue unwrapErr(void) const
    {
        return m_fnErrNotVoid.unwrapErr();
    }

private:
    Outcome                         m_outcome;
    detail::FuncBase<void, E>       m_fnBase;
    detail::FuncErrNotVoid<void, E> m_fnErrNotVoid;
};

/**
 * @brief Alternative to exception based error handling.
 * @tparam T   Type associated with a successful Result.
 */
template<typename T>
class Result<T, void>
{
public:
    /// @brief Value type contained in successful results.
    using OkTypeValue = T;
    /// @brief Type holding a successful result.
    using OkType = Ok<OkTypeValue>;
    /// @brief Type holding a failed result.
    using ErrType = Err<void>;
    /// @brief Type holding a either and successful or a failed result.
    using Outcome = std::variant<OkType, ErrType>;

    /**
     * @brief Construct Result.
     * @param[in] outcome   Either Ok<T> indicating as successful result
     *                      or Err<E> in case of a failed result.
     */
    explicit Result(Outcome outcome) noexcept
        : m_outcome(std::move(outcome))
        , m_fnBase(m_outcome)
        , m_fnOkNotVoid(m_outcome)
    {
    }

    /**
     * @brief Conversion Constructor. Converts Ok<T> implicitly to Result<T, E>.
     * @param[in] ok   Positive outcome to build result from.
     */
    Result(OkType ok) noexcept
        : Result(static_cast<Outcome>(ok))
    {
    }

    /**
     * @brief Conversion Constructor. Converts Err<E> implicitly to Result<T, E>.
     * @param[in] err   Negative outcome to build result.
     */
    Result(ErrType err) noexcept
        : Result(static_cast<Outcome>(err))
    {
    }

    /**
     * @brief Accessors to the internal variant holding the Results Outcome.
     * @returns const ref to internal outcome.
     */
    Outcome const& getOutcome(void) const
    {
        return m_fnBase.getOutcome();
    }

    /**
     * @brief Check if result contains a success value.
     * @returns true in case the Result contains a success, otherwise false.
     */
    bool isOk(void) const
    {
        return m_fnBase.isOk();
    }

    /**
     * @brief Check if result contains an error value.
     * @returns true in case the Result contains an error, otherwise false.
     */
    bool isErr(void) const
    {
        return m_fnBase.isErr();
    }

    /**
     * @brief Get stored success value.
     * @returns std::optional<T> holding the value stored in Ok<T>, if
     *          the result holds Ok<T>. Otherwise std::nullopt is returned.
     */
    std::optional<OkTypeValue> getOk(void) const
    {
        return m_fnOkNotVoid.getOk();
    }

    /**
     * @brief Get value stored in Ok<T> (held by the Result) directly.
     * @note Terminates application in case the result holds an Err<E>.
     */
    OkTypeValue unwrap(void) const
    {
        return m_fnOkNotVoid.unwrap();
    }

    /**
     * @brief Get value stored in Ok<T> (held by the Result) or return given default value.
     * @param[in] val   Default value if result holds Err<E> instead of Ok<T>.
     * @returns Value stored in Ok<T> or @p val.
     */
    OkTypeValue unwrapOrDefault(OkTypeValue const& val) const
    {
        return m_fnOkNotVoid.unwrapOrDefault(val);
    }

private:
    Outcome                        m_outcome;
    detail::FuncBase<T, void>      m_fnBase;
    detail::FuncOkNotVoid<T, void> m_fnOkNotVoid;
};

/**
 * @brief Alternative to exception based error handling.
 */
template<>
class Result<void, void>
{
public:
    /// @brief Type holding a successful result.
    using OkType = Ok<void>;
    /// @brief Type holding a failed result.
    using ErrType = Err<void>;
    /// @brief Type holding a either and successful or a failed result.
    using Outcome = std::variant<OkType, ErrType>;

    /**
     * @brief Construct Result.
     * @param[in] outcome   Either Ok<T> indicating as successful result
     *                      or Err<E> in case of a failed result.
     */
    explicit Result(Outcome outcome) noexcept
        : m_outcome(std::move(outcome))
        , m_fnBase(m_outcome)
    {
    }

    /**
     * @brief Conversion Constructor. Converts Ok<T> implicitly to Result<T, E>.
     * @param[in] ok   Positive outcome to build result from.
     */
    Result(OkType ok) noexcept
        : Result(static_cast<Outcome>(ok))
    {
    }

    /**
     * @brief Conversion Constructor. Converts Err<E> implicitly to Result<T, E>.
     * @param[in] err   Negative outcome to build result.
     */
    Result(ErrType err) noexcept
        : Result(static_cast<Outcome>(err))
    {
    }

    /**
     * @brief Accessors to the internal variant holding the Results Outcome.
     * @returns const ref to internal outcome.
     */
    Outcome const& getOutcome(void) const
    {
        return m_fnBase.getOutcome();
    }

    /**
     * @brief Check if result contains a success value.
     * @returns true in case the Result contains a success, otherwise false.
     */
    bool isOk(void) const
    {
        return m_fnBase.isOk();
    }

    /**
     * @brief Check if result contains an error value.
     * @returns true in case the Result contains an error, otherwise false.
     */
    bool isErr(void) const
    {
        return m_fnBase.isErr();
    }

private:
    Outcome                      m_outcome;
    detail::FuncBase<void, void> m_fnBase;
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
    auto lhsIsOk = lhs.isOk();
    if (lhsIsOk == rhs.isOk())
    {
        using OkType = typename Result<T, E>::OkType;
        using ErrType = typename Result<T, E>::ErrType;

        if (lhsIsOk)
        {
            auto const& lhsOk = std::get<OkType>(lhs.getOutcome());
            auto const& rhsOk = std::get<OkType>(rhs.getOutcome());
            return (lhsOk == rhsOk);
        }
        auto const& lhsErr = std::get<ErrType>(lhs.getOutcome());
        auto const& rhsErr = std::get<ErrType>(rhs.getOutcome());
        return (lhsErr == rhsErr);
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
