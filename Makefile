
# Test config section
CC = g++

CPPFLAGS = \
	-std=c++17 \
	-g \
	-Iinclude \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \

LDFLAGS = \
	-lpthread \
	-lgtest \

TEST_SRC = \
	test/main.cpp \
	test/LockGuardTest.cpp \
	test/DummyMutexTest.cpp \
	test/CachedCallableTest.cpp \
	test/RandomNumberGeneratorTest.cpp \
	test/MathTest.cpp \
	test/ResultTest.cpp \

TEST_BIN = test/test_bin.out

# Documentation config section
CLEAN_DOC = rm -rf doc/html
MAKE_DOC  = doxygen doc/doxygen_cfg

# Targets
.PHONY: test doc all

test:
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(TEST_SRC) -o $(TEST_BIN)
	$(TEST_BIN)

doc:
	$(CLEAN_DOC)
	$(MAKE_DOC)

