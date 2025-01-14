#!/bin/bash

set -e  # Exit on any error

# Configurable variables
LIBRARY_NAME="SimpleLibrary"  # Change this to the name of your library

echo "Configuring Git user..."
git config user.name "Matthew Elgert"
git config user.email "mdelgert@yahoo.com"

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

echo "Removing everything except .git, .gitignore, and lib/$LIBRARY_NAME..."
find . -mindepth 1 \
  -name '.git' -prune -o \
  -name '.gitignore' -prune -o \
  -path "./lib/$LIBRARY_NAME" -prune -o \
  -path "./lib/$LIBRARY_NAME/*" -prune -o \
  -exec rm -rf {} +

echo "Moving library contents to the root directory..."
mv lib/"$LIBRARY_NAME"/* . || { echo "Error: Failed to move files from lib/$LIBRARY_NAME"; exit 1; }
rm -rf lib

echo "Staging and committing changes..."
git add .
git commit -m "Update release branch" || echo "No changes to commit"

echo "Pushing release branch to origin..."
git push origin release --force

echo "Release branch updated successfully!"
