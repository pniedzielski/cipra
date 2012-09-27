<!-- -*- markdown -*- -->
# cipra Unit Testing Framework Installation
Version 1.0

This is the `INSTALL` file for the cipra Unit Testing Framework.
cipra is a Free and Open Source Unit Testing Framework for C++.

See the included [README](@ref index) file for more details.

### File Copyright and License

Copyright (C) 2012, [Patrick M. Niedzielski]
                    (mailto:PatrickNiedzielski@gmail.com)

This work is licensed under a Creative Commons Attribution 3.0 United
States License. You should have received a copy of the CC-BY 3.0 US
license along with this file. If not, see
[the Creative Commons website](http://creativecommons.org/licenses/by/3.0/us).

## Installation

Simply add the `cipra.h` header to your include path and use it in
your program.  No compilation is needed.  cipra is sufficiently
cross-platform that it should Just Work.

## Configuration

cipra accepts several preprocessor flags that affect both its
implementation and API.  Define these flags before you include the
`cipra.h` header file.  Different flags can be applied to different
translation units without problem.

  * `some flag`: description....
