#!/bin/bash

set -e  # Exit on any error

# Set repository root
REPO_ROOT="$(git rev-parse --show-toplevel)"

if [ -z "$REPO_ROOT" ]; then
  echo "Error: Not inside a Git repository. Please run this script from within a valid Git repository."
  exit 1
fi

echo "Changing to repository root: $REPO_ROOT"
cd "$REPO_ROOT"

echo "Configuring Git user..."
git config user.name "Local Test User"
git config user.email "local@test.com"

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
git --work-tree="$REPO_ROOT" --git-dir="$REPO_ROOT/.git" add .
git --work-tree="$REPO_ROOT" --git-dir="$REPO_ROOT/.git" commit -m "Update release branch" || echo "No changes to commit"

echo "Pushing release branch to origin..."
git --work-tree="$REPO_ROOT" --git-dir="$REPO_ROOT/.git" push origin release --force

echo "Release branch updated successfully!"
