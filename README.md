
---

# **SimpleLibrary**

## **Overview**
`SimpleLibrary` is an Arduino-compatible library designed for seamless use in Arduino IDE and PlatformIO. This repository employs a structured development workflow with three branches:
- `dev` for library development and testing.
- `main` for production-ready releases.
- `test` for verifying the library when installed as a dependency via `lib_deps`.

The automated workflow ensures the `main` branch always contains a clean, production-ready version of the library, while the `test` branch verifies the library's usability as a dependency.

---

## **Branching Strategy**

### **1. `dev` Branch**
- Used for **library development and testing**.
- Contains:
  - A complete PlatformIO project structure.
  - The library code under `lib/SimpleLibrary`.
  - Test sketches in the `src` folder.
- Developers work exclusively in this branch.

### **2. `main` Branch**
- Used for **production-ready library releases**.
- Contains only the necessary files for the Arduino IDE or PlatformIO.
- Automatically updated via a GitHub Action whenever changes are pushed to the `dev` branch.

### **3. `test` Branch**
- Used for **end-to-end testing** of the library as an external dependency.
- Contains:
  - A minimal PlatformIO project.
  - A `platformio.ini` file referencing the library via `lib_deps` from GitHub.
  - Allows developers to verify the library works correctly as an external dependency.

---

## **Project Structure**

### **`dev` Branch**
The `dev` branch has the following structure:

```
SimpleLibrary/
├── lib/
│   └── SimpleLibrary/
│       ├── src/
│       │   ├── SimpleLibrary.cpp
│       │   └── SimpleLibrary.h
│       ├── examples/
│       │   ├── HelloWorld/
│       │   │   └── HelloWorld.ino
│       │   └── SimpleCalc/
│       │       └── SimpleCalc.ino
│       ├── library.json
│       ├── library.properties
│       └── LICENSE.txt
├── src/
│   └── main.cpp          # Test code for the library
├── platformio.ini        # PlatformIO configuration file
├── README.md
└── .github/
    └── workflows/
        └── update-main.yml  # GitHub Action to update main branch
```

### **`main` Branch**
After automation, the `main` branch contains the production-ready library:
```
SimpleLibrary/
├── src/
│   ├── SimpleLibrary.cpp
│   └── SimpleLibrary.h
├── examples/
│   ├── HelloWorld/
│   │   └── HelloWorld.ino
│   └── SimpleCalc/
│       └── SimpleCalc.ino
├── library.json
├── library.properties
├── LICENSE.txt
└── README.md
```

### **`test` Branch**
The `test` branch is minimal, referencing the library as an external dependency:
```
SimpleLibrary/
├── src/
│   └── main.cpp          # Test sketch using the library
├── platformio.ini        # References the library from GitHub
└── README.md
```

---

## **Testing with the `test` Branch**

1. **Switch to the `test` Branch**:
   ```bash
   git checkout test
   ```

2. **Structure of `platformio.ini`**:
   Ensure `platformio.ini` references the library from the `main` branch:
   ```ini
   [env:esp32]
   platform = espressif32
   board = esp32dev
   framework = arduino

   lib_deps =
       https://github.com/mdelgert/SimpleLibrary.git
   ```

3. **Write Test Code**:
   In `src/main.cpp`, include and use the library:
   ```cpp
   #include <SimpleLibrary.h>

   SimpleLibrary lib;

   void setup() {
       Serial.begin(115200);
       lib.printHello();
       int result = lib.addNumbers(3, 7);
       Serial.print("Result of 3 + 7: ");
       Serial.println(result);
   }

   void loop() {
       // Do nothing
   }
   ```

4. **Run the Test**:
   - Build and upload the test sketch:
     ```bash
     pio run --target upload
     ```
   - Verify that the library works as expected.

---

## **Automating the `main` Branch Update**

### **GitHub Action**
A GitHub Action automates the process of updating the `main` branch whenever changes are pushed to the `dev` branch. The workflow is saved as `.github/workflows/update-main.yml`:

```yaml
name: Update Main Branch

on:
  push:
    branches:
      - dev

jobs:
  update-main:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout Repository
        uses: actions/checkout@v4

      - name: Configure Git User
        run: |
          git config user.name "GitHub Actions"
          git config user.email "actions@github.com"

      - name: Switch to dev Branch
        run: |
          echo "Switching to dev branch..."
          git checkout dev

      - name: Delete Local Main Branch if Exists
        run: |
          echo "Deleting main branch if it exists locally..."
          git branch -D main || true

      - name: Create and Switch to Main Branch
        run: |
          echo "Creating and switching to main branch..."
          git checkout -B main

      - name: Check if Library Exists
        run: |
          LIBRARY_NAME="SimpleLibrary"
          echo "Checking if lib/$LIBRARY_NAME exists in dev branch..."
          if [ ! -d "lib/$LIBRARY_NAME" ]; then
            echo "Error: lib/$LIBRARY_NAME does not exist in the dev branch."
            exit 1
          fi

      - name: Remove Unnecessary Files
        run: |
          echo "Removing everything except files specified..."
          find . -mindepth 1 \
            -name '.git' -prune -o \
            -name 'README.md' -prune -o \
            -name '.gitignore' -prune -o \
            -path './lib' -prune -o \
            -exec rm -rf {} +

      - name: Move Library Contents to Root Directory
        run: |
          LIBRARY_NAME="SimpleLibrary"
          echo "Moving library contents to the root directory..."
          mv lib/"$LIBRARY_NAME"/* . || { echo "Error: Failed to move files from lib"; exit 1; }
          rm -rf lib

      - name: Stage and Commit Changes
        run: |
          echo "Staging and committing changes..."
          git add .
          git commit -m "Update main branch" || echo "No changes to commit"

      - name: Push Main Branch to Origin
        run: |
          echo "Pushing main branch to origin..."
          git push origin main --force
```

---

## **Benefits of This Workflow**

1. **Cleaner Production (`main`) Branch**:
   - Contains only the necessary files for end users.
   - Compatible with Arduino IDE and PlatformIO.

2. **Efficient Development**:
   - `dev` branch provides a complete development environment with PlatformIO.

3. **End-to-End Testing**:
   - `test` branch allows developers to verify the library as an external dependency.

4. **Automation**:
   - GitHub Actions keeps `main` up-to-date automatically.

---