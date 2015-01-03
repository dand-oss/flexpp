cmake_minimum_required(VERSION 2.8)
project(flexpp C)

###############
# ASI default settings
list(APPEND CMAKE_MODULE_PATH "$ENV{ASI}/cmake/Modules")
include(asv_cmake_defaults)
asv_cmake_defaults( )
###############


# for all files
add_definitions(-DSTDC_HEADERS=1 -DHAVE_STRING_H=1 -DDEFAULT_CSIZE=256)

# used for main.c
add_definitions(-DDEFAULT_CSIZE=256 -c -DDEFAULT_SKELETON_FILE="/usr/local/lib/flexskel.cc" -DDEFAULT_SKELETONHEADER_FILE="/usr/local/lib/flexskel.h")

if ( WIN32 )
    # seems to help
    add_definitions(-D_MSDOS)
endif()

include_directories(src ${CMAKE_CURRENT_BINARY_DIR})

foreach(s
    ccl.c dfa.c ecs.c gen.c main.c misc.c nfa.c
    sym.c tblcmp.c yylex.c
)
  list(APPEND flexpp_sources src/${s})
  list(APPEND flexpp_sources ${CMAKE_CURRENT_BINARY_DIR}/parse.c)
endforeach()

#scan.c and yylex.c need parse.h

# make parse.c/h from parse.y
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parse.c
         ${CMAKE_CURRENT_BINARY_DIR}/parse.h
	 COMMAND bison -y -d -o ${CMAKE_CURRENT_BINARY_DIR}/parse.c ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.y
  DEPENDS src/parse.y
  COMMENT "yacc parse.c/h"
)

# run the first
# alternative - copy scan.[ch] files from "src/firstflex-output"
set (DO_FIRSTFLEX TRUE)

if (DO_FIRSTFLEX)
  # make scan.c from scan.l
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/scan.c
           src/scan.h
    COMMAND firstflex -ist -S${CMAKE_CURRENT_SOURCE_DIR}/src/flexskel.cc -H${CMAKE_CURRENT_SOURCE_DIR}/src/flexskel.h ${CMAKE_CURRENT_SOURCE_DIR}/src/scan.l |
           sed 's=\"./flexskel.=\"/usr/local/lib/flexskel.=' > ${CMAKE_CURRENT_BINARY_DIR}/scan.c
    DEPENDS firstflex
    DEPENDS src/scan.l
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/parse.h
    COMMENT "firstflex scan.c"
  )
endif (DO_FIRSTFLEX)

# intermediate flex to generate scan.c, built with initscan,
add_executable(firstflex ${flexpp_sources} src/initscan.c)

# library with one file
add_library(libflex++ src/libmain.c)

# finally, flex
add_executable(flex++ ${flexpp_sources} ${CMAKE_CURRENT_BINARY_DIR}/scan.c)

# copy exe
install(TARGETS flex++ DESTINATION bin)

# copy lib
install(TARGETS libflex++ DESTINATION lib)

# copy support files
install(FILES src/flexskel.cc src/flexskel.h DESTINATION lib)

# copy docs
install(FILES doc/flex++.1 doc/flex++.1.dman DESTINATION man)
