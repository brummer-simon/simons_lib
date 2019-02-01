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

#include <gtest/gtest.h>
#include "Stack.hpp"

using namespace simons_lib::stack;

TEST(StackTest, capacity)
{
    {
        auto obj = Stack<int, 5>();
        static_assert(obj.capacity() == 5);
    }
}

TEST(StackTest, empty)
{
    {
        auto obj = Stack<int, 5>();
        ASSERT_TRUE(obj.empty());
    }
    {
        auto obj = Stack<int, 5>{1};
        ASSERT_FALSE(obj.empty());
    }
}

TEST(StackTest, full)
{
    {
        auto obj = Stack<int, 5>{1, 2, 3, 4 ,5};
        ASSERT_TRUE(obj.full());
    }
    {
        auto obj = Stack<int, 5>{1, 2, 3, 4};
        ASSERT_FALSE(obj.full());
    }
    {
        auto obj = Stack<int, 5>();
        ASSERT_FALSE(obj.full());
    }
}

TEST(StackTest, size)
{
    {
        auto obj = Stack<int, 5>();
        ASSERT_EQ(obj.size(), 0);
    }
    {
        auto obj = Stack<int, 5>{1};
        ASSERT_EQ(obj.size(), 1);
    }
    {
        auto obj = Stack<int, 5>{1, 2};
        ASSERT_EQ(obj.size(), 2);
    }
    {
        auto obj = Stack<int, 5>{1, 2, 3};
        ASSERT_EQ(obj.size(), 3);
    }
    {
        auto obj = Stack<int, 5>{1, 2, 3, 4};
        ASSERT_EQ(obj.size(), 4);
    }
    {
        auto obj = Stack<int, 5>{1, 2, 3, 4, 5};
        ASSERT_EQ(obj.size(), 5);
    }
}


TEST(StackTest, ctop)
{
    // Test immutable access to last object maintained in the stack.
    {
        auto obj = Stack<int, 1>{1};

        ASSERT_TRUE(obj.ctop().isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 1);
    }

    {
        // Try to ctop on empty stack. -> StackError::IsEmpty must be returned.
        auto obj = Stack<int, 1>();
        ASSERT_EQ(obj.ctop().unwrapErr(), StackError::IsEmpty);
    }
}

TEST(StackTest, top)
{
    // Test mutable access to last object maintained in the stack.
    {
        auto obj = Stack<int, 1>{1};

        ASSERT_TRUE(obj.top().isOk());
        ASSERT_EQ(obj.top().unwrap(), 1);

        auto& ref = obj.top().unwrap();
        ref = 2;

        ASSERT_EQ(obj.top().unwrap(), 2);
    }

    {
        // Try to top on empty stack. -> StackError::IsEmpty must be returned.
        auto obj = Stack<int, 1>();
        ASSERT_EQ(obj.top().unwrapErr(), StackError::IsEmpty);
    }
}

TEST(StackTest, push)
{
    // Fill empty stack.
    {
        auto obj = Stack<int, 5>();
        ASSERT_TRUE(obj.push(1).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 1);

        ASSERT_TRUE(obj.push(2).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 2);

        ASSERT_TRUE(obj.push(3).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 3);

        ASSERT_TRUE(obj.push(4).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 4);

        ASSERT_TRUE(obj.push(5).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 5);
    }

    // Fill partially filled stack
    {
        auto obj = Stack<int, 5>{1, 2, 3};
        ASSERT_TRUE(obj.push(4).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 4);

        ASSERT_TRUE(obj.push(5).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 5);
    }

    // Error behavior: Push on full stack: Must return StackError::IsFull
    {
        auto obj = Stack<int, 5>{1, 2, 3, 4, 5};
        auto result = obj.push(6);

        ASSERT_TRUE(result.isErr());
        ASSERT_EQ(result.unwrapErr(), StackError::IsFull);
    }
}

TEST(StackTest, emplace)
{
    // Fill empty stack.
    {
        auto obj = Stack<int, 5>();
        ASSERT_TRUE(obj.emplace(1).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 1);

        ASSERT_TRUE(obj.emplace(2).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 2);

        ASSERT_TRUE(obj.emplace(3).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 3);

        ASSERT_TRUE(obj.emplace(4).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 4);

        ASSERT_TRUE(obj.emplace(5).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 5);
    }

    // Fill partially filled stack
    {
        auto obj = Stack<int, 5>{1, 2, 3};
        ASSERT_TRUE(obj.emplace(4).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 4);

        ASSERT_TRUE(obj.emplace(5).isOk());
        ASSERT_EQ(obj.ctop().unwrap(), 5);
    }

    // Error behavior: emplace on full stack: Must return StackError::IsFull
    {
        auto obj = Stack<int, 5>{1, 2, 3, 4, 5};
        auto result = obj.emplace(6);

        ASSERT_TRUE(result.isErr());
        ASSERT_EQ(result.unwrapErr(), StackError::IsFull);
    }
}

TEST(StackTest, pop)
{
    // pop full stack.
    {
        auto obj = Stack<int, 5>{1, 2, 3, 4, 5};
        ASSERT_EQ(obj.ctop().unwrap(), 5);
        ASSERT_TRUE(obj.pop().isOk());

        ASSERT_EQ(obj.ctop().unwrap(), 4);
        ASSERT_TRUE(obj.pop().isOk());

        ASSERT_EQ(obj.ctop().unwrap(), 3);
        ASSERT_TRUE(obj.pop().isOk());

        ASSERT_EQ(obj.ctop().unwrap(), 2);
        ASSERT_TRUE(obj.pop().isOk());

        ASSERT_EQ(obj.ctop().unwrap(), 1);
        ASSERT_TRUE(obj.pop().isOk());
    }

    // pop partially filled stack
    {
        auto obj = Stack<int, 5>{1, 2, 3};
        ASSERT_EQ(obj.ctop().unwrap(), 3);
        ASSERT_TRUE(obj.pop().isOk());

        ASSERT_EQ(obj.ctop().unwrap(), 2);
        ASSERT_TRUE(obj.pop().isOk());

        ASSERT_EQ(obj.ctop().unwrap(), 1);
        ASSERT_TRUE(obj.pop().isOk());
    }

    // Error behavior: pop on empty stack: Must return StackError::IsEmpty
    {
        auto obj = Stack<int, 5>();
        auto result = obj.pop();

        ASSERT_TRUE(result.isErr());
        ASSERT_EQ(result.unwrapErr(), StackError::IsEmpty);
    }
}
