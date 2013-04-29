# -*- CMAKE -*-
# This file is a part of the cipra Unit Testing Framework.
# Copyright (C) 2013, Patrick M. Niedzielski.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#
#  3. The names of its contributors may not be used to endorse or
#     promote products derived from this software without specific
#     prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 2.8)
project(cipra)
set(cipra_VERSION 1.1)

include(GNUInstallDirs)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cipra)

install(FILES AUTHORS.md
              COPYING.bsd
              COPYING.ccby
              COPYING.md
              INSTALL.md
              README.md
        DESTINATION ${CMAKE_INSTALL_DOCDIR})

option(WITH_PKGCONFIG "Create and install a pkg-config file." ON)
if(WITH_PKGCONFIG)
  find_package(PkgConfig REQUIRED)
  configure_file(${cipra_SOURCE_DIR}/cipra.pc.in
                 ${cipra_BINARY_DIR}/cipra.pc
                 @ONLY)
  # where to install?  test defaults:
  set(pkgconfig_install_path "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
  execute_process(
    COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=pc_path pkg-config
    OUTPUT_VARIABLE pkgconfig_paths_string
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REPLACE ":" ";" pkgconfig_paths ${pkgconfig_paths_string})
  foreach(path IN LISTS pkgconfig_paths)
    if("${path}" STREQUAL "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
      set(pkgconfig_install_path "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
      break()
    elseif ("${path}" STREQUAL "${CMAKE_INSTALL_FULL_DATADIR}/pkgconfig")
      set(pkgconfig_install_path "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
      break()
    endif()
  endforeach()
  set(CIPRA_INSTALL_PKGCONFIG_PATH ${pkgconfig_install_path}
      CACHE STRING "Where to install the pkg-config file.")
  install(FILES ${cipra_BINARY_DIR}/cipra.pc
          DESTINATION ${CIPRA_INSTALL_PKGCONFIG_PATH})
endif()

option(WITH_DOXYGEN "Create and install doxygen HTML documentation." ON)
if (WITH_DOXYGEN)
  find_package(Doxygen 1.8.2 REQUIRED)
  configure_file(${cipra_SOURCE_DIR}/Doxyfile.in
                 ${cipra_BINARY_DIR}/Doxyfile
                 @ONLY)
  add_custom_target (doc ALL
                     ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                     COMMENT "Generating API documentation with Doxygen"
                     VERBATIM)
  install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html/
           DESTINATION ${CMAKE_INSTALL_DOCDIR}/api)
  install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/man/
           DESTINATION ${CMAKE_INSTALL_MANDIR})
endif()