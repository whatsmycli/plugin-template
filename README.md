# plugin-template

Official template for developing GPLv3-compatible plugins for **[whatsmy](https://github.com/whatsmycli/whatsmy)**.

## Quick Start

### 1. Clone Template

```bash
git clone https://github.com/whatsmycli/plugin-template.git myplugin
cd myplugin
```

### 2. Implement Plugin

Edit `plugin.cpp`:

```cpp
#include <iostream>

extern "C" {
    int plugin_run() {
        std::cout << "Hello from my plugin!" << std::endl;
        return 0;
    }
}
```

### 3. Build

**Linux/macOS**:
```bash
mkdir build && cd build
cmake ..
make
```

**Windows**:
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 4. Test Locally

Copy binary to plugins directory:

**Linux**:
```bash
sudo mkdir -p /usr/lib/whatsmy/plugins/myplugin
sudo cp build/myplugin.so /usr/lib/whatsmy/plugins/myplugin/linux.so
whatsmy myplugin
```

**Windows** (as Administrator):
```powershell
New-Item -ItemType Directory -Force -Path "C:\Program Files\whatsmy\plugins\myplugin"
Copy-Item build\Release\myplugin.dll "C:\Program Files\whatsmy\plugins\myplugin\windows.dll"
whatsmy myplugin
```

**macOS**:
```bash
sudo mkdir -p /usr/local/lib/whatsmy/plugins/myplugin
sudo cp build/libmyplugin.dylib /usr/local/lib/whatsmy/plugins/myplugin/macos.dylib
whatsmy myplugin
```

## Plugin API

### Required Function

```cpp
extern "C" {
    int plugin_run();  // 0 = success, non-zero = error
}
```

That's it! Keep it simple.

## Pre-Built Binaries

**GitHub Releases** contain pre-built binaries for all platforms:

- Download from the [Releases page](https://github.com/whatsmycli/plugin-template/releases)
- Available platforms: Linux (x86_64), Windows (x64), macOS (Universal Binary)
- Includes SHA256 checksums for verification

## Building for All Platforms

### GitHub Actions (Automated Builds) ✅

This repository includes GitHub Actions workflows that automatically build the plugin for all platforms:

- **Build Workflow** (`.github/workflows/build.yml`): Runs on every push/PR
  - Builds for Linux, Windows, and macOS
  - Uploads artifacts for testing (90-day retention)
  
- **Release Workflow** (`.github/workflows/release.yml`): Runs on version tags
  - Creates GitHub Release automatically
  - Includes binaries for all platforms
  - Generates SHA256 checksums

**To create a release:**
```bash
git tag -a v1.0.0 -m "Release 1.0.0"
git push origin v1.0.0
# GitHub Actions will build and publish automatically!
```

## Submitting

1. Build for all platforms (Linux, Windows, macOS)
2. Test on at least one platform
3. Publish source code publicly
4. Submit PR to [plugins repository](https://github.com/whatsmycli/plugins)

Include:
- Plugin name and description
- Link to source repository
- All three binaries

## Example Plugins

### Hello World

```cpp
#include <iostream>

extern "C" {
    int plugin_run() {
        std::cout << "Hello, World!" << std::endl;
        return 0;
    }
}
```

### Platform-Specific

```cpp
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <unistd.h>
#else
#include <unistd.h>
#endif

extern "C" {
    int plugin_run() {
        #ifdef _WIN32
        std::cout << "Running on Windows" << std::endl;
        #elif __APPLE__
        std::cout << "Running on macOS" << std::endl;
        #else
        std::cout << "Running on Linux" << std::endl;
        #endif
        return 0;
    }
}
```

## Testing Your Plugin

### Local Testing

After building your plugin, test it locally before submitting:

**Option 1: Using WHATSMY_PLUGIN_DIR**

```bash
# Create test directory structure
mkdir -p test-plugins/myplugin

# Copy your built plugin
cp build/myplugin.so test-plugins/myplugin/linux.so

# Test with environment variable
export WHATSMY_PLUGIN_DIR=$(pwd)/test-plugins
whatsmy myplugin
```

**Option 2: Install to system plugins directory**

```bash
# Linux
sudo mkdir -p /usr/lib/whatsmy/plugins/myplugin
sudo cp build/myplugin.so /usr/lib/whatsmy/plugins/myplugin/linux.so
whatsmy myplugin

# Windows (as Administrator)
New-Item -ItemType Directory -Force -Path "C:\Program Files\whatsmy\plugins\myplugin"
Copy-Item build\Release\myplugin.dll "C:\Program Files\whatsmy\plugins\myplugin\windows.dll"
whatsmy myplugin

# macOS
sudo mkdir -p /usr/local/lib/whatsmy/plugins/myplugin
sudo cp build/libmyplugin.dylib /usr/local/lib/whatsmy/plugins/myplugin/macos.dylib
whatsmy myplugin
```

### Testing Checklist

Before submitting your plugin, verify:

- [ ] Plugin compiles cleanly on all platforms (or at least one)
- [ ] No compiler warnings
- [ ] Returns 0 on success
- [ ] Returns non-zero on error conditions
- [ ] Handles exceptions gracefully
- [ ] No memory leaks (use valgrind on Linux)
- [ ] Output is clear and user-friendly
- [ ] Works with whatsmy core application

### Debugging Tips

**Enable Debug Logging**:
```bash
export WHATSMY_DEBUG=1
whatsmy myplugin
```

**Check for Memory Leaks (Linux)**:
```bash
valgrind --leak-check=full whatsmy myplugin
```

**Platform-Specific Issues**:
- Linux: Check library dependencies with `ldd myplugin.so`
- Windows: Use Dependency Walker to check DLL dependencies
- macOS: Use `otool -L libmyplugin.dylib` to check dependencies

## Best Practices

- Keep it simple
- Minimize dependencies
- Handle errors gracefully
- Return 0 on success, non-zero on error
- Test on all platforms before submitting
- Write clear, user-friendly output
- Document any special requirements
- Include examples in your README

## Contributing

We welcome plugin contributions! To submit your plugin:

1. **Develop**: Create your plugin using this template
2. **Test**: Build and test on at least one platform
3. **Document**: Write a clear README explaining what your plugin does
4. **Publish**: Host your source code on GitHub (or similar)
5. **Submit**: Create a PR to the [plugins repository](https://github.com/whatsmycli/plugins)

Include in your PR:
- Plugin name and description
- Link to source code repository
- Platform-specific binaries (linux.so, windows.dll, macos.dylib)
- Any special requirements or dependencies

See [CONTRIBUTING.md](CONTRIBUTING.md) for detailed contribution guidelines.

## Resources

- [whatsmy](https://github.com/whatsmycli/whatsmy) - Main project
- [plugins](https://github.com/whatsmycli/plugins) - Plugin repository
- [plugin-gpu](https://github.com/whatsmycli/plugin-gpu) - Reference implementation

## License

GNU General Public License v3.0
