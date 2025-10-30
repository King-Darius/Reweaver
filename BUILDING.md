# Building Reweaver

> **Status:** These instructions will continue to evolve while we ship the first Reweaver release. Please report gaps or outdated details so we can keep the guide fresh.

## Requirements & dependencies

You will need the following tooling:

* Git
* CMake
* A package manager (tested: Chocolatey on Windows, Homebrew on macOS)
* A CMake generator (tested: Ninja)
* A C++ compiler (tested: MSVC on Windows, g++/clang on Linux)
* Qt 6.9.1 "Desktop" with the optional modules:
  * Qt 5 Compatibility Module
  * Qt Network Authorization
  * Qt Shader Tools
  * Qt State Machines

Large portions of Reweaver's stack are shared with MuseScore Studio, so their developer environment documentation remains a useful companion reference for the time being.

## Setup

1. [Set up a developer environment](https://github.com/musescore/MuseScore/wiki/Set-up-developer-environment)
2. [Install Qt and Qt Creator](https://github.com/musescore/MuseScore/wiki/Install-Qt-and-Qt-Creator)
3. Clone the Reweaver repository and submodules:

   ```bash
   git clone --recurse-submodules https://github.com/Reweaver/Reweaver.git
   ```

## Get dependencies

If you haven't installed the dependencies listed above, now is the time to do so. Ninja will attempt to pull in additional dependencies automatically; if anything is missing you can inspect the scripts in `buildscripts/ci/<your OS>/` to mirror the CI environment.

> **Note:** The dependency list is still larger than we would like because of legacy pieces that have not yet been untangled from the MuseScore integration.

## Add relevant tools to `PATH`

Ensure Git, CMake, Ninja, your package manager, compiler toolchain and Qt binaries are on your `PATH`. Otherwise you will need to specify explicit paths in the generated `CMakeCache`.

## Compiling

### With Qt Creator

Qt Creator offers the best IntelliSense and debugging experience when working with QML. Open `CMakeLists.txt` in Qt Creator, configure the project with the auto-detected Qt kit, and hit **Build**. Debugging on Windows can be slow; if you primarily work in C++ you may prefer one of the command-line options below.

### From the command line

Standard CMake workflow applies:

```bash
cmake -S . -B build/ [options]   # configure (first build only)
cmake --build build/             # build (every build)
cmake --install build/           # install (after successful builds)
```

### With Visual Studio (Windows only)

Double-click `generate_sln.bat` in the repository root. The script generates a Visual Studio solution in the `build` directory and builds the `install` target. Open `./build/audacity.sln` in Visual Studio and press **F5** to launch Reweaver (the solution name will change once the project rename propagates through CMake).

### With VS Code

> These steps currently focus on Windows. Contributions that document macOS and Linux workflows are welcome.

The default generator is Ninja. Install it ahead of time or adjust `"cmake.generator"` in `.vscode/settings.json`.

1. **Open the workspace.** Press `Ctrl`+`Shift`+`P` and choose “Open Workspace from File”. Select `.vscode/audacity.code-workspace` in the repository root (this will be renamed to match Reweaver in a future cleanup).
2. **Install recommended extensions.** When VS Code loads the workspace it will prompt you to install recommended extensions. You can revisit this later via `Extensions: Show Recommended Extensions` in the command palette.
3. **Configure and build the install target.** Execute `CMake: Configure` from the command palette.
4. **Build and run Reweaver.** Press **F5**. The first run builds and installs everything; subsequent builds are significantly faster, especially when using Ninja.
