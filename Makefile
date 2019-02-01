# Generic c++ project make template.
# Author: Simon Brummer <simon.brummer@posteo.de>

# --- Global Project settings ---
PROJECT_NAME     := simons_lib
PROJECT_TYPE     := headeronly
PROJECT_CONFIG   := debug
VERSION_MAJOR    := 0
VERSION_MINOR    := 2
VERSION_REVISION := 0

include etc/make/header.mk

# ---Install locations ---
INSTALL_INC_DIR := /usr/local/include

# --- Sources files ---
GTEST_SRC := \
	VersionTest.cpp \
	CachedCallableTest.cpp \
	LockGuardTest.cpp \
	MathTest.cpp \
	NullTypesTest.cpp \
	RandomNumberGeneratorTest.cpp \
	ResultTest.cpp \
	StackTest.cpp \
	main.cpp

# --- Compiler settings ---
CC := g++

STD := -std=c++17

INCLUDES := \
	-I$(INC_DIR)

DEFINES := \
	$(VERSION_DEFINES)

WARNINGS := \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wtype-limits \
	-Wstrict-overflow=5 \
	-fstrict-overflow \
	-Wsign-compare \
	-Wconversion

CPPFLAGS := \

CPPFLAGS_GTEST := \
	-Og \
	-ggdb

# --- Linker settings ---
LDFLAGS := \

LDFLAGS_GTEST := \

# --- Library settings ---
LIBS_GTEST := \
	-lgtest \
	-lpthread

# --- Execution Arguments ---
TEST_ARGS := \

# Include actual make targets
include etc/make/targets.mk
