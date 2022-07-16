# Copyright (C) 2022 Joel Fischer

ifeq ($(OS),Windows_NT)
	SHELL := bash.exe
	APPPF := .exe
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

FMOD 	:= lorenz.o
MFOBJ 	:= lorenz_fixed.o lorenz_module_fun.o lorenz_module_param.o lorenz_nested_fun.o lorenz_static_arg.o lorenz_static_file.o
FOBJ	:= dlsode.o
COBJ 	:=
CPPOBJ	:=

TARGET 	:= lorenz_module_fun

main : $(TARGET)

lorenz_module_fun : dlsode.o lorenz_module_fun.o lorenz.o
	$(LD) $(LDFLAGS) $^ -o $@

lorenz_module_param : dlsode.o lorenz_module_param.o lorenz.o
	$(LD) $(LDFLAGS) $^ -o $@

lorenz_nested_fun : dlsode.o lorenz_nested_fun.o  
	$(LD) $(LDFLAGS) $^ -o $@

lorenz_static_arg : dlsode.o lorenz_static_arg.o  
	$(LD) $(LDFLAGS) $^ -o $@

lorenz_static_file : dlsode.o lorenz_static_file.o  
	$(LD) $(LDFLAGS) $^ -o $@

lorenz_fixed : dlsode.o lorenz_fixed.o  
	$(LD) $(LDFLAGS) $^ -o $@

$(filter %.o,$(MFOBJ) $(FMOD)): %.o: %.f90 $(FMOD)
	$(FC) $(FFLAGS) $^ $(subst .o,.mod,$(FMOD)) -c

$(filter %.o,$(FOBJ)): %.o: %.f
	$(FC) -w -O3 $^ -c

$(filter %.o,$(COBJ)): %.o: %.c
	$(CC) $(CFLAGS) $^ -c

$(filter %.o,$(CPPOBJ)): %.o: %.cpp
	$(CPP) $(CPPFLAGS) $^ -c

.PHONY: all clean 

all: clean lorenz_fixed lorenz_static_file lorenz_static_arg lorenz_nested_fun lorenz_module_param lorenz_module_param

clean:
	rm -fv $(wildcard *.exe) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.smod)
