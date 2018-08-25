/**
 * @file      CachedCallable.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Simple cache for results of callables.
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

#ifndef CACHED_CALLABLE_HPP_20180825084201
#define CACHED_CALLABLE_HPP_20180825084201

#include <functional>
#include <optional>

namespace simons_lib::cached_callable
{

/**
 * @brief Simple cache for results returned by callable objects.
 * @tparam result_type   The cached result type.
 */
template<typename result_type>
class CachedCallable
{
public:
    /**
     * @brief Type of stores callable object. 
     */
    using callable_type = std::function<result_type(void)>;

    /**
     * @brief Constructor.
     * @param[in] callable   Callable object those results should be cached.
     */
    CachedCallable(callable_type callable) noexcept
        : m_callable(callable)
        , m_result()
    {
    }

    /**
     * @brief Get cached result.
     * @note In case the cache holds currently no result, the stored
     *       callable is executed first and its result is stored.
     * @returns A copy of the cached result.
     */
    result_type operator ()(void)
    {
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
        m_result.reset();
    }

private:
    callable_type              m_callable;
    std::optional<result_type> m_result;
};

} // namespace simons_lib::cached_callable

#endif // CACHED_CALLABLE_HPP_20180825084201
