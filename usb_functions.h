#ifndef USB_FUNCTIONS_H
#define USB_FUNCTIONS_H

#include <memory>
#include <string>
#include "headers/libusb-cpp.hpp"

void enumerate(std::shared_ptr<LibUSB::Device> pDevice);
void enumerateDevice(std::uint16_t vid, std::uint16_t pid);
void enumerateDevices();
std::optional<std::string> sendMessage(std::uint16_t vid, std::uint16_t pid,
                                       std::string const &message, std::uint16_t in = 1, std::uint16_t out = 2,
                                       int timeout = 500);


#endif // USB_FUNCTIONS_H
