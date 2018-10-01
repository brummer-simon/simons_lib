/**
 * @file      StackImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Stack: Generic fixed-size Stack. Thread safety is configurable.
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

#ifndef STACKIMPL_HPP_20181121104928
#define STACKIMPL_HPP_20181121104928

#include <array>
#include <initializer_list>
#include "StackError.hpp"
#include "../Result.hpp"
#include "../LockGuard.hpp"
#include "../NullTypes/NullMutexImpl.hpp"

namespace simons_lib::stack
{

using simons_lib::result::Result;
using simons_lib::result::Ok;
using simons_lib::result::Err;

/**
 * @brief Type holding a failed result.
 * @tparam E   Type contained within the Stack.
 * @tparam S   Number of Elements of Type T the stack can store.
 */
template<typename T, std::size_t S>
class Stack
{
public:
    /// @brief Internally used container type.
    using ContainerType  = std::array<T, S>;
    /// @brief Type stored in the stack.
    using ValueType      = typename ContainerType::value_type;
    /// @brief Ref to type stored in the stack.
    using Reference      = typename ContainerType::reference;
    /// @brief Const ref to type stored in the stack.
    using ConstReference = typename ContainerType::const_reference;
    /// @brief Type related to Stack sizes.
    using SizeType       = typename ContainerType::size_type;

public:
    /**
     * @brief Construct empty stack.
     */
    explicit Stack() noexcept
    {
        static_assert(S > 0u, "Stack size must be > 0. Abort");
    }

    /**
     * @brief Construct stack with a given initializer list.
     * @param[in] initList   List used to initializer the stack.
     */
    explicit Stack(std::initializer_list<ValueType> initList) noexcept
        : Stack()
    {
        m_usage = std::min(m_container.size(), initList.size());

        for (auto i = 0u; i < m_usage; ++i)
        {
            m_container[i] = *(initList.begin() + i);
        }
    }

    /**
     * @brief Get stack capacity.
     * @returns Number of elements that can be stored.
     */
    constexpr SizeType capacity(void) const
    {
        return S;
    }

    /**
     * @brief Get current stack size.
     * @returns Number of stored elements.
     */
    SizeType size(void) const
    {
        return m_usage;
    }

    /**
     * @brief Test if the stack is empty.
     * @returns true if the stack is empty, otherwise false.
     */
    bool empty(void) const
    {
        return (m_usage == 0u);
    }

    /**
     * @brief Test if the stack is full.
     * @returns true if the stack is full, otherwise false.
     */
    bool full(void) const
    {
        return (m_usage >= capacity());
    }

    /**
     * @brief Push an Object onto the stack.
     * @param[in] data   the data to push onto the stack.
     * @returns Result holding Ok<void> on success. On failure, the Result
     *          contains Err<StackError>.
     */
    Result<void, StackError> push(ValueType&& data)
    {
        if (full())
        {
            return  Err<StackError>(StackError::IsFull);
        }
        else
        {
            m_container[m_usage++] = std::forward<ValueType>(data);
        }
        return Ok<void>();
    }

    /**
     * @brief Construct a object directly at the stack top.
     * @tparam Args   arguments to forward.
     * @param[in] args   Arguments forwarded to the object construction.
     * @returns Result holding Ok<void> on success. On failure, the Result
     *          contains Err<StackError>.
     */
    template<typename... Args>
    Result<void, StackError> emplace(Args&&... args)
    {
        if (full())
        {
            return  Err<StackError>(StackError::IsFull);
        }
        else
        {
            // The Object is already allocated -> Reuse location with placement new.
            new (&m_container[m_usage++]) ValueType(std::forward<Args>(args)...);
        }
        return Ok<void>();
    }

    /**
     * @brief Remove an Object from the Stack.
     * @returns Result holding Ok<void> on success. On failure, the Result
     *          contains Err<StackError>.
     */
    Result<void, StackError> pop(void)
    {
        if (empty())
        {
            return Err<StackError>(StackError::IsEmpty);
        }
        else
        {
            // Call destructor before this location is reused.
            m_container[m_usage--].~ValueType();
        }
        return Ok<void>();
    }

    /**
     * @brief Get const ref to the top of the stack.
     * @returns Result holding Ok<ConstReference> on success.
     *          On failure, the Result contains Err<StackError>.
     */
    Result<ConstReference, StackError> ctop(void) const
    {
        if (empty())
        {
            return Err<StackError>(StackError::IsEmpty);
        }
        return Ok<ConstReference>(m_container[m_usage - 1]);
    }

    /**
     * @brief Get ref to the top of the stack.
     * @returns Result holding Ok<ConstReference> on success.
     *          On failure, the Result contains Err<StackError>.
     */
    Result<Reference, StackError> top(void)
    {
        if (empty())
        {
            return Err<StackError>(StackError::IsEmpty);
        }
        return Ok<Reference>(m_container[m_usage - 1]);
    }

private:
    ContainerType m_container = ContainerType();
    SizeType      m_usage = 0u;
};
} // namespace simon_lib::stack

#endif // STACKIMPL_HPP_20181121104928
