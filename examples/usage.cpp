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

// Uncomment on GCC and other compilers that support abi:: functions.
//#define CIPRA_CXA_ABI
#include "../cipra-tap13.h"
#include "../cipra-tests.h"

int main(int argc, char* argv[])
{
    cipra::tap13_header();

    cipra::ok([]() { return true; }, "ok() succeeds on true");
    cipra::ok([]() { return false; }, "ok() fails on false");
    cipra::ok([]() { throw 0; return true; }, "ok() fails on throw");

    cipra::throws([]() { throw 0; }, "throws() detects int throw");
    cipra::throws([]() { }, "throws() fails on no throw");

    cipra::throws<int>([]() { throw 0; }, "throws<int>() detects int throw");
    cipra::throws<int>([]() { throw 'a'; },
                       "throws<int>() fails on char throw");
    cipra::throws<int>([]() { }, "throws<int>() fails on no throw");

    cipra::nothrows([]() { }, "nothrows() accepts no throw");
    cipra::nothrows([]() { throw 0; }, "nothrows() fails on int throw");

    cipra::nothrows<int>([]() { throw 'a'; },
                         "nothrows<int>() accepts char throw");
    cipra::nothrows<int>([]() {}, "nothrows<int>() accepts no throw");
    cipra::nothrows<int>([]() { throw 0; },
                         "nothrows<int>() fails on int throw.");

    return 0;
}
