// -*- c++ -*-
/* This file is a part of the cipra Unit Testing Framework.
 * Copyright (C) 2012, Patrick M. Niedzielski.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *  3. The names of its contributors may not be used to endorse or
 *     promote products derived from this software without specific
 *     prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CIPRA_TESTS_H
#define CIPRA_TESTS_H

#include "cipra-tap13.h"

#include <string>
#include <iostream>
#include <type_traits>

#ifdef CIPRA_CXA_ABI
#  include <cxxabi.h>
#endif

namespace cipra {

    /**
     * The base class for any test fixtures.  To use cipra, you should
     * derive from this class.
     *
     * @version 1.0
     * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date    2012-09-07
     * @since   1.0
     *
     * @note For compilers that support the Itanium ABI and have the
     * associated functions in the `abi::` namespace, define the
     * preprocessor token `CIPRA_CXA_ABI` before the `cipra.h` header
     * is included to take advantage of these functions to provide
     * better diagnostics of exceptions that are thrown by test
     * expressions.  A conforming compiler should provide
     * `abi::__cxa_current_exception_type()` and `abi::__cxa_demangle`
     * in the header file `cxxabi.h`.  This flag does not affect test
     * behavior outside of exception diagnostics.
     */
    class fixture {
    public:
        /**
         * Run this test fixture and produce output from the
         * user-defined `test()` method.  Returns a value suitable for
         * the return value of the program's `main()` function.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-02
         * @since  1.0
         *
         * @return The program's return value to the operating system.
         * @retval 0 Successful test execution.
         *
         * @note Calling this function will implicitly call your
         * `test()` method.  It runs additional initialization and
         * cleanup code for your test fixture.
         */
        inline int run();

    protected:
        /**
         * Construct a new test fixture.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-02
         * @since  1.0
         */
        inline fixture();
        /**
         * Construct a new test fixture from an existing one.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-02
         * @since  1.0
         */
        inline fixture(const fixture &);

        /**
         * Sets the number of tests you plan to have run by the end of
         * this fixture.  This is used as a checksum after all tests
         * are run.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-08
         * @since  1.0
         *
         * @param [in] total The number of tests you want to run.
         */
        inline void plan(int total);

        /**
         * @name Diagnostic output
         * Prints some string to your test output.  These methods must
         * be used, because the normal output to the nonrmal C++
         * iostreams will be intercepted during the course of the unit
         * test.  The API is modelled on that of Perl's `Test::More`
         * module.  For a more extensible API, use the iostream.
         */
        /// @{
        /**
         * Print a diagnostic message to the test output.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-26
         * @since  1.0
         *
         * @param [in] message A string to print to the test output.
         */
        void diag(std::string message);
        /**
         * Print out a non-diagnostic note to the test output.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-26
         * @since  1.0
         *
         * @param [in] message A string to print to the test output.
         */
        void note(std::string message);
        /// @}
        
        /**
         * @name Test Cases
         * Call these functions to perform single test cases in your
         * unit test.  Each of these functions will output to the test
         * output whether the succeed or fail.
         *
         * Test cases that run code take some input that has an
         * operator().   This can include function pointers, functor
         * objects, or C++11 lambdas.  This allows a form of "lazy
         * execution", in which the test case can run code before and
         * after running your inputted code.
         */
        /// @{
        /**
         * Assert that some expression returns a value that when
         * converted to a `bool` will be `true`.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-07
         * @since  1.0
         *
         * @tparam funcT The type of the object provided in the `expr`
         * argument.
         *
         * @param [in] expr Some object providing the `operator()`
         * that will return a value convertable to `bool`.  This
         * expression will be your assertion expression.
         * @param [in] name A user-readable description of this test
         * assertion.
         *
         * @note `expr` can't simply be a boolean value indicating
         * true or false.  In order to catch exceptions thrown by the
         * expression, we need to run the expression inside a
         * `try`-`catch` block.  If `expr` were a boolean value, the
         * expression would already have been evaluated and the
         * exception already thrown by the time the function would
         * begin.
         */
        template<typename funcT>
        void ok(funcT expr, std::string name);
        /**
         * Assert that some expression throws an exception of any type.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-07
         * @since  1.0
         *
         * @tparam funcT The type of the object provided in the `expr`
         * argument.
         *
         * @param [in] expr Some object providing the `operator()`.
         * This expression will be your assertion expression.
         * @param [in] name A user-readable description of this test
         * assertion.
         *
         * @note `expr` can't simply be a boolean value indicating
         * true or false.  In order to catch exceptions thrown by the
         * expression, we need to run the expression inside a
         * `try`-`catch` block.  If `expr` were a boolean value, the
         * expression would already have been evaluated and the
         * exception already thrown by the time the function would
         * begin.
         */
        template<typename funcT>
        void throws(funcT expr, std::string name);
        /**
         * Assert that some expression throws an exception of a
         * specified type.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-07
         * @since  1.0
         *
         * @tparam exceptionT The type of the exception that running
         * `expr` should cause.
         * @tparam funcT The type of the object provided in the `expr`
         * argument.
         *
         * @param [in] expr Some object providing the `operator()`.
         * This expression will be your assertion expression.
         * @param [in] name A user-readable description of this test
         * assertion.
         *
         * @note `expr` can't simply be a boolean value indicating
         * true or false.  In order to catch exceptions thrown by the
         * expression, we need to run the expression inside a
         * `try`-`catch` block.  If `expr` were a boolean value, the
         * expression would already have been evaluated and the
         * exception already thrown by the time the function would
         * begin.
         */
        template<typename exceptionT, typename funcT>
        void throws(funcT expr, std::string name);
        /**
         * Assert that some expression does not throw an exception of
         * any type.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-07
         * @since  1.0
         *
         * @tparam funcT The type of the object provided in the `expr`
         * argument.
         *
         * @param [in] expr Some object providing the `operator()`.
         * This expression will be your assertion expression.
         * @param [in] name A user-readable description of this test
         * assertion.
         *
         * @note `expr` can't simply be a boolean value indicating
         * true or false.  In order to catch exceptions thrown by the
         * expression, we need to run the expression inside a
         * `try`-`catch` block.  If `expr` were a boolean value, the
         * expression would already have been evaluated and the
         * exception already thrown by the time the function would
         * begin.
         */
        template<typename funcT>
        void nothrows(funcT expr, std::string name);
        /**
         * Assert that some expression does not throw an exception of
         * a specified type.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-07
         * @since  1.0
         *
         * @tparam exceptionT The type of the exception that running
         * `expr` should not cause.
         * @tparam funcT The type of the object provided in the `expr`
         * argument.
         *
         * @param [in] expr Some object providing the `operator()`.
         * This expression will be your assertion expression.
         * @param [in] name A user-readable description of this test
         * assertion.
         *
         * @note `expr` can't simply be a boolean value indicating
         * true or false.  In order to catch exceptions thrown by the
         * expression, we need to run the expression inside a
         * `try`-`catch` block.  If `expr` were a boolean value, the
         * expression would already have been evaluated and the
         * exception already thrown by the time the function would
         * begin.
         */
        template<typename exceptionT, typename funcT>
        void nothrows(funcT expr, std::string name);
        /// @}

    private:
        /**
         * Implements the ok() method.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-08
         * @since  1.0
         *
         * @tparam funcT `expr`'s type
         *
         * @param [in] expr Your function
         * @param [in] name Test name
         *
         * @pre `decltype(expr())` is convertable to `bool`
         */
        template<typename funcT>
        void ok_impl(funcT &expr, std::string &name, std::true_type);
        /**
         * Dummy method for if `expr()` cannot be converted to a
         * boolean value.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-08
         * @since  1.0
         *
         * @tparam funcT `expr`'s type
         *
         * @param [in] expr Your function
         * @param [in] name Test name
         *
         * @pre `decltype(expr())` is not convertable to `bool`.
         */
        template<typename funcT>
        void ok_impl(funcT &expr, std::string &name, std::false_type);
        
        /**
         * Override this method with your test cases.  By default, no
         * tests are defined.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-08
         * @since  1.0
         */
        inline virtual void test();

        /**
         * Find out the name of the type of the current exception that
         * was thrown.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2012-09-07
         * @since  1.0
         *
         * @return A `std::string` that contains the name of the type
         * that was thrown, or the string "(unknown type)" if the
         * compiler does not give us the resources to figure out the
         * true name.
         *
         * @note This function is only able to determine exact names
         * if `CIPRA_CXA_ABI` is defined.
         *
         * @deprecated Don't use this in future versions.  We'll
         * switch to using the YAMLish blocks in the TAP output.
         */
        inline std::string current_exception_name();

        bool succeeded; ///< Whether all the tests succeeded.
    };
}

#include "cipra-tests.inl"

#endif
