<#
.SYNOPSIS
    Updates the `main` branch with production-ready library files from the `dev` branch.

.DESCRIPTION
    This script automates the process of preparing the `main` branch for distribution. 
    It cleans up unnecessary files, moves library files from `lib/<LIBRARY_NAME>` to the root directory,
    and force-pushes the updated branch to the remote repository.

.NOTES
    Author: Your Name
    Last Updated: January 2025

.PARAMETER LIBRARY_NAME
    The name of the library directory under `lib`.

.EXAMPLE
    .\update-main.ps1 -LibraryName "SimpleLibrary"
#>

param (
    [string]$LibraryName = "SimpleLibrary"  # Default library name
)

# Exit on any error
$ErrorActionPreference = "Stop"

Write-Host "Switching to dev branch..."
git checkout dev

Write-Host "Deleting main branch if it exists locally..."
try {
    git branch -D main
} catch {
    Write-Host "No existing main branch to delete."
}

Write-Host "Creating and switching to main branch..."
git checkout -B main

Write-Host "Checking if lib/$LibraryName exists in dev branch..."
if (-not (Test-Path "lib/$LibraryName")) {
    Write-Error "Error: lib/$LibraryName does not exist in the dev branch."
    exit 1
}

Write-Host "Removing everything except files specified..."
Get-ChildItem -Path . -Force -Exclude '.git', 'README.md', '.gitignore', "lib" |
    ForEach-Object { Remove-Item -Recurse -Force $_.FullName }

Write-Host "Moving library contents to the root directory..."
Get-ChildItem -Path "lib/$LibraryName/*" | ForEach-Object {
    Move-Item $_.FullName .
}

Write-Host "Cleaning up the lib directory..."
Remove-Item -Recurse -Force lib

Write-Host "Staging and committing changes..."
git add .
try {
    git commit -m "Update main branch"
} catch {
    Write-Host "No changes to commit."
}

Write-Host "Pushing main branch to origin..."
git push origin main --force

Write-Host "Main branch updated successfully!"
