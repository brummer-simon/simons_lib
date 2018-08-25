/**
 * @file      DummyMutex.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Dummy implementation of the std::mutex interface.
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

#ifndef DUMMY_MUTEX_HPP_20180825084201
#define DUMMY_MUTEX_HPP_20180825084201

namespace simons_lib::lock
{

/**
 * @brief Dummy implementation of the std::mutex interface.
 * @note This class is intended to be optimized out, in cases
 *       where threadsafety is not required.
 */
class DummyMutex
{
public:
    /**
     * @brief locks the mutex dummy. Does nothing.
     */
    void lock(void) const noexcept
    {
    }

    /**
     * @brief try_locks the mutex dummy. Does nothing.
     * @returns always true;
     */
    bool try_lock(void) const noexcept
    {
        return true;
    }

    /**
     * @brief unlocks the mutex dummy. Does nothing.
     */
    void unlock(void) const noexcept
    {
    }
};

} // namespace simons_lib::lock

#endif // DUMMY_MUTEX_HPP_20180825084201