cmake_minimum_required(VERSION 2.8)

project(hiredis)

list(APPEND public_hdrs
	"hiredis.h")

list(APPEND src
	"async.c"
	"async.h"
#	"dict.c"
#	"dict.h"
	"fmacros.h"
	"hiredis.c"
	"net.c"
	"net.h"
	"sds.c"
	"sds.h"
	"system_diff.h"
	${public_hdrs}
	)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -fPIC -Wall -W -Wstrict-prototypes -Wwrite-strings")
endif()

list(APPEND public_inc_dir
	"${CMAKE_CURRENT_SOURCE_DIR}")

if(MSVC)
	list(APPEND definitions
		"_CRT_SECURE_NO_WARNINGS")
endif()

if(WIN32)
	list(APPEND system_libs
		"wsock32"
		"ws2_32")
	list(APPEND private_inc_dirs
		"${CMAKE_CURRENT_SOURCE_DIR}/win32helpers")
endif()

add_library(hiredis ${src})
set_target_properties(hiredis PROPERTIES
	PUBLIC_HEADERS "${public_hdrs}"
	INCLUDE_DIRECTORIES "${public_inc_dir};${private_inc_dirs}"
	COMPILE_DEFINITIONS "${definitions}"
	INTERFACE_INCLUDE_DIRECTORIES "${public_inc_dir}")
target_link_libraries(hiredis ${system_libs})

list(APPEND test_src
	"test.c"
	)

if(WIN32)
	list(APPEND test_src
		"win32.c")
endif()

add_executable(hiredis_test ${test_src})
set_target_properties(hiredis_test PROPERTIES
	INCLUDE_DIRECTORIES "${private_inc_dirs}")
target_link_libraries(hiredis_test hiredis)
