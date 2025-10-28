/**
 * whatsmycli Plugin API
 * 
 * This header defines the interface that all whatsmy plugins must implement.
 * 
 * Copyright (C) 2025 enXov
 * Licensed under GPLv3
 */

#ifndef WHATSMY_PLUGIN_API_H
#define WHATSMY_PLUGIN_API_H

/**
 * Plugin API Version
 * 
 * This version number indicates the plugin API version.
 * Increment when making breaking changes to the plugin interface.
 */
#define WHATSMY_PLUGIN_API_VERSION 1

/**
 * Plugin Entry Point
 * 
 * Every plugin MUST implement this function. It is called by the whatsmy
 * core application when the plugin is executed.
 * 
 * Return Values:
 *   0           - Success
 *   Non-zero    - Error (plugin-defined error codes)
 * 
 * Example:
 * 
 *   extern "C" {
 *       int plugin_run() {
 *           std::cout << "Hello from my plugin!" << std::endl;
 *           return 0;
 *       }
 *   }
 * 
 * Notes:
 *   - Use extern "C" linkage for cross-compiler compatibility
 *   - Handle all exceptions within the plugin
 *   - Return appropriate exit codes (0 = success)
 *   - Do NOT throw exceptions across the plugin boundary
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Required: Plugin execution function
 * 
 * @return 0 on success, non-zero on error
 */
int plugin_run(void);

/**
 * Future Optional Functions (not yet implemented in core)
 * 
 * These functions may be added in future versions of the plugin API:
 * 
 * const char* plugin_version(void);      // Plugin version string
 * const char* plugin_description(void);  // Plugin description
 * int plugin_init(void);                 // Initialization hook
 * void plugin_cleanup(void);             // Cleanup hook
 */

#ifdef __cplusplus
}
#endif

#endif // WHATSMY_PLUGIN_API_H

