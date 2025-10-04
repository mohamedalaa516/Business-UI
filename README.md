# Busniess Project

C++ project built using **Visual Studio 2022**.

![Logo](assets/atm.jpg)

## Description
This is a simple project for managing data (or a short description of your project).  
The goal is to practice C++, data management, and optionally use ImGui/SFML for GUI.

## Requirements
- Windows 10 or later
- Visual Studio 2022
- C++ Desktop Development workload
- [MSBuild](https://learn.microsoft.com/en-us/visualstudio/msbuild/msbuild?view=vs-2022) (comes with VS)

## Build Instructions
1. Open the project in Visual Studio 2022.
2. Choose **Release** or **Debug** configuration.
3. Build the project via **Build > Build Solution** or press `Ctrl+Shift+B`.

### Using GitHub Actions (CI)
The project is set up with **GitHub Actions** to automatically build on Windows.  
- Every push to the `master` branch triggers a build.
- The CI workflow file is located at `.github/workflows/ci.yml`.

## Running the Project
- After building, run the `.exe` file from the `Release` or `Debug` folder.

## Running Tests (Optional)
- If you have Unit Tests, run them after building:
```powershell
path\to\your_tests.exe
