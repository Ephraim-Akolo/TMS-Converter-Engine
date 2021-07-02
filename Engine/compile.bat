@echo off
gcc -c converter.c
gcc -o main.exe main.c converter.o
main.exe
cmd \k