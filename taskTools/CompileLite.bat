@echo off
taskkill /IM main.exe
forfiles /M *.cpp /c "cmd /c g++ -Wall -std=c++20 *.cpp -o @fname.exe"
pause