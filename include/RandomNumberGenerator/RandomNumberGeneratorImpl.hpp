/**
 * @file      RandomNumberGeneratorImpl.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Thin wrapper around stl rng facilities.
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

#ifndef RANDOM_NUMBER_GENERATOR_IMPL_HPP
#define RANDOM_NUMBER_GENERATOR_IMPL_HPP

#include <random>
#include "../LockGuard.hpp"
#include "../DummyMutex.hpp"

namespace simons_lib::random_number_generator
{

using simons_lib::lock::DummyMutex;
using simons_lib::lock::LockGuard;

/**
 * @brief Thin wrapper arround the STL random number generator facilities.
 * @tparam engine_type         Randomness engine to use.
 * @tparam distribution_type   Distribution to use.
 * @tparam mutex_type          Mutex used for synchronization, defaults to DummyMutex.
 *                             If threadsafety is required, supply std::mutex
 */
template <typename engine_type, typename distribution_type, typename mutex_type = DummyMutex>
class RandomNumberGenerator
{
public:
    /// @brief type of resulting values generated by RNG
    using result_type = typename distribution_type::result_type;
    /// @brief type of RNG seed
    using seed_type   = typename engine_type::result_type;

    /**
     * @brief Constructor. Create RNG with a given seed.
     * @param[in] seed   The seed used to initialize RNGs random engine.
     */
    RandomNumberGenerator(seed_type seed)
        : m_engine()
        , m_distribution()
        , m_mutex()
    {
        m_engine.seed(seed);
    }

    /**
     * @brief Set lower and upper Boundries for the RNG.
     * @param[in] lowerBound   The lower boundry of the value interval.
     * @param[in] upperBound   The upper boundry of the value interval.
     * @returns true in case of success, false if @p lowerBound > @p upperBound.
     */
    bool setBoundries(result_type lowerBound, result_type upperBound)
    {
        auto guard = LockGuard<mutex_type>(m_mutex);
        if (lowerBound > upperBound)
        {
            return false;
        }
        m_distribution.param(typename distribution_type::param_type(lowerBound, upperBound));
        return true;
    }

    /**
     * @brief Get next random number.
     * @returns random number
     */
    result_type operator () (void)
    {
        auto guard = LockGuard<mutex_type>(m_mutex);
        return m_distribution(m_engine);
    }

private:
    engine_type       m_engine;
    distribution_type m_distribution;
    mutex_type        m_mutex;
};

} // namespace simons_lib::random_number_generator

#endif // RANDOM_NUMBER_GENERATOR_IMPL_HPP
