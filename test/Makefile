SRC_DIR=../src
INC_FILES=../include
SOURCES=$(shell ls $(SRC_DIR)/*.cpp)
TEST_FILE=test_noticias.cpp
GTEST_FILE=gtest
GTEST_LIBS=gtest gtest_main pthread
GTEST_LINK_LIBS=$(addprefix -l,$(GTEST_LIBS))
CC=g++
CC_FLAGS=-ggdb

all: gtest

$(GTEST_FILE): $(TEST_FILE) $(SOURCES)
	$(CC) $(CC_FLAGS) -I$(INC_FILES) $(SOURCES) $(TEST_FILE) -o $@ $(GTEST_LINK_LIBS)

clean:
	-rm $(GTEST_FILE)
