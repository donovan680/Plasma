@echo off
cls
echo ***********************************************************************
echo ****************************** Clang++11 ******************************
echo ***********************************************************************
clang++ -std=c++11  Lightning.cpp main.cpp -o %~n0.exe -l"wsock32" -l"ws2_32" -l"IPHLPAPI" -l"Winmm" -l"Shlwapi" -l"Psapi" > %~n0.log 2>&1
type %~n0.log
echo ****************************** COMPLETED ******************************
pause
