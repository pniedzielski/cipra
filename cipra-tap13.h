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

#ifndef CIPRA_TAP13_H
#define CIPRA_TAP13_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <utility>

namespace cipra {

    std::string tap13_header()
    {
        return std::string("TAP version 13\n");
    }

    std::string tap13_plan(int total)
    {
        std::stringstream out;
        out << "1.." << total;
        return out.str();
    }
    
    std::string tap13_diagnostic(std::string text)
    {
        return "# " + text;
    }

    std::string tap13_ok(std::string name = "")
    {
        return std::string("ok ") +
            ((name != "") ? "- " + name : "") +
            "\n";
    }

    std::string tap13_not_ok(std::string name = "")
    {
        return std::string("not ok ") +
            ((name != "") ? "- " + name : "") +
            "\n";
    }

/*    struct tap13_yamlish {
        std::string message;
        std::string severity;
        std::string source;
        std::chrono::time_point<std::chrono::system_clock> datetime;
        std::string file;
        int line;
        std::string name;
        struct {
            std::string type;
            std::string value;
        } actual, expected;
        std::string display;
        std::map<std::string, std::string> dump;
        struct {
            std::string name;
            std::string what;
        } error;
        std::vector<std::string> backtrace;
    };

    namespace details {
        std::string time_point_to_string(
            std::chrono::time_point<std::chrono::system_clock> t)
        {
            char datetime_string[] = "YYYY-MM-DDThh:mm:ss+0000";
            std::time_t t =
                std::chrono::system_clock::to_time_t(yaml.datetime);
            std::strftime(datetime_string, sizeof datetime_string,
                          "%FT%T%z", std::localtime(&t));
            return std::string(datetime_string);
        }

        std::string value_to_string(std::string type, std::string val)
        {
            return std::
    }

    std::string tap13_yamlish_output(tap13_yamlish yaml)
    {
        std::string output("    ---\n");
        if (yaml.message != "") {
            output += "    message: " + yaml.message + "\n";
        }
        if (yaml.severity != "") {
            output += "    severity: " + yaml.severity + "\n"
        }
        if (yaml.source != "") {
            output += "    source: " + yaml.source + "\n";
        }
        if (yaml.datetime != std::chrono::time_point
            <std::chrono::system_clock>()) {
            output += "    datetime: " +
                time_point_to_string(yaml.datetime) + "\n";
        }
        if (yaml.file != "") {
            output += "    file: " + yaml.file + "\n";
        }
        if (yaml.line != 0) {
            output += "    line: " + yaml.line + "\n";
        }
        if (yaml.name != "") {
            output += "    name: " + yaml.name + "\n";
        }
        if (yaml.file != "") {
            output += "    file: " + yaml.file + "\n";
            } */

}

#endif
