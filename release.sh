#!/bin/bash

set -e  # Exit on any error

#echo "Configuring Git user..."
#git config user.name "Local Test User"
#git config user.email "local@test.com"

echo "Switching to main branch..."
git checkout main

echo "Deleting release branch if it exists..."
git branch -D release || true  # Safely delete release branch if it exists

echo "Creating and switching to release branch..."
git checkout -B release

echo "Checking if lib/SimpleLibrary exists..."
if [ ! -d "lib/SimpleLibrary" ]; then
  echo "Error: lib/SimpleLibrary does not exist. Ensure the folder is present in the repository."
  exit 1
fi

echo "Removing everything except lib/SimpleLibrary..."
find . -mindepth 1 ! -path './lib/SimpleLibrary/*' ! -path './lib/SimpleLibrary' \
  ! -name '.git' ! -name '.gitignore' -exec rm -rf {} +

echo "Moving library contents to the root..."
mv lib/SimpleLibrary/* . || { echo "Error: Failed to move files from lib/SimpleLibrary"; exit 1; }
rm -rf lib

echo "Staging and committing changes..."
git add .
git commit -m "Update release branch" || echo "No changes to commit"

echo "Pushing release branch to origin..."
git push origin release --force

echo "Release branch updated successfully!"
