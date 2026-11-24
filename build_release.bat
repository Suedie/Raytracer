@echo off
setlocal

set "PATH=C:\msys64\ucrt64\bin;%PATH%"

if not exist build\release mkdir build\release

set SOURCES=
for %%f in (src\*.c) do call set SOURCES=%%SOURCES%% %%f

rem -ffast-math is used with -fno-finite-math-only because the renderer uses INFINITY as a "no hit" sentinel
gcc -O3 -march=native -flto -fuse-linker-plugin -ffast-math -fno-finite-math-only -funroll-loops -fomit-frame-pointer -DNDEBUG -s -std=c23 -Wall -Wextra -fopenmp -Isrc %SOURCES% -o build\release\Raytracer.exe -lraylib -lopengl32 -lgdi32 -lwinmm
if errorlevel 1 exit /b 1

copy /y C:\msys64\ucrt64\bin\libraylib.dll build\release\ >nul
copy /y C:\msys64\ucrt64\bin\libgomp-1.dll build\release\ >nul
echo Built build\release\Raytracer.exe
