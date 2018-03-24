#
# Copyright © 2018 ebio lab. SNU. All Rights Reserved.
#
# @file CmakeList.txt
# @date 2018-03-24, JoonYong
# @author Kim, JoonYong <tombraid@snu.ac.kr>
#
# This file is for compiling a standard converter
# refer from: https://github.com/ebio-snu/stdcvt
#

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (stdcvt)

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
SET(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/../doc/doxy.conf
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
ENDIF(DOXYGEN_FOUND)

FIND_PACKAGE(Boost 1.62 REQUIRED COMPONENTS system date_time filesystem iostreams)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF(Boost_FOUND)

FIND_PACKAGE(Glog REQUIRED)
IF(GLOG_FOUND)
    INCLUDE_DIRECTORIES (${GLOG_INCLUDE_DIRS})
ENDIF(GLOG_FOUND)

ADD_DEFINITIONS(-fsigned-char -Wall) 

INCLUDE_DIRECTORIES (include cvtdriver/spec cvtdriver/include)

ADD_EXECUTABLE (stdcvt src/stdcvt.cpp)
TARGET_LINK_LIBRARIES (stdcvt ${Boost_LIBRARIES} ${GLOG_LIBRARIES} pthread dl ${GTEST_LIBRARIES})
