@echo off



cl /c src/*.c
link *.obj shell32.lib user32.lib ntdll.lib winmm.lib advapi32.lib gdi32.lib /SUBSYSTEM:WINDOWS /OUT:installer.exe
del *.obj