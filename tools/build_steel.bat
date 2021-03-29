@echo on
set "_OLD_CD=%CD%"
mkdir "%~dp0\..\build"
cd /d "%~dp0\..\build"
call cmake -G "Visual Studio 16 2019" .. || goto: eof
call cmake --build . || goto: eof
cd /d "%_OLD_CD%"
mkdir "build\steel_tests\game_assets"
robocopy "steel_tests\game_assets" "build\steel_tests\game_assets" /s /e