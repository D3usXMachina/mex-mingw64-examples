ifeq ($(OS),Windows_NT)
	SHELL := bash.exe
else
	SHELL := /usr/bin/env bash
endif
.SHELLFLAGS := -eo pipefail -c

FC 		:= gfortran
FFLAGS 	:= -Wall -Wextra

CC 		:= gcc
CFLAGS 	:= -Wall -Wextra

CPP		:= g++
CPPFLAGS:= -Wall -Wextra

LDFLAGS :=

FOBJ 	:=
COBJ 	:= timestwo.o test_timestwo.o
CPPOBJ	:=

TARGET 	:= test.exe

$(TARGET): $(FOBJ) $(COBJ) $(CPPOBJ)
	$(CC) $(LDFLAGS) $(FOBJ) $(COBJ) $(CPPOBJ) -o $(TARGET)

$(filter %.o,$(FOBJ)): %.o: %.f90
	$(FC) $(FFLAGS) $^ -c -o $@

$(filter %.o,$(COBJ)): %.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

$(filter %.o,$(CPPOBJ)): %.o: %.cpp
	$(CPP) $(CPPFLAGS) $^ -c -o $@

.PHONY: all clean

all: $(TARGET)

clean:
	rm -fv $(wildcard *.exe) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.smod)
