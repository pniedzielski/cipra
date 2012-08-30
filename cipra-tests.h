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
#include <cstdlib>
#include <cstring>

#ifdef CIPRA_CXA_ABI
#  include <cxxabi.h>
#endif

namespace cipra {

    namespace details {
        std::string current_exception_name()
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
    }

    template <typename funcT>
    void ok(funcT expr, std::string name)
    {
        try {
            if (expr()) {
                std::cout << tap13_ok(name);
                return;
            } else {
                std::cout << tap13_not_ok(name);
                return;
            }
        } catch (...) { // don't count exception as ok
            std::cout << tap13_not_ok(name)
                      << "# got exception of type "
                      << details::current_exception_name()
                      << std::endl;
        }
    }

//    template <typename funcT, typename T>
//    void is(funcT 
            


    template<typename funcT>
    void throws(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (...) {
            // we expect an exception
            std::cout << tap13_ok(name);
            return;
        }
        // no exception thrown
        std::cout << tap13_not_ok(name)
                  << "# got no exception" << std::endl;
    }

    template<typename exceptionT, typename funcT>
    void throws(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (exceptionT &e) {
            // we expect this exception.
            std::cout << tap13_ok(name);
            return;
        } catch (...) {
            // an exception was thrown, but we don't know what.
            std::cout << tap13_not_ok(name)
                      << "# got exception of type "
                      << details::current_exception_name()
                      << std::endl;
            return;
        }
        // no exception thrown
        std::cout << tap13_not_ok(name)
                  << "# got no exception" << std::endl;
    }

    template<typename funcT>
    void nothrows(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (...) {
            // exception not expected
            std::cout << tap13_not_ok(name)
                      << "# got exception of type "
                      << details::current_exception_name()
                      << std::endl;
            return;
        }
        // no exception thrown
        std::cout << tap13_ok(name);
    }

    template<typename exceptionT, typename funcT>
    void nothrows(funcT expr, std::string name)
    {
        try {
            (void)expr();
        } catch (exceptionT &e) {
            // we don't want this exception
            std::cout << tap13_not_ok(name);
            return;
        } catch (...) {
            // this is okay.  catch exception and fall through to
            // below
        }
        // no exception thrown
        std::cout << tap13_ok(name);
    }
}

#endif
