#!/bin/bash

set -e  # Exit on any error

echo "Configuring Git user..."
git config user.name "Matthew Elgert"
git config user.email "mdelgert@yahoo.com"

echo "Switching to main branch..."
git checkout main

echo "Deleting release branch if it exists..."
git branch -D release 2>/dev/null || true  # Safely delete release branch if it exists

echo "Creating and switching to release branch..."
git checkout -B release

echo "Checking if lib/SimpleLibrary exists in main branch..."
if [ ! -d "lib/SimpleLibrary" ]; then
  echo "Error: lib/SimpleLibrary does not exist in the main branch."
  exit 1
fi

echo "Cleaning up any leftover temporary files..."
rm -rf /tmp/SimpleLibrary
mkdir -p /tmp/SimpleLibrary

echo "Moving lib/SimpleLibrary contents to a temporary location..."
cp -R lib/SimpleLibrary/* /tmp/SimpleLibrary/

echo "Removing everything else..."
find . -mindepth 1 \
  ! -name '.git' \
  ! -name '.gitignore' \
  -exec rm -rf {} +

echo "Restoring library contents to root directory..."
cp -R /tmp/SimpleLibrary/* .
rm -rf /tmp/SimpleLibrary

echo "Staging and committing changes..."
git add .
git commit -m "Update release branch" || echo "No changes to commit"

echo "Pushing release branch to origin..."
git push origin release --force

echo "Release branch updated successfully!"
