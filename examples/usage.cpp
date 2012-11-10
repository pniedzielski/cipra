// -*- c++ -*-
/* This file is a part of the cipra Unit Testing Framework.
 * Copyright (C) 2012, Patrick M. Niedzielski.
 * All rights reserved.
 *
 * See accompanying COPYING.bsd file for the license.  When
 * distributing this file independently , it's a good idea to replace
 * this reference with the full license.
 */

// Uncomment on GCC and other compilers that support abi:: functions.
// #define CIPRA_CXA_ABI
#include "../cipra.h"

int main(int argc, char* argv[])
{
    struct my_fixture : cipra::fixture {
        virtual void test() override // define this function to run tests
        {
            plan(13); // Run 13 tests.

            ok([]() { return true; }, "ok() succeeds on true");
            ok([]() { return false; }, "ok() fails on false");
            ok([]() { throw 0; return true; }, "ok() fails on throw");

            throws([]() { throw 0; }, "throws() detects int throw");
            throws([]() { }, "throws() fails on no throw");

            throws<int>([]() { throw 0; }, "throws<int>() detects int throw");
            throws<int>([]() { throw 'a'; },
                       "throws<int>() fails on char throw");
            throws<int>([]() { }, "throws<int>() fails on no throw");

            nothrows([]() { }, "nothrows() accepts no throw");
            nothrows([]() { throw 0; }, "nothrows() fails on int throw");

            nothrows<int>([]() { throw 'a'; },
                         "nothrows<int>() accepts char throw");
            nothrows<int>([]() {}, "nothrows<int>() accepts no throw");
            nothrows<int>([]() { throw 0; },
                         "nothrows<int>() fails on int throw");
        }
    } test;

    return test.run();
}
