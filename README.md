# SimpleLibrary
Comprehensive Guide Creating a Simple PlatformIO Library from Scratch with Release Branch

This document explains how to create a simple PlatformIO library from scratch, organize your repository for testing, and automate the creation of a `release` branch for sharing your library with others via `lib_deps`. The library will perform a basic function, such as printing "Hello, World!" or performing a simple calculation, while following best practices for compatibility with both Arduino and PlatformIO.

---

## 1. Folder Structure

Create a new project:
```bash
pio project init --board esp32-s3-devkitc-1 --project-option "platform=espressif32@6.9.0" --project-option "framework=arduino"
```

The following folder structure is recommended for developing your PlatformIO library and testing it in a single repository:

```
SimpleLibrary/
|
├── lib/                        # Library development folder
│   ├── SimpleLibrary/          # Library folder (develop here)
│   │   ├── src/                # Core library source files
│   │   │   ├── SimpleLibrary.cpp
│   │   │   └── SimpleLibrary.h
│   │   ├── examples/           # Example sketches
│   │   │   ├── HelloWorld/
│   │   │   │   └── HelloWorld.ino
│   │   │   └── SimpleCalc/
│   │   │       └── SimpleCalc.ino
│   │   ├── library.json        # Metadata for PlatformIO
│   │   ├── library.properties  # Metadata for Arduino IDE
│   │   └── LICENSE.txt         # License
|
├── src/                        # PlatformIO test project
│   └── main.cpp                # Test code for the library
|
├── platformio.ini              # PlatformIO configuration file
├── README.md                   # Documentation
├── .gitignore                  # Git ignore rules
└── .github/
    └── workflows/
        └── release-branch.yml  # GitHub Action for automating `release` branch
```

---

## 2. Creating the Simple Library

### 2.1 Library Code
Create the library files in `lib/SimpleLibrary/src/`:

#### `SimpleLibrary.h`
```cpp
#ifndef SIMPLE_LIBRARY_H
#define SIMPLE_LIBRARY_H

#include <Arduino.h>

class SimpleLibrary {
public:
    SimpleLibrary();
    void printHello();
    int addNumbers(int a, int b);
};

#endif // SIMPLE_LIBRARY_H
```

#### `SimpleLibrary.cpp`
```cpp
#include "SimpleLibrary.h"

SimpleLibrary::SimpleLibrary() {
    // Constructor
}

void SimpleLibrary::printHello() {
    Serial.println("Hello, World!");
}

int SimpleLibrary::addNumbers(int a, int b) {
    return a + b;
}
```

### 2.2 Example Sketches
Add example sketches to demonstrate the library’s functionality.

#### `examples/HelloWorld/HelloWorld.ino`
```cpp
#include <SimpleLibrary.h>

SimpleLibrary lib;

void setup() {
    Serial.begin(115200);
    lib.printHello();
}

void loop() {
    // Do nothing
}
```

#### `examples/SimpleCalc/SimpleCalc.ino`
```cpp
#include <SimpleLibrary.h>

SimpleLibrary lib;

void setup() {
    Serial.begin(115200);
    int result = lib.addNumbers(5, 7);
    Serial.print("Result of 5 + 7: ");
    Serial.println(result);
}

void loop() {
    // Do nothing
}
```

---

## 3. Setting Up PlatformIO for Testing

### 3.1 Test Code
Write test code in the PlatformIO `src/main.cpp` file:

#### `src/main.cpp`
```cpp
#include <Arduino.h>
#include <SimpleLibrary.h>

SimpleLibrary lib;

void setup() {
    Serial.begin(115200);
    lib.printHello();

    int result = lib.addNumbers(10, 20);
    Serial.print("Result of 10 + 20: ");
    Serial.println(result);
}

void loop() {
    // Do nothing
}
```

### 3.2 PlatformIO Configuration
Update `platformio.ini` for your test environment:
```ini
[env:esp32]
platform = espressif32
board = esp32dev
framework = arduino
```

---

## 4. Automating the `release` Branch

### 4.1 GitHub Action to Automate the `release` Branch

Create the following GitHub Action file in `.github/workflows/release-branch.yml`:

```yaml
name: Update Release Branch

on:
  push:
    branches:
      - main

jobs:
  update-release:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout Code
        uses: actions/checkout@v3

      - name: Prepare Release Branch
        run: |
          git config user.name "GitHub Actions"
          git config user.email "actions@github.com"

          # Create or switch to release branch
          git checkout -B release

          # Remove everything except the library folder
          find . -mindepth 1 ! -regex '^./lib/SimpleLibrary\(.*\)?' ! -name '.git' ! -name '.gitignore' -exec rm -rf {} +

          # Move library contents to the root
          mv lib/SimpleLibrary/* .
          rm -rf lib

          # Commit changes
          git add .
          git commit -m "Update release branch" || echo "No changes to commit"
          git push origin release --force
```

---

## 5. Sharing the Library

### PlatformIO Users
To use your library, users can add the following to their `platformio.ini`:
```ini
lib_deps = https://github.com/yourusername/SimpleLibrary.git#release
```

### Arduino IDE Users
- Download the repository and copy the `lib/SimpleLibrary` folder to their Arduino `libraries/` directory.

---

## 6. Testing the Workflow

1. Develop your library in `lib/SimpleLibrary`.
2. Push changes to the `main` branch.
3. Verify that the GitHub Action updates the `release` branch.
4. Test installing the library via `lib_deps` in another PlatformIO project:
   ```ini
   lib_deps = https://github.com/yourusername/SimpleLibrary.git#release
   ```

---

## 7. Best Practices

1. **Use Semantic Versioning**:
   - Update the `version` field in `library.json` for each release.

2. **Document Everything**:
   - Include clear instructions in `README.md` for installing and using the library.

3. **Automate as Much as Possible**:
   - Use the GitHub Action for consistent updates to the `release` branch.

4. **Test Thoroughly**:
   - Regularly test the library in the `main` branch using your test project.

---

By following this guide, you can create, test, and distribute a simple PlatformIO library efficiently, ensuring compatibility with both Arduino IDE and PlatformIO. This workflow can be expanded for more complex libraries in the future.

