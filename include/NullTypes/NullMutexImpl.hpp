/**
 * @file      NullMutexImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Dummy implementation of the std::mutex interface.
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

#ifndef NULL_MUTEX_IMPL_HPP_20180825084201
#define NULL_MUTEX_IMPL_HPP_20180825084201

namespace simons_lib::null_types
{

/**
 * @brief Dummy implementation of the std::mutex interface.
 * @note This class is intended to be optimized out, in cases
 *       where thread safety is not required.
 */
class NullMutex
{
public:
    /**
     * @brief locks null mutex. Does nothing.
     */
    void lock(void) const noexcept
    {
    }

    /**
     * @brief try_locks null mutex. Does nothing.
     * @returns always true;
     */
    bool try_lock(void) const noexcept
    {
        return true;
    }

    /**
     * @brief unlocks null mutex. Does nothing.
     */
    void unlock(void) const noexcept
    {
    }
};

} // namespace simons_lib::null_types

#endif // NULL_MUTEX_IMPL_HPP_20180825084201
