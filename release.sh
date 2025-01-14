#!/bin/bash

# Purpose:
# This script automates the creation of a "release" branch for an Arduino or PlatformIO library. 
# It moves the library contents to the root directory of the `release` branch, ensuring compatibility 
# with Arduino IDE and PlatformIO while removing unnecessary files. The release branch is updated 
# and pushed to the remote repository for distribution.

# Why This Script Was Created:
# - Arduino IDE requires libraries to have a specific structure with files like `src/` and `examples/` at the root.
# - PlatformIO users also benefit from the streamlined structure for `lib_deps` installation.
# - Manually updating the `release` branch is error-prone and tedious; this script automates the process.

# Functionality:
# - Deletes an existing `release` branch if it exists.
# - Creates a new `release` branch based on `main`.
# - Moves the contents of a specific library folder (`lib/<LIBRARY_NAME>`) to the root directory.
# - Removes unnecessary files and folders while preserving `.git`, `.gitignore`, and `README.md`.
# - Stages and commits the changes, then pushes the updated `release` branch to the remote repository.

set -e  # Exit on any error

# Configurable variables
LIBRARY_NAME="SimpleLibrary"  # Change this to the name of your library

echo "Switching to main branch..."
git checkout main

echo "Deleting release branch if it exists..."
git branch -D release 2>/dev/null || true  # Safely delete release branch if it exists

echo "Creating and switching to release branch..."
git checkout -B release

echo "Checking if lib/$LIBRARY_NAME exists in main branch..."
if [ ! -d "lib/$LIBRARY_NAME" ]; then
  echo "Error: lib/$LIBRARY_NAME does not exist in the main branch."
  exit 1
fi

echo "Removing everything except files specified."
find . -mindepth 1 \
  -name '.git' -prune -o \
  -name 'README.md' -prune -o \
  -name '.gitignore' -prune -o \
  -path './lib' -prune -o \
  -exec rm -rf {} +

echo "Moving library contents to the root directory..."
mv lib/"$LIBRARY_NAME"/* . || { echo "Error: Failed to move files from lib"; exit 1; }
rm -rf lib

echo "Staging and committing changes..."
git add .
git commit -m "Update release branch" || echo "No changes to commit"

echo "Pushing release branch to origin..."
git push origin release --force

echo "Release branch updated successfully!"
