echo >/dev/null # >nul & GOTO WINDOWS & rem ^
@echo off

# Do Linux Bash commands here... for example:

if [ -f "../../build" ]; then
	mkdir ../../build
fi

pushd ../../build
gcc -Wall -g ../Engine/code/main.cpp -L../Engine/res/libs -lglfw3.lib -lopengl32.lib
popd



exit 0
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
:WINDOWS

REM Do Windows CMD commands here... for example:
@ECHO OFF

IF NOT EXIST ..\..\build (mkdir ..\..\build)

pushd ..\..\build
REM NOTE -> CHANGE PATH FOR YOUR COMPILER AND COMPILER SETTINGS
REM -l:libmcfgthread.a since I am using MINGW to compile <- replaces threading library.
C:\SpiderEnv\mingw64\bin\gcc.exe -Wall -g ..\Engine\code\main.cpp -L..\Engine\res\libs -lglfw3 -lopengl32 -lgdi32 
REM -static -l:libmcfgthread.a
popd



REM Then, when all Windows commands are complete... the script is done.
