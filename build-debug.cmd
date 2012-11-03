@echo off
call "%VS100COMNTOOLS%vsvars32.bat"
devenv hunspell.sln /Build Debug
xcopy /Y /D Debug\lib\*.lib .\
