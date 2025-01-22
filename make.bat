@echo off



cl /c src/*.c
link *.obj user32.lib ntdll.lib advapi32.lib gdi32.lib /SUBSYSTEM:WINDOWS /OUT:installer.exe
del *.obj