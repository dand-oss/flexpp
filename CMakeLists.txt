cmake_minimum_required(VERSION 3.31)
project(flexpp VERSION 1.0.0 LANGUAGES C)

set(exename "flex++")
set(libname "libflex++")

###############
# ASI default settings
list(APPEND CMAKE_MODULE_PATH "$ENV{ASV_CMAKE}")
include(asv_cmake_defaults)
asv_cmake_defaults( )
###############

# Option to use bison++ for generating parser
option(FLEXPP_USE_BISON "Use bison++ to generate parser (requires bison++)" ON)

###############
# ASI default settings
list(APPEND CMAKE_MODULE_PATH "$ENV{ASV_CMAKE}")
include(asv_cmake_defaults)
asv_cmake_defaults( )
###############

# redo where bisonpp is
set(BISON_DIR $ENV{ASV_PLAT_PORTS})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Global includes and definitions
include_directories(src ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(
    -DSTDC_HEADERS=1
    -DHAVE_STRING_H=1
    -DDEFAULT_CSIZE=256
)

if(WIN32)
    add_definitions(
        -D_MSDOS
        -D_CRT_SECURE_NO_WARNINGS
    )
endif()

# Find or locate bison++ if requested
if(FLEXPP_USE_BISON)
    # Try to find bisonpp package first
    find_package(bisonpp CONFIG REQUIRED PATHS ${ASV_PLAT_PORTS} NO_DEFAULT_PATH)
    print_target_properties(
        bisonpp::bison++
    )
    
    if(bisonpp_FOUND)
        message(STATUS "Found bisonpp package: ${BISONPP_EXECUTABLE}")
        set(HAS_BISON TRUE)
        set(BISON_EXECUTABLE ${BISONPP_EXECUTABLE})
        set(BISON_SKELETON_CC ${BISONPP_SKELETON_CC})
        set(BISON_SKELETON_H ${BISONPP_SKELETON_H})
    else()
        # Fallback to finding bison++ in the system
        set(BISON_DIR "/usr/local/bin" CACHE PATH "Location of Bison++")
        find_program(BISON_EXECUTABLE 
            NAMES bison++ bison++.exe
            PATHS ${BISON_DIR}/bin ${BISON_DIR} /usr/local/bin /usr/bin
        )
        
        if(BISON_EXECUTABLE)
            message(STATUS "Found bison++ executable: ${BISON_EXECUTABLE}")
            set(HAS_BISON TRUE)
            # Try to find skeleton files
            get_filename_component(BISON_BIN_DIR ${BISON_EXECUTABLE} DIRECTORY)
            get_filename_component(BISON_PREFIX ${BISON_BIN_DIR} DIRECTORY)
            
            # Check common locations for skeleton files
            find_file(BISON_SKELETON_CC 
                NAMES bison.cc
                PATHS ${BISON_PREFIX}/lib ${BISON_DIR}/lib ${BISON_BIN_DIR}/../lib
            )
            find_file(BISON_SKELETON_H
                NAMES bison.h  
                PATHS ${BISON_PREFIX}/lib ${BISON_DIR}/lib ${BISON_BIN_DIR}/../lib
            )
            
            if(NOT BISON_SKELETON_CC OR NOT BISON_SKELETON_H)
                message(WARNING "Bison++ skeleton files not found, disabling bison++ usage")
                set(HAS_BISON FALSE)
            endif()
        else()
            message(STATUS "Bison++ not found, will use pre-generated files")
            set(HAS_BISON FALSE)
        endif()
    endif()
else()
    set(HAS_BISON FALSE)
endif()

# Collect source files
set(flexpp_sources
    src/ccl.c
    src/dfa.c
    src/ecs.c
    src/gen.c
    src/main.c
    src/misc.c
    src/nfa.c
    src/sym.c
    src/tblcmp.c
    src/yylex.c
    ${CMAKE_CURRENT_BINARY_DIR}/parse.c
)

# Generate parse.c/h from parse.y
if(HAS_BISON)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parse.c
               ${CMAKE_CURRENT_BINARY_DIR}/parse.h
        COMMAND ${BISON_EXECUTABLE} 
            -S ${BISON_SKELETON_CC} 
            -H ${BISON_SKELETON_H} 
            -y -d 
            -o ${CMAKE_CURRENT_BINARY_DIR}/parse.c 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.y
        DEPENDS src/parse.y
        COMMENT "Generating parse.c/h with bison++"
        VERBATIM
    )
else()
    # Use pre-generated files
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parse.c
               ${CMAKE_CURRENT_BINARY_DIR}/parse.h
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.c ${CMAKE_CURRENT_BINARY_DIR}/parse.c
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.h ${CMAKE_CURRENT_BINARY_DIR}/parse.h
        DEPENDS src/parse.c src/parse.h
        COMMENT "Using pre-generated parse.c/h"
        VERBATIM
    )
endif()

# Build firstflex (intermediate flex to generate scan.c)
add_executable(firstflex EXCLUDE_FROM_ALL)
target_sources(firstflex PRIVATE
    ${flexpp_sources}
    src/initscan.c
)

# Generate scan.c from scan.l using firstflex
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/scan.c
    COMMAND firstflex 
        -ist 
        -S${CMAKE_CURRENT_SOURCE_DIR}/src/flexskel.cc 
        -H${CMAKE_CURRENT_SOURCE_DIR}/src/flexskel.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scan.l 
        > ${CMAKE_CURRENT_BINARY_DIR}/scan.c
    DEPENDS firstflex
    DEPENDS src/scan.l
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/parse.h
    COMMENT "Generating scan.c with firstflex"
    VERBATIM
)

# Build the library
if(WIN32)
    add_library(${libname} STATIC)
else()
    add_library(${libname} SHARED)
endif()

set_target_properties(${libname} PROPERTIES OUTPUT_NAME "flex++")
target_sources(${libname} PRIVATE src/libmain.c)

if(WIN32)
    # Export all symbols from Windows DLL
    set_target_properties(${libname} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    if(COMMAND install_pdb)
        install_pdb(${libname})
    endif()
endif()

# Build the main flex++ executable
add_executable(${exename})
target_sources(${exename} PRIVATE
    ${flexpp_sources}
    ${CMAKE_CURRENT_BINARY_DIR}/scan.c
)

# Installation
install(TARGETS ${exename} ${libname}
    EXPORT flexppTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install support files
install(FILES
    src/flexskel.cc
    src/flexskel.h
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install documentation
install(FILES
    doc/flex++.1
    doc/flex++.1.dman
    DESTINATION ${CMAKE_INSTALL_MANDIR}/man1
)

# Export targets
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
set(CPACK_PACKAGE_NAME "flexpp")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Flex++ lexical analyzer generator")
set(CPACK_PACKAGE_VENDOR "AppSmiths Ventures LLP")
set(CPACK_GENERATOR "ZIP;TGZ")
include(CPack)
