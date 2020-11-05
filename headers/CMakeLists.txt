#
# headers/CMakeLists.txt
#
cmake_minimum_required(VERSION 3.5)

include_directories("headers")

# Collect all library header files
set (libusbcppheader
    libusb-cpp.hpp
    libusb-cpp/configuration.hpp
    libusb-cpp/device.hpp
    libusb-cpp/endpointdefs.hpp
    libusb-cpp/endpoint.hpp
    libusb-cpp/exception.hpp
    libusb-cpp/interface.hpp
    libusb-cpp/transferdefs.hpp
    libusb-cpp/transfer.hpp
)

# Check if all headers were catched
message (STATUS "Searching for uncatched library header...")
file (GLOB_RECURSE allheader RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.h
    *.inl
    *.hpp
)
foreach (_header ${allheader})
    list (FIND libusbcppheader ${_header} matchidx)
    if (${matchidx} EQUAL -1)
        message (AUTHOR_WARNING "  ${_header}")
    endif ()
endforeach ()

# Install collected header files
#foreach (file ${libusbppheader})
#    get_filename_component( dir ${file} DIRECTORY )
#    install (FILES ${file} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PACKAGE}/${dir})
#endforeach ()

