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
#include "../DummyMutex.hpp"
#include "../Result.hpp"

namespace simons_lib::ringbuffer
{

template<typename T, std::size_t S, typename M = simons_lib::lock::DummyMutex>
class Ringbuffer
{
public:
    /// @brief Internally used container type.
    using ContainerType = std::array<T, S>;
    /// @brief Type contained in Ringbuffer.
    using ValueType = ContainerType::value_type;
    /// @brief Ref to type contained in Ringbuffer.
    using Reference = ContainerType::reference;
    /// @brief Const ref to type contained in Ringbuffer.
    using ConstReference = ContainerType::const_reference;
    /// @brief Type used to express the Ringbuffer sizes.
    using SizeType = ContainerType::size_type;
    /// @brief Type of supplied mutex.
    using MutexType = M;
    /// @brief Lock to use with given mutex.
    using LockType = simons_lib::lock::LockGuard<MutexType>;

    using ResultType = simons_lib::result::Result<T, char const *>;

    Ringbuffer()
        : m_rawBuf()
        , m_idxHead(0)
        , m_idxTail(0)
        , m_mutex()
        , m_isFull(0)
    {
    }

    /*
    Ringbuffer(std::initializer_list<ValueType> const& list)
    {
        for (auto const& node : list)
        {

        }
    }
    */

    ResultType front() const
    {
        return ResultType::ErrType("front() not implemented");
    }

    ResultType back() const
    {
        return ResultType::ErrType("back() not implemented");
    }

    bool empty() const
    {
        return (m_head == m_tail) && (!m_isFull);
    }

    SizeType size() const
    {
        return 0;
    }

    ResultType push(T const& val)
    {
        if (size() >= S)
        {
            return ResultType::ErrType("Ringbuffer: out of memory.");
        }

        m_rawBuf[m_head] = val;

        if (++m_head == S)
        {
            m_head = 0;
        }
    }

    ResultType pop()
    {
        return ResultType::ErrType("pop() not implemented");
    }

    ResultType emplace()
    {
        return ResultType::ErrType("emplace() not implemented");
    }

    void swap()
    {
    }

private:
    ContainerType     m_rawBuf;
    SizeType          m_head;
    SizeType          m_tail;
    bool              m_isFull;
    mutable MutexType m_mutex;
};

template<typename T, std::size_t S>
bool operator == (Ringbuffer<T, S> const& lhs, Ringbuffer<T, S> const& rhs)
{
    // TODO: Implement me
    return false;
}

template<typename T, std::size_t S>
bool operator == (Ringbuffer<T, S> const& lhs, Ringbuffer<T, S> const& rhs)
{
    return !(lhs == rhs);
}

} // simons_lib::ringbuffer

#endif // RINGBUFFER_IMPL_HPP_20181001091421