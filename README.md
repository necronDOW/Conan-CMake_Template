# Gameplay Analytics Tool

## Description
A tool used to aid game designers by visualising positional data in the form of heatmaps and trajectories.  This takes log data from the Battery Collector game.

## Instructions
### Generating Logs
1. Download the BatteryTutorial_UE4 [link](https://github.com/necronDOW/BatteryTutorial_UE4 "repository").
2. Open the "BatteryCollector 4.14/BatteryCollector.uproject" within Unreal Engine version 4.14 or higher.
3. Once loaded, select the "Simulate" button located just above the scene/game view.
4. Play the game, log files will be generated and stored within "BatteryCollector 4.14/Content/Logs".

### Using the Tool
#### Running from IDE
1. If you have not already downloaded this project, do so from [link](https://github.com/necronDOW/Conan-CMake_Template "here").
2. Ensure that Conan.io and CMake 3.0 or higher are installed on your machine.
3. Run "BuildSolution.bat" located within the root directory to create Visual Studio project files.
4. Open "build/Conan-Cmake_Template.sln" in Visual Studio 2015 or higher.
5. Once loaded, select "Local Windows Debugger" from the debug options at the top to run the application.

#### Loading a log file
1. Locate the desired positional data log using Windows File Explorer.
2. Drag and drop the file into the tool window.
3. Follow on screen instructions to set desired display options.

#### Navigation and controls
* Pan the camera using W (up), A (left), S (down) and D (right).
* Zoom in/out using the mouse wheel, this will adjust relative to your mouse position.