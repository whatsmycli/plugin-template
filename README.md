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

## Building for All Platforms

### GitHub Actions (Recommended)

Create `.github/workflows/build.yml`:

```yaml
name: Build Plugin
on: [push, pull_request]
jobs:
  build:
    runs-on: ${{ matrix.os }}
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
    steps:
    - uses: actions/checkout@v3
    - name: Configure
      run: cmake -B build
    - name: Build
      run: cmake --build build --config Release
    - name: Upload
      uses: actions/upload-artifact@v3
      with:
        name: plugin-${{ matrix.os }}
        path: |
          build/*.so
          build/*.dll
          build/*.dylib
          build/Release/*.dll
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

## Best Practices

- Keep it simple
- Minimize dependencies
- Handle errors gracefully
- Return 0 on success, non-zero on error
- Test on all platforms before submitting

## Resources

- [whatsmy](https://github.com/whatsmycli/whatsmy) - Main project
- [plugins](https://github.com/whatsmycli/plugins) - Plugin repository

## License

GNU General Public License v3.0
