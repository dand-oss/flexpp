cmake_minimum_required(VERSION 3.1)
project(flexpp VERSION 1.0.0 LANGUAGES C)

set(exename "flex++")
set(libname "libflex++")

set(BISON_DIR "/usr/local/bin"
    CACHE PATH "Locatoin of Bison++")

include(GNUInstallDirs)

# for all files in this directory..
include_directories(src ${CMAKE_CURRENT_BINARY_DIR})

foreach(s
    ccl.c
    dfa.c
    ecs.c
    gen.c
    main.c
    misc.c
    nfa.c
    sym.c
    tblcmp.c
    yylex.c
)
  list(APPEND flexpp_sources src/${s})
endforeach()
list(APPEND flexpp_sources ${CMAKE_CURRENT_BINARY_DIR}/parse.c)

#scan.c and yylex.c need parse.h

set (HAS_BISON TRUE)

# make parse.c/h from parse.y
# bootstrap with bison
# alternative - copy parse.[ch] files from "src"
if(HAS_BISON)
   if("$ENV{WINVER}" STREQUAL "5.01")
      add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parse.c
               ${CMAKE_CURRENT_BINARY_DIR}/parse.h
               COMMAND ${BISON_DIR}/bin/bison++.exe -S ${BISON_DIR}/lib/bison.cc -H ${BISON_DIR}/lib/bison.h -y -d -o ${CMAKE_CURRENT_BINARY_DIR}/parse.c ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.y
        DEPENDS src/parse.y
        COMMENT "yacc parse.c/h"
        )
   else("$ENV{WINVER}" STREQUAL "5.01")
      add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parse.c
               ${CMAKE_CURRENT_BINARY_DIR}/parse.h
               COMMAND ${BISON_DIR}/bin/bison++ -S ${BISON_DIR}/lib/bison.cc -H ${BISON_DIR}/lib/bison.h -y -d -o ${CMAKE_CURRENT_BINARY_DIR}/parse.c ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.y
        DEPENDS src/parse.y
        COMMENT "yacc parse.c/h"
        )
   endif("$ENV{WINVER}" STREQUAL "5.01")
else(HAS_BISON)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parse.c
           ${CMAKE_CURRENT_BINARY_DIR}/parse.h
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.c ${CMAKE_CURRENT_BINARY_DIR}/parse.c
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.h ${CMAKE_CURRENT_BINARY_DIR}/parse.h
    DEPENDS src/parse.c src/parse.h
    COMMENT "yacc parse.c/h"
    )
endif(HAS_BISON)

# make scan.c from scan.l
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/scan.c
         src/scan.h
    COMMAND firstflex -ist -S${CMAKE_CURRENT_SOURCE_DIR}/src/flexskel.cc -H${CMAKE_CURRENT_SOURCE_DIR}/src/flexskel.h ${CMAKE_CURRENT_SOURCE_DIR}/src/scan.l > ${CMAKE_CURRENT_BINARY_DIR}/scan.c
  DEPENDS firstflex
  DEPENDS src/scan.l
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/parse.h
  COMMENT "firstflex scan.c"
)

# intermediate flex to generate scan.c, built with initscan,
add_executable(firstflex)
target_compile_definitions(firstflex PRIVATE
    STDC_HEADERS=1
    HAVE_STRING_H=1
    DEFAULT_CSIZE=256
    )
if ( WIN32 )
    target_compile_definitions(firstflex PRIVATE
        _MSDOS
        _CRT_SECURE_NO_WARNINGS
        )
endif()
target_sources(firstflex PRIVATE
    ${flexpp_sources}
    src/initscan.c)
if (MSVC)
endif (MSVC)

# library with one file
if (WIN32)
    add_library(${libname} STATIC)
else (WIN32)
    add_library(${libname} SHARED)
endif (WIN32)
set_target_properties(${libname} PROPERTIES OUTPUT_NAME "flex++")
target_sources(${libname} PRIVATE
    src/libmain.c)
#####
# Can't get link yet...
#####
if(UNIX)
    # force linker to resolve all deps
    # master can't handle this
    #set_target_properties(${libname} PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
else(UNIX) # windows
    # export all symobols from windows DLL
    set_target_properties(${libname} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    install_pdb(${libname})
endif(UNIX)

# finally, flex
add_executable(${exename})
target_compile_definitions(${exename} PRIVATE
    STDC_HEADERS=1
    HAVE_STRING_H=1
    DEFAULT_CSIZE=256
    )
if ( WIN32 )
    target_compile_definitions(${exename} PRIVATE
        _MSDOS
        _CRT_SECURE_NO_WARNINGS
        )
endif()
target_sources(${exename} PRIVATE
    ${flexpp_sources}
    ${CMAKE_CURRENT_BINARY_DIR}/scan.c)

# copy exe, lib, support files, and docs
install(TARGETS ${exename} DESTINATION bin)
install(TARGETS ${libname} DESTINATION lib)
install(FILES
    src/flexskel.cc
    src/flexskel.h
    DESTINATION lib)
install(FILES
    doc/flex++.1
    doc/flex++.1.dman
    DESTINATION man)
