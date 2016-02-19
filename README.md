# SignalCraft-Designer

A flowchart builder for programming our hardware DSP project.

## Installing the dev environment

### On windows:
- Install Qt
  - Download: http://www.qt.io/download-open-source/
  - At minimum, install the latest version of Qt 5.5 for MinGW with OpenGL, and the latest version of MinGW in Tools (unless you already have MinGW 32 bit).
- Get the repository using git (https://git-scm.com/downloads)

#### Building from command line (first time)
- Set up Path
  - For permanent setup, add two entries to the Path variable: `C:\path_to_Qt\5.5\mingw492_32\bin` and `C:\path_to_Qt\Tools\mingw492_32\bin`
  - Otherwise, you can temporarily set up the path for the current terminal by running `"C:\path_to_Qt\5.5\mingw492_32\bin\qtenv2.bat"`
- In the repo directory:
```
mkdir build
cd build
qmake ..\SignalCraft.pro -r
mingw32-make
```

#### Building with the Qt Creator IDE (first time)
- Open Qt Creator
- Click "Open Project", and navigate to SignalCraft.pro
- In the "Configure Project" dialog, a kit called "Desktop Qt 5.5.X MinGW 32bit" should be set up for you. Otherwise you will have to set it up manually by navigating to qmake and g++ inside the Qt install directory.
- You can modify the default build directories by clicking "Details"
- Click "Configure Project" and everything should work as expected

### On Debian/Ubuntu/Mint (apt-get)

- Run `sudo apt-get install build-essential qt5-default`
- Get the repository using git (`sudo apt-get install git`)

#### Building from the command line

- In the repo directory:
```
mkdir build
cd build
qmake ../SignalCraft.pro -r
make
```

#### Building with the Qt Creator IDE

- Run `sudo apt-get install qtcreator`
- Run `qtcreator`
- Click "Open Project", and navigate to SignalCraft.pro
- In the "Configure Project" dialog, a kit called "Desktop" should be set up for you. Otherwise you will have to set it up manually by navigating to qmake and g++ inside the Qt install directory.
- You can modify the default build directories by clicking "Details"
- Click "Configure Project" and everything should work as expected
