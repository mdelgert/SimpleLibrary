# Purpose:
# This script automates the creation of a "release" branch for an Arduino or PlatformIO library.
# It moves the library contents to the root directory of the `release` branch, ensuring compatibility 
# with Arduino IDE and PlatformIO while removing unnecessary files. The release branch is updated 
# and pushed to the remote repository for distribution.

# Configurable variables
$LibraryName = "SimpleLibrary"  # Change this to the name of your library

# Enable strict mode to catch errors
Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"  # Exit on any error

# Ensure Git is available
if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
    Write-Error "Git is not installed or not available in the PATH. Please install Git before running this script."
    exit 1
}

Write-Host "Switching to main branch..."
git checkout main

Write-Host "Deleting release branch if it exists..."
try {
    git branch -D release
} catch {
    Write-Host "No existing release branch to delete. Continuing..."
}

Write-Host "Creating and switching to release branch..."
git checkout -B release

Write-Host "Checking if lib/$LibraryName exists in main branch..."
if (-not (Test-Path -Path "lib\$LibraryName")) {
    Write-Error "Error: lib/$LibraryName does not exist in the main branch."
    exit 1
}

Write-Host "Removing everything except files specified..."
Get-ChildItem -Path . -Recurse -Force | ForEach-Object {
    $fullPath = $_.FullName

    # Skip .git folder, .gitignore file, README.md, and lib folder
    if ($fullPath -match "\\.git($|\\)" -or
        $_.Name -eq "README.md" -or
        $_.Name -eq ".gitignore" -or
        $fullPath -like "*\lib\$LibraryName*") {
        Write-Host "Preserving $fullPath"
    } else {
        Remove-Item -Path $fullPath -Recurse -Force -ErrorAction SilentlyContinue
    }
}

Write-Host "Moving library contents to the root directory..."
Get-ChildItem -Path "lib\$LibraryName" -Recurse | ForEach-Object {
    Move-Item -Path $_.FullName -Destination . -Force
}
Remove-Item -Path "lib" -Recurse -Force

Write-Host "Staging and committing changes..."
git add .
try {
    git commit -m "Update release branch"
} catch {
    Write-Host "No changes to commit."
}

Write-Host "Pushing release branch to origin..."
git push origin release --force

Write-Host "Release branch updated successfully!"
