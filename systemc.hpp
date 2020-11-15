#pragma once
/** @brief Wrapper around SystemC
 *
 * Allows compiling with `--pedantic -Wall -Wextra` without suppressing things that SystemC currently violates.
 */
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __GNUC__
#pragma GCC   diagnostic push
#pragma GCC   diagnostic ignored "-Wunused-parameter"
#endif
#include <systemc>
#include "sc_time_literals.hpp"
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __GNUC__
#pragma GCC   diagnostic pop
#endif
//vim:syntax=systemc
