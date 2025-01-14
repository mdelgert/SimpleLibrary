
---

### **Release Script Documentation**

#### **Purpose**
This script:
1. **Prepares the library for distribution**:
   - Moves the library contents from `lib/<LIBRARY_NAME>` to the root directory of the `release` branch.
   - Removes unnecessary files and folders to streamline the structure.

2. **Automates the release process**:
   - Simplifies creating a clean and correctly structured `release` branch for Arduino IDE and PlatformIO.

#### **Key Configurable Variable**
- `LIBRARY_NAME`: Set this to the name of your library (e.g., `MyLibrary`).

#### **Usage Instructions**
1. Save the script as `release.sh` in the root directory of your repository.
2. Make it executable:
   ```bash
   chmod +x release.sh
   ```
3. Run the script:
   ```bash
   ./release.sh
   ```
4. The script will:
   - Delete the existing `release` branch (if it exists).
   - Create a new `release` branch from `main`.
   - Move library contents to the root.
   - Push the updated `release` branch to the remote repository.

---

### **Example Directory Structure After Running the Script**
If the library is named `SimpleLibrary`, the `release` branch will look like this:
```
release/
├── src/
│   ├── SimpleLibrary.cpp
│   └── SimpleLibrary.h
├── examples/
│   ├── HelloWorld/
│   │   └── HelloWorld.ino
│   ├── SimpleCalc/
│   │   └── SimpleCalc.ino
├── library.json
├── library.properties
├── LICENSE
├── README.md
```

---

### **Why This Script is Important**
- **Arduino IDE Compliance**: Ensures the `release` branch structure is compatible with the Arduino IDE, which expects library files at the root.
- **PlatformIO Users**: Simplifies installation via `lib_deps`.
- **Automation**: Reduces manual errors when preparing the library for distribution.