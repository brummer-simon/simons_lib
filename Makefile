CC = g++

CPPFLAGS = \
	-std=c++17 \
	-g \
	-Iinclude \

LDFLAGS = \
	-lpthread \
	-lgtest \

TEST_SRC = \
	tests/main.cpp \
	tests/CachedCallableTest.cpp \

TEST_BIN = tests/test_bin.out

test:
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(TEST_SRC) -o $(TEST_BIN)
	$(TEST_BIN)
