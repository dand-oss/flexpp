cmake_minimum_required(VERSION 3.30)
project(flexpp VERSION 1.0.0 LANGUAGES C)

set(exename "flex++")
set(libname "libflex++")

set (HAS_BISON TRUE)
set(BISON_DIR "/usr/local/bin"
    CACHE PATH "Location of Bison++")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# for all files in this directory..
include_directories(src ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(
    -DSTDC_HEADERS=1
    -DHAVE_STRING_H=1
    -DDEFAULT_CSIZE=256
    )

if (WIN32)
    add_definitions(
        -D_MSDOS
        -D_CRT_SECURE_NO_WARNINGS
        )
endif(WIN32)

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
target_sources(firstflex PRIVATE
    ${flexpp_sources}
    src/initscan.c)

# library with one file
if (WIN32)
    add_library(${libname} STATIC)
else (WIN32) # unix
    add_library(${libname} SHARED)
endif (WIN32)
set_target_properties(${libname} PROPERTIES OUTPUT_NAME "flex++")
target_sources(${libname} PRIVATE
    src/libmain.c)
#####
# Can't get link yet...
#####
if(WIN32)
    # export all symbols from windows DLL
    set_target_properties(${libname} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    install_pdb(${libname})
else(WIN32) # windows
    # force linker to resolve all deps
    # master can't handle this
    #set_target_properties(${libname} PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
endif(WIN32)

# finally, flex
add_executable(${exename})
target_sources(${exename} PRIVATE
    ${flexpp_sources}
    ${CMAKE_CURRENT_BINARY_DIR}/scan.c)

# copy exe, lib, support files, and docs
install(TARGETS ${exename} ${libname}
    EXPORT flexppTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES
    src/flexskel.cc
    src/flexskel.h
    DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES
    doc/flex++.1
    doc/flex++.1.dman
    DESTINATION man)

# Export all targets as a single flexppTargets group
install(EXPORT flexppTargets
    FILE flexppTargets.cmake
    NAMESPACE flexpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/flexpp
)

# Generate version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/flexppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Configure and install flexppConfig.cmake
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/flexppConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/flexppConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/flexpp
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/flexppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/flexppConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/flexpp
)

# CPack configuration
set(CPACK_PACKAGE_NAME        "flexpp")
set(CPACK_PACKAGE_VERSION     "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Flex++ lexical analyzer generator"
)
set(CPACK_PACKAGE_VENDOR      "AppSmiths Ventures LLP")
set(CPACK_GENERATOR           "ZIP;TGZ")
include(CPack)