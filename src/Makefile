.PHONY: all clean

# Required fgl variables
FGL_VERSION		= 1.0.0
FGL_API 	    = 100

# Define fgl source code path
FGL_SRC_PATH	   ?= ../src

# Define the output directory for the library
FGL_RELEASE_PATH	?= $(FGL_SRC_PATH)

# Library type for fgl: STATIC (.a) or SHARED (.so/.dll)
FGL_LIBTYPE 		?= SHARED

# Build mode for fgl
FGL_BUILD_MODE 	?= RELEASE

# Build output name for the library
FGL_LIB_NAME 	?= FGL

USE_WAYLAND_DISPLAY ?= FALSE

# Determine if the file has root access only for installing stugex
# whoami prints the name of the user that calls it.
ROOT = $(shell whoami)

HOST_PLATFORM_OS ?= LINUX

# Define the C compiler
CC = gcc

# Define compiler flags
# -O1: optimization level
# -g: include debug information
# -s: strip unnecesary data
# -Wall: turns most compiler warnings
# -std=c99: defines C language mode (standard C from 1999)
# -Wno-missing-braces: ignore invalid warnings
CFLAGS += -Wall -Wno-missing-braces -std=c99 -fPIC

ifeq ($(FGL_BUILD_MODE),DEBUG)
	CFLAGS += -g
endif

ifeq ($(FGL_BUILD_MODE),RELEASE)
	CFLAGS += -s -O1
endif

# Libraries used
LDLIBS = -lGL -lglfw -lm
INCLUDE_PATHS = -I. -I/usr/include/GL -I/usr/include/GLFW

# Define objects required in compilation
OBJS = core.o \
	   shapes.o \
	   sprites.o \
	   text.o

# Default target entry
all: fgl

# Compile stugex library
fgl: $(OBJS)

ifeq ($(FGL_LIBTYPE),SHARED)
	$(CC) -shared -o $(FGL_RELEASE_PATH)/lib$(FGL_LIB_NAME).so.$(FGL_VERSION) $(OBJS) -Wl,-soname,lib$(FGL_LIB_NAME).so.$(FGL_API) -lc $(LDLIBS)
	@echo "fgl shared library generated (lib$(FGL_LIB_NAME).so.$(FGL_VERSION)) in $(FGL_RELEASE_PATH)"
	cd $(FGL_RELEASE_PATH) && ln -fsv lib$(FGL_LIB_NAME).so.$(FGL_VERSION) lib$(FGL_LIB_NAME).so.$(FGL_API)
	cd $(FGL_RELEASE_PATH) && ln -fsv lib$(FGL_LIB_NAME).so.$(FGL_API) lib$(FGL_LIB_NAME).so

# Compile
fgl.o: core.c shapes.c sprites.c text.c fgl.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# Install generated and needed files to desired directories
DESTDIR ?= /usr/local
FGL_INSTALL_PATH ?= $(DESTDIR)/lib

FGL_H_INSTALL_PATH ?= $(DESTDIR)/include

clean:
	rm *.o *.so
	@echo "Removed .o and .so files."
endif