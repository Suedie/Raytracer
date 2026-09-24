@echo off
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
cd /d "%~dp0"

cl /c /I"C:\vcpkg\installed\x64-windows\include" main.c camera.c canvas.c render.c scene.c vector.c light.c
if errorlevel 1 exit /b 1

link /OUT:raytracer.exe main.obj camera.obj canvas.obj render.obj scene.obj vector.obj light.obj ^
    /LIBPATH:"C:\vcpkg\installed\x64-windows\lib" ^
    /LIBPATH:"C:\vcpkg\installed\x64-windows\lib\manual-link" ^
    /SUBSYSTEM:WINDOWS SDL2main.lib SDL2.lib shell32.lib
if errorlevel 1 exit /b 1

copy /Y "C:\vcpkg\installed\x64-windows\bin\SDL2.dll" .
echo Built raytracer.exe
