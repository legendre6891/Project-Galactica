#----------------------------------------------------------
# MemoizationTests Makefile
#----------------------------------------------------------
# Date: 10/1/2011
# Author: Ben Nye
# License: Apache License, Version 2.0

#***********Description***********: 	
# This make file builds c objects from the memoization library and compiles a test example (using factorials)

#***********Typical Usage*********:
# Compiling: 				make -f Makefile
# Cleaning out bad build:	make -f Makefile clean (deletes built files in directory, including exes)


# Add -pg for profiling with gprof
#PG_FLAG = -pg
PG_FLAG = 
CC=gcc -pipe -g $(PG_FLAG) -Wall

# Objects and Resources
#---------------------------------------------
OBJS=murmur_hash3.o memoization.o

# Make Options
#---------------------------------------------
all: memoizationTests.exe

#*****Compile Tests****:
memoizationTests.exe: MemoizationTests.c $(OBJS)
	$(CC) -static $(OBJS) fib.c -o memoizationTests.exe
#********Clean*********:	
clean:
	rm -f *.o *.obj
	rm -f *.exe
