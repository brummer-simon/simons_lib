/**
 * @file      RingbufferImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Generic fixed-sized ringbuffer.
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

#ifndef RINGBUFFER_IMPL_HPP_20181001091421
#define RINGBUFFER_IMPL_HPP_20181001091421

#include <array>
#include <initializer_list>
#include "../LockGuard.hpp"
#include "../NullTypes.hpp"
#include "../Result.hpp"
#include "../Math/ModuloUnsignedImpl.hpp"

namespace simons_lib::ringbuffer
{

// Draw Result and NullObj into local namespace
using namespace simons_lib::result;
using simons_lib::null_types::NullObj;

template<typename T, std::size_t S, typename M = simons_lib::null_types::NullMutex>
class Ringbuffer
{
public:
    /// @brief Internally used container type.
    using ContainerType = std::array<T, S>;
    /// @brief Type contained in Ringbuffer.
    using ValueType = typename ContainerType::value_type;
    /// @brief Ref to type contained in Ringbuffer.
    using Reference = typename ContainerType::reference;
    /// @brief Const ref to type contained in Ringbuffer.
    using ConstReference = typename ContainerType::const_reference;
    /// @brief Type used to express the Ringbuffer sizes.
    using SizeType = typename ContainerType::size_type;

private:
    /// @brief Type of supplied mutex.
    using MutexType = M;
    /// @brief Lock to use with given mutex.
    using LockType = simons_lib::lock::LockGuard<MutexType>;

public:
    /// @brief ErrorCodes returned as Result error type.
    enum class ErrorCodes
    {
        OutOfMemory = 1,
        BufferEmpty = 2,
        NoImpl      = 3
    };

    Ringbuffer()
        : m_rawBuf()
        , m_head(0)
        , m_tail(0)
        , m_size(0)
        , m_mutex()
    {
    }

    /* TODO: Add init list */

    bool empty() const
    {
        auto guard = LockType(m_mutex);
        return (m_size == 0);
    }

    SizeType size() const
    {
        auto guard = LockType(m_mutex);
        return m_size;
    }

    SizeType capacity() const
    {
        return S;
    }

    Result<void, ErrorCodes> push(T const& val)
    {
        // Check if there is enough room for an additional element.
        if (size() >= capacity())
        {
            return Result<void, ErrorCodes>(Err(ErrorCodes::OutOfMemory));
        }

        // Add Object to Buffer and increase head
        m_rawBuf[static_cast<SizeType>(m_head)] = val;
        ++m_head;

        if (m_head == m_tail)
        {
            m_isFull = true;
        }
        return Result<void, ErrorCodes>(Ok());
    }

    Result<void, ErrorCodes> pop()
    {
        return Result<void, ErrorCodes>(Err(ErrorCodes::NoImpl));
    }

    Result<ValueType, ErrorCodes> peek() const
    {
        if (empty())
        {
            return Result<ValueType, ErrorCodes>(Err(ErrorCodes::BufferEmpty));
        }
        return Result<ValueType, ErrorCodes>(Ok(m_rawBuf[static_cast<SizeType>(m_head - 1)]));
    }

private:
    ContainerType                       m_rawBuf;
    simons_lib::math::ModuloUnsigned<S> m_head;
    simons_lib::math::ModuloUnsigned<S> m_tail;
    SizeType                            m_size;
    mutable MutexType                   m_mutex;
};

template<typename T, std::size_t S>
bool operator == (Ringbuffer<T, S> const& lhs, Ringbuffer<T, S> const& rhs)
{
    // TODO: Implement me
    return false;
}

template<typename T, std::size_t S>
bool operator != (Ringbuffer<T, S> const& lhs, Ringbuffer<T, S> const& rhs)
{
    return !(lhs == rhs);
}

} // simons_lib::ringbuffer

#endif // RINGBUFFER_IMPL_HPP_20181001091421
