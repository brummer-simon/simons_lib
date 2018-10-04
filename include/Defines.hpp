/**
 * @file      CachedCallable.hpp
 * @author    Simon Brummer (<simon.brummer@posteo.de>)
 * @brief     Defines controlling the behavior of simons_lib.
 * @copyright 2018 Simon Brummer. All rights reserved.
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

#ifndef DEFINES_HPP_20180930093829
#define DEFINES_HPP_20180930093829

// Configure simons_lib for a constrained environments (e.g. Embedded systems
// incapable of running a full OS like MCU, SoC ...). This leads to:
// 1) Remove all prints to the console.
// 2) Different hard fault handling (stay in endless loop instead of calling exit()).
#ifdef SIMON_LIB_CONFIG_FOR_HEAVILY_CONSTRAINS_ENVIRONMENTS

// Disable Printing to std out
#ifndef SIMONS_LIB_DISABLE_PRINTS
#define SIMONS_LIB_DISABLE_PRINTS
#endif // SIMONS_LIB_DISABLE_PRINTS

#ifndef SIMONS_LIB_DISABLE_EXIT
#define SIMONS_LIB_DISABLE_EXIT
#endif // SIMONS_LIB_DISABLE_EXIT

#ifndef SIMONS_LIB_DISABLE_OPERATOR_MOD
#define SIMONS_LIB_DISABLE_OPERATOR_MOD
#endif // SIMONS_LIB_DISABLE_OPERATOR_MOD

// Disable
#endif // SIMON_LIB_CONFIG_FOR_MCU

#endif // DEFINDES_HPP_20180930093829
