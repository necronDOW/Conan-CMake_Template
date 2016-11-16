@ECHO OFF

FOR %%a IN (.) DO SET dir=%%~nxa

@ECHO -- CPP CHECK --
GOTO :CHECKCPP
:CHECKCPP-END

@ECHO.
@ECHO -- BUILD DIRECTORY CHECK --
GOTO :CREATEBUILD
:CREATEBUILD-END

@ECHO.
@ECHO -- RUNNING CONAN --
conan install ..

@ECHO.
@ECHO -- RUNNING CMAKE --
cmake .. -G "Visual Studio 14 Win64" -DPROJNAME=%dir%

@ECHO.
@ECHO -- BUILDING SOLUTION --
cmake --build . --config Release

@ECHO.
@ECHO -- SOLUTION GENERATED SUCCESSFULLY! --
@ECHO.
PAUSE
EXIT

:CHECKCPP
	@ECHO Searching for main.cpp ...
	IF NOT EXIST main.cpp (
		@ECHO main.cpp not found, creating blank source ...
		TYPE nul > main.cpp
		)
		@ECHO main.cpp created successfully!
	)
	
	GOTO CHECKCPP-END

:CREATEBUILD
	@ECHO Searching for build folder ...
	IF NOT EXIST ./build (
		@ECHO Build folder not found, creating ...
		MD "./build"
		@ECHO Build folder created successfully!
	)
	
	cd ./build
	
	GOTO CREATEBUILD-END