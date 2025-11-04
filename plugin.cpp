/**
 * Example Plugin Template for whatsmycli
 * 
 * This is a simple example plugin that demonstrates:
 * - Plugin API v2 with argument support
 * - Basic plugin_run() implementation
 * - Platform detection
 * - Error handling
 * - Return codes
 * 
 * Copyright (C) 2025 enXov
 * Licensed under GPLv3 - see LICENSE file
 */

#include <iostream>
#include <string>

// Platform detection
#ifdef _WIN32
    #define PLATFORM_NAME "Windows"
    #include <windows.h>
#elif __APPLE__
    #define PLATFORM_NAME "macOS"
    #include <unistd.h>
    #include <sys/utsname.h>
#else
    #define PLATFORM_NAME "Linux"
    #include <unistd.h>
    #include <sys/utsname.h>
#endif

/**
 * Get system information (platform-specific)
 */
std::string get_system_info() {
    std::string info;
    
#ifdef _WIN32
    // Windows implementation
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    
    // Note: GetVersionEx is deprecated but used here for example simplicity
    // Real plugins should use modern APIs
    #pragma warning(disable: 4996)
    if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
        info = "Windows " + std::to_string(osvi.dwMajorVersion) + 
               "." + std::to_string(osvi.dwMinorVersion);
    } else {
        info = "Windows (version unknown)";
    }
    #pragma warning(default: 4996)
#else
    // Unix-like systems (Linux, macOS)
    struct utsname buffer;
    if (uname(&buffer) == 0) {
        info = std::string(buffer.sysname) + " " + 
               std::string(buffer.release);
    } else {
        info = PLATFORM_NAME;
    }
#endif
    
    return info;
}

/**
 * Plugin entry point with argument support (API v2)
 * 
 * This function is called by whatsmy when the plugin is executed.
 * 
 * @param argc Number of arguments passed to the plugin
 * @param argv Array of argument strings
 *             argv[0] is the plugin name
 *             argv[1..argc-1] are additional arguments
 * 
 * Return values:
 *   0 = Success
 *   1 = General error
 *   Other non-zero values = Custom error codes
 * 
 * Example usage:
 *   whatsmy example          -> argc=1, argv[0]="example"
 *   whatsmy example John     -> argc=2, argv[0]="example", argv[1]="John"
 *   whatsmy example foo bar  -> argc=3, argv[0]="example", argv[1]="foo", argv[2]="bar"
 */
extern "C" {
    int plugin_run(int argc, char* argv[]) {
        try {
            // Print plugin information
            std::cout << "==================================" << std::endl;
            std::cout << "  Example Plugin for whatsmycli  " << std::endl;
            std::cout << "  API Version: 2.0 (with args)  " << std::endl;
            std::cout << "==================================" << std::endl;
            std::cout << std::endl;
            
            // Display arguments received
            std::cout << "Arguments received: " << argc << std::endl;
            for (int i = 0; i < argc; i++) {
                std::cout << "  argv[" << i << "] = " << argv[i] << std::endl;
            }
            std::cout << std::endl;
            
            // Show platform information
            std::cout << "Platform: " << PLATFORM_NAME << std::endl;
            std::cout << "System:   " << get_system_info() << std::endl;
            std::cout << std::endl;
            
            // Example: Greet user if name is provided as argument
            if (argc >= 2) {
                std::cout << "Hello to you too, " << argv[1] << "!" << std::endl;
            } else {
                std::cout << "Hello, World!" << std::endl;
                std::cout << "Try: whatsmy example YourName" << std::endl;
            }
            std::cout << std::endl;
            
            // Example: Demonstrate error handling
            std::cout << "Tip: Return 0 for success, non-zero for errors." << std::endl;
            
            // Success!
            return 0;
            
        } catch (const std::exception& e) {
            // Handle exceptions gracefully
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            // Catch any other exceptions
            std::cerr << "Unknown error occurred" << std::endl;
            return 1;
        }
    }
}
