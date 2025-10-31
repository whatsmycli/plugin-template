# plugin-template

Write your first whatsmycli plugin in under 10 minutes.

## Quick Start

```bash
# 1. Clone template
git clone https://github.com/whatsmycli/plugin-template.git myplugin
cd myplugin

# 2. Edit plugin.cpp - implement your logic
# 3. Build
mkdir build && cd build
cmake ..
make

# 4. Test locally
mkdir -p ~/test-plugins/myplugin
cp linux.so ~/test-plugins/myplugin/
export WHATSMY_PLUGIN_DIR=~/test-plugins
whatsmy myplugin
```

## Plugin API

One function. That's it.

```cpp
extern "C" {
    int plugin_run() {
        // Your code here
        return 0;  // 0 = success, non-zero = error
    }
}
```

**Return codes:**
- `0` = Success
- `1` = General error
- `2+` = Custom error codes

**Error handling & platform detection:** See `plugin.cpp` for complete examples.

## Debugging

Enable verbose output to troubleshoot your plugin:

```bash
export WHATSMY_DEBUG=1
whatsmy myplugin
```

Or use the debug flag:
```bash
whatsmy --debug myplugin
```

## Build

**Linux/macOS:**
```bash
mkdir build && cd build
cmake ..
make
```

**Windows:**
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

**Cross-platform builds:** This template includes GitHub Actions workflows that automatically build your plugin for all platforms when you push code. Check `.github/workflows/` for the automation.

## Submit Your Plugin

1. Push source code to GitHub (workflows will build for all platforms automatically)
2. Download binaries from GitHub Actions artifacts
3. Submit PR to [plugins repository](https://github.com/whatsmycli/plugins)

## License

GPLv3
