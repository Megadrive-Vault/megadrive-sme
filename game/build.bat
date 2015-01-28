@echo off
..\compiler\bin\compiler.exe %CD%\data\
set GAME_PATH=%CD:\=/%
cd ..
cd sgdk
call build.bat
set CUR_CD=%CD:\=/%
set GDK=%CUR_CD%
set GDK_WIN=%CUR_CD%
set OLD_PATH=%PATH%
set PATH=%GDK_WIN%\bin;%PATH%
cd ..
cd sme
call build.bat
set SME_PATH=%CD:\=/%
cd %GAME_PATH%
make -f makefile.gen
set PATH=%OLD_PATH%
