@echo off
SET filestocompile= *.c
SET libs= -lgdi32
gcc %filestocompile% -o main.exe %libs%
main.exe