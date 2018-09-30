/**
 * @file      Detail.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Implementation details of Result.
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

/**
 * @cond DO_NOT_DOCUMENT
 * @note Documentation for this file is suppressed to avoid
 *       polluting the generated documentation with internal details.
 */

#ifndef DETAIL_HPP_20180923151521
#define DETAIL_HPP_20180923151521

#include <optional>
#include <functional>
#include "Ok.hpp"
#include "Err.hpp"

#include "../Defines.hpp"
#ifndef SIMONS_LIB_DISABLE_PRINTS
#include <cstdio>
#endif
#ifndef SIMONS_LIB_DISABLE_EXIT
#include <cstdlib>
#endif

namespace simons_lib::result::detail
{
// @Note: As soon as this function is called, the program is
//        in a unrecoverable error state.
[[noreturn]] void abort([[maybe_unused]] char const *msg)
{
#ifndef SIMONS_LIB_DISABLE_PRINTS
    puts(msg);
#endif
#ifndef SIMONS_LIB_DISABLE_EXIT
    exit(EXIT_FAILURE);
#else
    while (1)
    {
    }
#endif
}

template<typename T, typename E>
struct IsVisitor
{
    bool operator () (T const&) const
    {
        return true;
    }

    bool operator () (E const&) const
    {
        return false;
    }
};

template<typename T, typename E>
struct GetVisitor
{
    using ReturnType = typename T::ValueType;

    std::optional<ReturnType> operator () (T const& val) const
    {
        return val.getValue();
    }

    std::optional<ReturnType> operator () (E const&) const
    {
        return std::nullopt;
    }
};

template<typename T, typename E>
struct UnwrapVisitor
{
    using ReturnType = typename T::ValueType;
    using ErrorType = typename E::ValueType;
    using FuncType = std::function<ReturnType(ErrorType const&)>;

    UnwrapVisitor(FuncType f)
        : m_f(f)
    {
    }

    ReturnType operator () (T const& val) const
    {
        return val.getValue();
    }

    ReturnType operator () (E const& val) const
    {
        return m_f(val.getConstRef());
    }

    FuncType m_f;
};

} // namespace simons_lib::result::detail
#endif // DETAIL_HPP_20180923151521

/**
 * @endcond DO_NOT_DOCUMENT
 */
