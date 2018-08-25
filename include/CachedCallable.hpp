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

#ifndef CACHED_CALLABLE_HPP_20180825084201
#define CACHED_CALLABLE_HPP_20180825084201

#include <functional>
#include <optional>

namespace simons_lib::cached_callable
{

template<typename result_type>
class CachedCallable
{
public:
    using callable_type = std::function<result_type(void)>;

    CachedCallable(callable_type callable) noexcept
        : m_callable(callable)
        , m_result()
    {
    }

    result_type operator ()(void)
    {
        if (!m_result)
        {
            m_result = m_callable();
        }
        return *m_result;
    }

    void reset(void)
    {
        m_result.reset();
    }

private:
    callable_type              m_callable;
    std::optional<result_type> m_result;
};

} // simons_lib::cached_callable

#endif // CACHED_CALLABLE_HPP_20180825084201