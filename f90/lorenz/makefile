# Copyright (C) 2022 Joel Fischer

ifeq ($(OS),Windows_NT)
	SHELL := bash.exe
else
	SHELL := /usr/bin/env bash
endif
.SHELLFLAGS := -eo pipefail -c

LD 	:= gfortran

FC	:= gfortran
FFLAGS 	:= -Wall -Wextra -O3

CC 	:= gcc
CFLAGS 	:= -Wall -Wextra

CPP	:= g++
CPPFLAGS:= -Wall -Wextra

LDFLAGS :=

mFOBJ 	:= lorenz.o
FOBJ	:= dlsode.o
COBJ 	:=
CPPOBJ	:=

TARGET 	:= test.exe

$(TARGET): $(FOBJ) $(mFOBJ) $(COBJ) $(CPPOBJ)
	$(LD) $(LDFLAGS) $(FOBJ) $(mFOBJ) $(COBJ) $(CPPOBJ) -o $(TARGET)

$(filter %.o,$(mFOBJ)): %.o: %.f90
	$(FC) $(FFLAGS) $^ -c -o $@

$(filter %.o,$(FOBJ)): %.o: %.f
	$(FC) $(FFLAGS) $^ -c -o $@

$(filter %.o,$(COBJ)): %.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

$(filter %.o,$(CPPOBJ)): %.o: %.cpp
	$(CPP) $(CPPFLAGS) $^ -c -o $@

.PHONY: all clean 

all: clean $(TARGET)

clean:
	rm -fv $(wildcard *.exe) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.smod)
