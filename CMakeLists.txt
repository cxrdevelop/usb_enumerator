cmake_minimum_required(VERSION 3.5)

project(usb_enumerator LANGUAGES CXX)

# The project package version.
set (PROJECT_VERSION_MAJOR 1)
set (PROJECT_VERSION_MINOR 0)
set (PROJECT_VERSION_PATCH 0)

# The project package version.
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# The package configuration name.
set (PACKAGE_NAME "${PROJECT_NAME}")

# Define a short description of the project (only a few words).
set (PACKAGE_DESCRIPTION "C++ wrapper API of C API for USB device access (libusb-1.0)")

# The package configuration version.
set (PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

# The package full name with version
set (PACKAGE "${PACKAGE_NAME}-${PACKAGE_VERSION}")

set (LIBUSBPP_LIB_SOVERSION 0)

# The build version (VERSION) of the USBPP libraries.
set (LIBUSBPP_LIB_VERSION "${LIBUSBPP_LIB_SOVERSION}.${PACKAGE_VERSION}")

# The build name (OUTPUT_NAME) of the USBPP libraries.
set (LIBUSBPP_LIB_NAME "usbpp-${PACKAGE_VERSION}")

# Make sure the user doesn't play dirty with symlinks
get_filename_component (srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
get_filename_component (bindir "${CMAKE_BINARY_DIR}" REALPATH)

# Disallow in-source builds
if (${srcdir} STREQUAL ${bindir})
        message(FATAL_ERROR "In-source builds are not allowed. "
        "Please create a directory and run cmake from there, passing the path "
        "to this source directory as the last argument. This process created "
        "the file `CMakeCache.txt' and the directory `CMakeFiles' in ${srcdir}. "
        "Please remove them.")
endif (${srcdir} STREQUAL ${bindir})

# Use NEW behavior with newer CMake releases
foreach (p
                CMP0025 # CMake 3.0: Compiler id for Apple Clang is now AppleClang
                )
        if (POLICY ${p})
                cmake_policy(SET ${p} NEW)
        endif()
endforeach()

# Make it possible to locate CMake modules for finding libraries
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Use GNUInstallDirst to get canonical paths
include(GNUInstallDirs)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.
install(EXPORT ${PACKAGE_NAME}Config DESTINATION ${CMAKE_INSTALL_DATADIR}/${PACKAGE}/cmake)

# Exporting dependencies towards external packages
set (PKG_CONFIG_REQUIRES libusb-1.0)
set (PKG_CONFIG_LIBDIR
    "\${prefix}/lib"
)
set (PKG_CONFIG_INCLUDEDIR
    "\${prefix}/include/${PACKAGE}"
)
set (PKG_CONFIG_LIBS
    "-L\${libdir} -l${LIBUSBPP_LIB_NAME}"
)
set (PKG_CONFIG_CFLAGS
    "-I\${includedir}"
)

configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/pkg-config.pc.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE}.pc
)

# Install package configuration file
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE}.pc
         DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Preappend the local include search path
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
#message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

#add_subdirectory (headers)
add_subdirectory (src)
#add_subdirectory (examples)

add_executable(usb_enumerator
    main.cpp
    usb_functions.cpp
    usb_functions.h
    string_allocation.cpp
    string_allocation.h
    )

target_link_libraries (usb_enumerator sharedlibusbcpp)
