@echo off
call "%VS100COMNTOOLS%vsvars32.bat"
devenv hunspell.sln /Build Release
xcopy /Y /D Release\lib\*.lib .\
