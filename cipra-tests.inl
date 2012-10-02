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

#ifndef CIPRA_TESTS_INL
#define CIPRA_TESTS_INL

#include "cipra-tap13.h"

#include <iostream>
#include <string>
#include <type_traits>

namespace cipra {

    std::string fixture::current_exception_name()
    {
#ifdef CIPRA_CXA_ABI
        // with this flag, we can use abi:: functions from GCC and
        // others to determine more about the exception.
        int success_code = 0;
        char *realname = abi::__cxa_demangle(
            abi::__cxa_current_exception_type()->name(),
            0,
            0,
            &success_code);
        if (success_code == 0) { // success
            std::string return_realname(realname);
            std::free(realname);
            return return_realname;
        }
        // else, use what other compilers use
#endif
        return std::string("(unknown type)");
    }

    int fixture::run()
    {
        std::cout << cipra::tap13::header() << std::endl;
        test();
        return succeeded ? 0 : 1;
    }

    fixture::fixture()
        : status(0)
    {}

    fixture::fixture(const fixture &t)
        : status(t.status)
    {}

    void fixture::plan(int total)
    {
        std::cout << tap13::plan(total) << std::endl;
    }
    void fixture::plan(fixture::skip_all_t, std::string reason)
    {
        std::cout << tap13_plan(0) << ' ' << tap13_diagnostic(reason)
                  << std::endl;
    }

    void fixture::diag(std::string message)
    {
        std::cerr << tap13::diagnostic(message) << std::endl;
    }
    void fixture::note(std::string message)
    {
        std::cout << tap13::diagnostic(message) << std::endl;
    }

    // use this one for successful static assert
    // we have to use this because there isn't function partial
    // specialization.
    template<typename funcT>
    void fixture::ok_impl(funcT &expr, std::string &name, std::true_type)
    {
        try {
            if (expr()) {
                std::cout << tap13::ok(0, name) << std::endl;
                return;
            } else {
                status = 1;
                std::cout << tap13::not_ok(0, name) << std::endl;
                return;
            }
        } catch (...) { // don't count exception as ok
            status = 1;
            std::cout << tap13::not_ok(0, name) << std::endl
                      << tap13::diagnostic("got exception of type " +
                                           current_exception_name())
                      << std::endl;
        }
    }

    // use this one for failing static assert
    // we have to use this because there isn't function partial
    // specialization.
    template<typename funcT>
    void fixture::ok_impl(funcT &expr, std::string &name, std::false_type)
    {
        // There was an error in the static_assert.
    }

    template<typename funcT>
    void fixture::ok(funcT expr, std::string name)
    {
        // static_cast<bool>(expr()) should work
        static_assert(
            std::is_convertible<decltype(expr()), bool>::value,
            "The expression argument provided cannot be evaluated as "
            "true or false.");

        // now we separate it into another function so we don't get
        // another compile error telling us the same thing, only more
        // tersely
        ok_impl (expr, name,
                 typename std::is_convertible<decltype(expr()), bool>::type());
    }

    template<typename T, typename U>
    void fixture::is(T got, U expected, std::string name)
    {
        if (got == expected) {
            std::cout << tap13_ok(name) << std::endl;
        } else {
            std::cout << tap13_not_ok(name) << std::endl;
        }
    }

    template<typename T, typename U>
    void fixture::isnt(T got, U expected, std::string name)
    {
        if (got != expected) {
            std::cout << tap13_ok(name) << std::endl;
        } else {
            std::cout << tap13_not_ok(name) << std::endl;
        }
    }

    template<typename funcT>
    void fixture::throws(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (...) {
            // we expect an exception
            std::cout << tap13::ok(0, name) << std::endl;
            return;
        }
        // no exception thrown
        status = 1;
        std::cout << tap13::not_ok(0, name) << std::endl
                  << tap13::diagnostic("got no exception")
                  << std::endl;
    }

    template<typename exceptionT, typename funcT>
    void fixture::throws(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (exceptionT &e) {
            // we expect this exception.
            std::cout << tap13::ok(0, name) << std::endl;
            return;
        } catch (...) {
            // an exception was thrown, but we don't know what.
            status = 1;
            std::cout << tap13::not_ok(0, name) << std::endl
                      << tap13::diagnostic("got exception of type " +
                                           current_exception_name())
                      << std::endl;
            return;
        }
        // no exception thrown
        status = 1;
        std::cout << tap13::not_ok(0, name) << std::endl
                  << tap13::diagnostic("got no exception")
                  << std::endl;
    }

    template<typename funcT>
    void fixture::nothrows(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (...) {
            // exception not expected
            status = 1;
            std::cout << tap13::not_ok(0, name) << std::endl
                      << tap13::diagnostic("got exception of type " +
                                           current_exception_name())
                      << std::endl;
            return;
        }
        // no exception thrown
        std::cout << tap13::ok(0, name) << std::endl;
    }

    template<typename exceptionT, typename funcT>
    void fixture::nothrows(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (exceptionT &e) {
            // we don't want this exception
            status = 1;
            std::cout << tap13::not_ok(0, name) << std::endl;
            return;
        } catch (...) {
            // this is okay.  catch exception and fall through to
            // below
        }
        // no exception thrown
        std::cout << tap13::ok(0, name) << std::endl;
    }

    void fixture::test()
    {
        // If there's no test defined by the user, this will be
        // defaulted to.
        plan(0);
        std::cout << tap13::diagnostic("no tests were defined")
                  << std::endl;
    }

}

#endif
