# Copyright (C) 2022 Joel Fischer

ifeq ($(OS),Windows_NT)
	SHELL := bash.exe
else
	SHELL := /usr/bin/env bash
endif
.SHELLFLAGS := -eo pipefail -c

LD 	:= gcc

FC 	:= gfortran
FFLAGS 	:= -Wall -Wextra -O3

CC	:= gcc
CFLAGS 	:= -Wall -Wextra -O3

CPP	:= g++
CPPFLAGS:= -Wall -Wextra -O3

LDFLAGS := -lgfortran

FMOD 	:= m_lorenz.o
FOBJ 	:= dlsode.o 
MFOBJ 	:= f_lorenz.o
COBJ 	:= test_lorenz.c
CPPOBJ	:=

TARGET 	:= test

$(TARGET) : $(FOBJ) $(MFOBJ) $(FMOD) $(COBJ) $(CPPOBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


$(filter %.o,$(MFOBJ) $(FMOD)): %.o: %.f90 $(FMOD)
	$(FC) $(FFLAGS) $^ $(subst .o,.mod,$(FMOD)) -c

$(filter %.o,$(FOBJ)): %.o: %.f
	$(FC) -w -O3 $^ -c

$(filter %.o,$(COBJ)): %.o: %.c
	$(CC) $(CFLAGS) $^ -c

$(filter %.o,$(CPPOBJ)): %.o: %.cpp
	$(CPP) $(CPPFLAGS) $^ -c


.PHONY: all clean

all: $(TARGET)

clean:
	rm -fv $(wildcard *.exe) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.smod) $(wildcard *.mex*)
