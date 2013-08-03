#**************************************
	C-Memo: A C Memoization Library
#**************************************
By: Benjamin D. Nye
Source: www.seas.upenn.edu/~benjamid/
License: http://www.apache.org/licenses/LICENSE-2.0

Description: A function memoization library for C, meant to make caching the values
of functions relatively straightforward and simple.

Attribution: While not required, it would be preferable to give attribution when using this code,
particularly if the code is used for academic purposes.  To cite this code library, please cite the
manual as per:

Nye, B.D. (2011). C-Memo: A Generic Function Memoization Library for C (Manual).  Retrieved from: www.seas.upenn.edu/~benjamid/ on (Date Retrieved).

------------------------------------
	Contents of this Package
------------------------------------

Core Library Files:
#-----------------------------------
A. macro_utilities.h - C preprocessor (CPP) macros used to build memoization macro
B. memoization.h - Memoization library header.  Contains CPP macro for memoizing functions and function headers.
C. memoization.c - Implementation of memoization function cache management and access.
	
Required 3rd Party Libraries:
--------------------------------------
A. khash.h (MIT License, Author: Attractive Chaos) - Lightweight header-only hash map implementation
B. Murmur_hash3 - (Public Domain, Author: Austin Appleby) - Simple well-behaved hash key generator for C

Testing Files (Optional):
--------------------------------------
A. MemoizationTests.c - A simple set of performance and verification (sanity) tests, memoizing a factorial function.
B. Makefile - A simple makefile for compiling the tests

Documentation:
---------------------------------------
A. Readme.txt - The file you are reading at this very moment!
B. C-MemoManual.pdf - A brief manual about the usage of this library.