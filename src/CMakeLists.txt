#
# src/CMakeLists.txt
#
cmake_minimum_required(VERSION 3.5)

# Require libusb-1.0
find_package (LibUSB-1.0 REQUIRED)
if (LIBUSB1_FOUND)
    include_directories (${LIBUSB1_INCLUDE_DIR})
else (LIBUSB1_FOUND)
    message (FATAL_ERROR "LibUSB-1.0 was not found.")
endif (LIBUSB1_FOUND)

# On Windows do not prefix the DLLs with the 'lib' prefix
if (WIN32)
    set (LIB_PREFIX "")
else (WIN32)
    set (LIB_PREFIX "lib")
endif (WIN32)

# Create position independent code on all targets [auto]
# (needed for static build on non-x86):
set (CMAKE_POSITION_INDEPENDENT_CODE on)

# Collect all library source files
set (libusbcppsrc
    configuration.cpp
    configurationImpl.cpp
    configurationImpl.hpp
    device.cpp
    deviceImpl.cpp
    deviceImpl.hpp
    endpoint.cpp
    endpointImpl.cpp
    endpointImpl.hpp
    exception.cpp
    interface.cpp
    interfaceImpl.cpp
    interfaceImpl.hpp
    libusbImpl.cpp
    libusbImpl.hpp
    libusb-cpp.cpp
    transfer.cpp
    transferImpl.cpp
    transferImpl.hpp
    wideconvert.cpp
    wideconvert.hpp
)

# Check if all sources were catched
message (STATUS "Searching for uncatched library sources...")
file (GLOB allsrc RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.hpp
    *.cpp
)
foreach (_src ${allsrc})
    list (FIND libusbcppsrc ${_src} matchidx)
    if (${matchidx} EQUAL -1)
        message (AUTHOR_WARNING "  ${_src}")
    endif ()
endforeach ()

# This is the "object library" target:
# - compiles the sources only once
# - shared libraries need PIC
add_library (objlibusbcpp OBJECT ${libusbcppsrc})
set_property (TARGET ${objlibusbcpp} PROPERTY POSITION_INDEPENDENT_CODE on)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories (objlibusbcpp
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/../headers
            ${CMAKE_INSTALL_INCLUDEDIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Current source dir1111111: ${CMAKE_CURRENT_SOURCE_DIR}/../headers")

# Actual shared and static libraries built from the same object files
add_library (sharedlibusbcpp SHARED $<TARGET_OBJECTS:objlibusbcpp>)
target_link_libraries (sharedlibusbcpp ${LIBUSB1_LIBRARIES})
set_target_properties (sharedlibusbcpp
                       PROPERTIES OUTPUT_NAME "${LIBUSBPP_LIB_NAME}"
                                  PREFIX "${LIB_PREFIX}"
                                  IMPORT_PREFIX "${LIB_PREFIX}"
                                  VERSION "${LIBUSBPP_LIB_VERSION}"
                                  SOVERSION "${LIBUSBPP_LIB_SOVERSION}")

add_library (staticlibusbcpp STATIC $<TARGET_OBJECTS:objlibusbcpp>)
set_target_properties (staticlibusbcpp
                       PROPERTIES OUTPUT_NAME "${LIBUSBPP_LIB_NAME}"
                                  PREFIX "${LIB_PREFIX}"
                                  IMPORT_PREFIX "${LIB_PREFIX}")

# Install shared and static libraries
install (TARGETS sharedlibusbcpp staticlibusbcpp EXPORT ${PACKAGE_NAME}Config
         ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows

# This makes the project importable from the build directory
export (TARGETS sharedlibusbcpp staticlibusbcpp FILE ${PACKAGE_NAME}Config.cmake)
