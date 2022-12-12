@echo off
cd cdimage
del game.iso
cd..
cls
psymake
pause
.\mkpsxiso\mkpsxiso.exe -o cdimage\Extermination.iso -y .\cuesheet.xml
"C:/psx/psx.exe" "cdimage/Extermination.iso
