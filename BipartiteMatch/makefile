# makefile for HopcroftKarp class
# implementing Hopcroft-Karp algorithm
#
# Copyright (c) 2014 Marshall Farrier
# license http://opensource.org/licenses/gpl-license.php GNU Public License
#
# Author Marshall Farrier
# Since 2014-05-23

CC = g++
CFLAGS = -Wall
CPPFLAGS = -std=c++11 -Iinclude
PROG1 = maxmatch
PROG2 = hungarian
ODIR = obj
BDIR = bin
LDIR = lib
CPPFLAGSTEST = $(CPPFLAGS)

vpath %.cpp src tst

.PHONY: all
all: directories $(PROG1)_test $(PROG2)_test

.PHONY: directories
directories:
	mkdir -p ./$(BDIR)
	mkdir -p ./$(ODIR)

$(PROG1)_test: $(ODIR)/$(PROG1)_test.o $(ODIR)/$(PROG1).o $(LDIR)/index.o
	$(CC) $(CFLAGS) $^ -o $(BDIR)/$@

$(ODIR)/$(PROG1).o: $(PROG1).cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(ODIR)/$(PROG1)_test.o: $(PROG1)_test.cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGSTEST) -c $< -o $@

$(PROG2)_test: $(ODIR)/$(PROG2)_test.o $(ODIR)/$(PROG2).o $(LDIR)/index.o
	$(CC) $(CFLAGS) $^ -o $(BDIR)/$@

$(ODIR)/$(PROG2).o: $(PROG2).cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(ODIR)/$(PROG2)_test.o: $(PROG2)_test.cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGSTEST) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
