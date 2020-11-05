#include <iostream>
#include <sstream>
#include <string>
#include <ios>
#include <list>
#include <algorithm>
#include <cstring>
#include <wchar.h>
#include<chrono>
#include<thread>

#include "headers/libusb-cpp.hpp"

#include "cxxopts/cxxopts.hpp"

#include "usb_functions.h"


int main(int argc, char* argv[])
{
    try {
        cxxopts::Options options("MyProgram", "One line description of MyProgram");
        options.add_options()
                ("d,debug", "Enable debugging") // a bool parameter
                ("e,enumerate", "Enumerate all devices")
                ("v,vid", "VID", cxxopts::value<std::uint16_t>())
                ("p,pid", "PID", cxxopts::value<std::uint16_t>())
                ("m,message", "Mesage", cxxopts::value<std::string>()->default_value({}))                
                ("i,in", "In EndPoint", cxxopts::value<std::uint16_t>()->default_value("1"))
                ("o,out", "Out EndPoint", cxxopts::value<std::uint16_t>()->default_value("1"))
                ("period", "Period, ms", cxxopts::value<std::uint32_t>())
                ;

        auto result = options.parse(argc, argv);

        if (result.arguments().size() == 0) {
            enumerateDevices();
            return 0;
        }

        if (result["enumerate"].as<bool>()) {
            enumerateDevices();
        }

        if (!(result["vid"].count() && result["pid"].count())) {
            return 0;
        }

        auto vid = result["vid"].as<std::uint16_t>();
        auto pid = result["pid"].as<std::uint16_t>();
        auto in =  result["in"].as<std::uint16_t>();
        auto out = result["out"].as<std::uint16_t>();
        auto message = result["message"].as<std::string>();

        // show info about the device
        enumerateDevice(vid, pid);

        if (message.empty()) return 0;
        bool once{true};
        int pause{0};
        if (result["period"].count()) {
            pause = result["period"].as<std::uint32_t>();
            once = false;
        }

        do {
            std::cout << "Sending message: " << message << std::endl;
            auto answer = sendMessage(vid, pid, message, in, out);
            if (once) return 0;
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(pause));
        } while (true);

    }
    catch(cxxopts::OptionParseException const &e) {
        std::wcout << "Wrong argument exception: " << e.what() << std::endl;
    }
    catch(cxxopts::OptionSpecException const &e) {
        std::wcout << "Wrong option spec exception: " << e.what() << std::endl;
    }
    catch(cxxopts::OptionException const &e) {
        std::wcout << "Option exception: " << e.what() << std::endl;
    }
    catch(std::exception const &e) {
        std::wcout << "Unknown error: " << e.what() << std::endl;
    }
    catch (...) {
        std::wcout << "Unknown error" << std::endl;
    }

    return 0;
}


