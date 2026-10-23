@echo off
setlocal

set "PATH=C:\msys64\ucrt64\bin;%PATH%"

if not exist build mkdir build

set SOURCES=
for %%f in (src\*.c) do call set SOURCES=%%SOURCES%% %%f

gcc -g -std=c23 -Wall -Wextra -Isrc %SOURCES% -o build\Raytracer.exe -lraylib -lopengl32 -lgdi32 -lwinmm
if errorlevel 1 exit /b 1

copy /y C:\msys64\ucrt64\bin\libraylib.dll build\ >nul
echo Built build\Raytracer.exe
