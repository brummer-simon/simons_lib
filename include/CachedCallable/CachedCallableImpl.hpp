/**
 * @file      CachedCallableImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Simple cache for callable results.
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

#ifndef CACHED_CALLABLE_IMPL_HPP_20180825084201
#define CACHED_CALLABLE_IMPL_HPP_20180825084201

#include <functional>
#include <optional>
#include "../LockGuard.hpp"
#include "../DummyMutex.hpp"

namespace simons_lib::cached_callable
{

using simons_lib::lock::DummyMutex;
using simons_lib::lock::LockGuard;

/**
 * @brief Simple cache for results returned by callable objects.
 * @tparam T   The cached result type.
 * @tparam M   Internally used mutex type (defaults to DummyMutex).
 *             If thread safety is required supply a mutex of your choice.
 */
template<typename T, typename M = DummyMutex>
class CachedCallable
{
public:
    /// @brief Type the stored callable return value.
    using ResultType = T;
    /// @brief Type of supplied mutex.
    using MutexType = M;
    /// @brief Type of stored callable object.
    using CallableType = std::function<ResultType(void)>;

    /**
     * @brief Constructor.
     * @param[in] callable   Callable object those results should be cached.
     */
    CachedCallable(CallableType callable) noexcept
        : m_callable(callable)
        , m_result()
        , m_mutex()
    {
    }

    /**
     * @brief Get cached result.
     * @note In case the cache holds currently no result, the stored
     *       callable is executed first and its result is stored.
     * @returns A copy of the cached result.
     */
    ResultType operator ()(void)
    {
        auto guard = LockGuard<MutexType>(m_mutex);
        if (!m_result)
        {
            m_result = m_callable();
        }
        return *m_result;
    }

    /**
     * @brief Discard the currently cached result.
     * @note After this calling this method, the stored callable
     *       is always re-evaluated on calling operator () (void)
     */
    void reset(void)
    {
        auto guard = LockGuard<MutexType>(m_mutex);
        m_result.reset();
    }

private:
    CallableType              m_callable;
    std::optional<ResultType> m_result;
    MutexType                 m_mutex;
};

} // namespace simons_lib::cached_callable

#endif // CACHED_CALLABLE_IMPL_HPP_20180825084201
