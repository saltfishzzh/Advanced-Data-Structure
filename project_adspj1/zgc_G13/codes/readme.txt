Data Structure Project 1
Build Guide

You have totally three ways to use the project program.

1. Using the Prebuilt Binary File.

We prebuilt some binary file for several popular system:
(the content in the parentheses is the prebuilt environment)

Windows(x86): project1.win32.exe (Windows 10 Professional 14393; TDM-GCC 5.1.0)
Windows(x64): project1.exe (Windows 10 Professional 14393; TDM-GCC 5.1.0)
Linux(x64): project1 (Ubuntu 14.04; clang 3.5)

2. Using Makefile (Linux & macOS )

$ make

3. Compile Manually

Windows (GCC)

> gcc .\project1.c .\SplayTree.c .\UBTree.c .\AvlTree.c -O0 -std=c99 -o .\project1.exe

Linux / macOS (GCC)
you may need replace the 'CLK_TCK' in project1.c with 'CLOCKS_PER_SEC'

$ gcc project1.c SplayTree.c UBTree.c AvlTree.c -O0 -std=c99 -o project1

Linux / macOS (Clang)
you may need replace the 'CLK_TCK' in project1.c with 'CLOCKS_PER_SEC'
$ clang project1.c SplayTree.c UBTree.c AvlTree.c -O0 -std=c99 -o project1
