@echo on
set "_OLD_CD=%CD%"
mkdir "%~dp0\..\build"
cd /d "%~dp0\..\build"
call cmake -G "Visual Studio 15 2017 Win64" .. || goto: eof
call cmake --build . || goto: eof
cd /d "%_OLD_CD%"