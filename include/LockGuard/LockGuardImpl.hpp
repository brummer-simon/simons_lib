/**
 * @file      LockGuardImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Basic reimplementation of std::lock_guard.
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

#ifndef LOCK_GUARD_IMPL_HPP_20180825084201
#define LOCK_GUARD_IMPL_HPP_20180825084201

namespace simons_lib::lock
{

/**
 * @brief Simple re-implementation of std::lock_guard.
 * @note This RAII lock guard is used throughout simons_lib
 *       with the intension, that the mutex header doesn't have to be included
 *       in cases where no thread safety is required.
 * @tparam Mutex   the mutex type to lock. Must implement at least BasicLockable.
 */
template<typename Mutex>
class LockGuard
{
public:
    /// @brief Type of internally used mutex.
    using mutex_type = Mutex;

    /**
     * @brief Constructor.
     * @param[in] mutex   Mutex that should be used by the LockGuard
     */
    LockGuard(mutex_type& mutex) noexcept
        : m_mutex(mutex)
    {
        m_mutex.lock();
    }

    ~LockGuard() noexcept
    {
        m_mutex.unlock();
    }

    // Copying and moving is forbidden
    LockGuard(LockGuard const&) = delete;
    LockGuard(LockGuard&&) = delete;
    LockGuard& operator = (LockGuard const&) = delete;
    LockGuard& operator = (LockGuard&&) = delete;

private:
    mutex_type& m_mutex;
};

} // namespace simons_lib::lock

#endif // LOCK_GUARD_IMPL_HPP_20180825084201
