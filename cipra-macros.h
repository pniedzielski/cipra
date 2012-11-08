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

#ifndef CIPRA_MACROS_H
#define CIPRA_MACROS_H

#ifdef CIPRA_MACRO_APOLOGIST
#define CIPRA_PLAN(num) plan(num)
#define CIPRA_OK(name, ...) ok([]() {__VA_ARGS__}, name)
#define CIPRA_IS(name, got, expected) is(got, expected, name)
#define CIPRA_ISNT(name, got, expected) isnt(got, expected, name)
#define CIPRA_THROWS(name, ...) throws([]() {__VA_ARGS__}, name)
#define CIPRA_THROWS_TYPE(name, type, ...)      \
    throws<type>([]() {__VA_ARGS__}, name)
#define CIPRA_NOTHROWS(name, ...) nothrows([]() {__VA_ARGS__}, name)
#define CIPRA_NOTHROWS_TYPE(name, type, ...)    \
    nothrows<type>([]() {__VA_ARGS__}, name)
#endif

#ifdef CIPRA_MACRO_POLLUTER
#define PLAN(num) plan(num)
#define OK(name, ...) ok([]() {__VA_ARGS__}, name)
#define IS(name, got, expected) is(got, expected, name)
#define ISNT(name, got, expected) isnt(got, expected, name)
#define THROWS(name, ...) throws([]() {__VA_ARGS__}, name)
#define THROWS_TYPE(name, type, ...)            \
    throws<type>([]() {__VA_ARGS__}, name)
#define NOTHROWS(name, ...) nothrows([]() {__VA_ARGS__}, name)
#define NOTHROWS_TYPE(name, type, ...)          \
    nothrows<type>([]() {__VA_ARGS__}, name)
#endif

#endif
