/**
 * @file      LockGuardImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Basic reimplementation of std::lock_guard.
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

#ifndef LOCK_GUARD_IMPL_HPP_20180825084201
#define LOCK_GUARD_IMPL_HPP_20180825084201

namespace simons_lib::lock
{

/**
 * @brief Simple re-implementation of std::lock_guard.
 * @note This RAII lock guard is used throughout simons_lib
 *       with the intension, that the mutex header doesn't have to be included
 *       in cases where no threadsafety is required.
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
