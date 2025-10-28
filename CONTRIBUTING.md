# Contributing to whatsmycli Plugins

Thank you for your interest in contributing to the whatsmycli plugin ecosystem! This document provides guidelines for creating and submitting plugins.

## Plugin Development Process

### 1. Planning Your Plugin

Before you start coding, consider:

- **Purpose**: What information will your plugin provide?
- **Platform Support**: Which platforms will you support (Linux, Windows, macOS)?
- **Dependencies**: What external libraries or APIs will you use?
- **Name**: Choose a clear, descriptive name (lowercase, no spaces)

### 2. Creating Your Plugin

**Use the Template**:
```bash
git clone https://github.com/whatsmycli/plugin-template.git my-plugin-name
cd my-plugin-name
```

**Implement Your Logic**:
- Edit `plugin.cpp` with your plugin code
- Update `CMakeLists.txt` with your plugin name
- Keep dependencies minimal
- Handle errors gracefully

**Update Documentation**:
- Write a clear README explaining what your plugin does
- Include usage examples
- Document any special requirements

### 3. Building and Testing

**Build for Your Platform**:
```bash
mkdir build && cd build
cmake ..
make  # or cmake --build . --config Release on Windows
```

**Test Locally**:
```bash
# Create test directory
mkdir -p test-plugins/myplugin
cp build/myplugin.so test-plugins/myplugin/linux.so

# Test with whatsmy
export WHATSMY_PLUGIN_DIR=$(pwd)/test-plugins
whatsmy myplugin
```

**Quality Checks**:
- [ ] No compiler warnings
- [ ] No memory leaks (run valgrind)
- [ ] Returns 0 on success
- [ ] Handles errors with non-zero return codes
- [ ] Clear and user-friendly output

### 4. Cross-Platform Builds

Ideally, plugins should work on all platforms. You can use GitHub Actions to automate builds:

**Create `.github/workflows/build.yml`**:
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
    - name: Upload Artifacts
      uses: actions/upload-artifact@v3
      with:
        name: plugin-${{ matrix.os }}
        path: |
          build/*.so
          build/*.dll
          build/*.dylib
          build/Release/*.dll
```

This will automatically build your plugin for Linux, Windows, and macOS on every commit.

## Submission Guidelines

### Prerequisites

Before submitting, ensure:

1. **Source Code is Public**: Host on GitHub, GitLab, or similar
2. **License is GPLv3-compatible**: Your plugin must be open source
3. **README Exists**: Clear documentation of what your plugin does
4. **At Least One Binary**: Provide binaries for at least one platform

### Submission Process

1. **Fork the plugins repository**:
   ```bash
   git clone https://github.com/whatsmycli/plugins.git
   ```

2. **Create a directory for your plugin**:
   ```bash
   cd plugins
   mkdir my-plugin-name
   ```

3. **Add your binaries**:
   ```
   my-plugin-name/
   ├── linux.so       (if you built for Linux)
   ├── windows.dll    (if you built for Windows)
   ├── macos.dylib    (if you built for macOS)
   └── README.md      (plugin information)
   ```

4. **Create README.md**:
   ```markdown
   # My Plugin Name
   
   Brief description of what your plugin does.
   
   ## Source Code
   
   https://github.com/yourusername/my-plugin-name
   
   ## Supported Platforms
   
   - [x] Linux
   - [ ] Windows
   - [ ] macOS
   
   ## Usage
   
   ```bash
   whatsmy my-plugin-name
   ```
   
   ## License
   
   GPLv3
   ```

5. **Create Pull Request**:
   - Submit PR to the plugins repository
   - Include description of your plugin
   - Link to source code repository
   - Mention any special requirements

### Review Process

Plugin maintainers will:

1. **Review source code**: Check for quality and security
2. **Test functionality**: Verify the plugin works correctly
3. **Verify license**: Ensure GPLv3 compatibility
4. **Optionally rebuild**: May rebuild from source to verify binaries

Expect feedback within a few days. We may ask for changes before merging.

## Code Quality Standards

### Code Style

- **Clear naming**: Use descriptive variable and function names
- **Comments**: Explain *why*, not *what*
- **Error handling**: Handle all errors gracefully
- **No crashes**: Never crash the main application

### Performance

- **Fast startup**: Plugin should load quickly (< 10ms)
- **Efficient execution**: Minimize resource usage
- **No memory leaks**: Clean up all allocated resources

### Security

- **Input validation**: Validate all external input
- **No unsafe operations**: Avoid buffer overflows, etc.
- **Minimal privileges**: Don't require root/admin unless absolutely necessary

## Best Practices

### Output Formatting

Keep output clean and readable:

```cpp
extern "C" {
    int plugin_run() {
        std::cout << "Component: Value" << std::endl;
        std::cout << "Details:   More info" << std::endl;
        return 0;
    }
}
```

### Error Messages

Be helpful when errors occur:

```cpp
extern "C" {
    int plugin_run() {
        try {
            // Your code here
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "Tip: Check your configuration" << std::endl;
            return 1;
        }
        return 0;
    }
}
```

### Platform Detection

Use standard preprocessor macros:

```cpp
#ifdef _WIN32
    // Windows-specific code
#elif __APPLE__
    // macOS-specific code
#else
    // Linux-specific code
#endif
```

## Plugin Ideas

Looking for inspiration? Consider creating plugins for:

- **Hardware Info**: CPU, RAM, disk, network cards
- **System Info**: OS version, kernel, uptime
- **Development Tools**: Git status, Docker info, language versions
- **Utilities**: Weather, time zones, currency conversion
- **Fun**: Jokes, quotes, fortune cookies

## Getting Help

- **Documentation**: Read the [main README](README.md)
- **Examples**: Study [plugin-gpu](https://github.com/whatsmycli/plugin-gpu)
- **Issues**: Open an issue on GitHub
- **Discussions**: Use GitHub Discussions for questions

## Code of Conduct

Be respectful, inclusive, and constructive in all interactions. We're building this together!

---

Thank you for contributing to whatsmycli! Your plugins help make system information accessible to everyone.

