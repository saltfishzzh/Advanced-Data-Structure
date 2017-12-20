Data Structure Project 1
Build Guide

You have totally three ways to use the project program.

1. Using the Prebuilt Binary File.

We prebuilt some binary file for several popular system:
(the content in the parentheses is the prebuilt environment)

Windows(x64): solution1.exe (Windows 10 Professional 14393; TDM-GCC 5.1.0)
Linux(x64): project1 (Ubuntu 14.04; clang 3.5)

2. Compile Manually

Windows (GCC)

> gcc .\solution1.c -O0 -std=c99 -o .\solution1.exe

Linux / macOS (GCC)
you may need replace the 'CLK_TCK' in solution1.c with 'CLOCKS_PER_SEC'

$ gcc solution1.c -O0 -std=c99 -o solution1

Linux / macOS (Clang)
you may need replace the 'CLK_TCK' in solution1.c with 'CLOCKS_PER_SEC'
$ clang solution1.c -O0 -std=c99 -o solution1

* solution 2 is the same.
