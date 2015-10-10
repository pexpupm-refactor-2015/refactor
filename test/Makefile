SRC_DIR=../src
INC_FILES=../include
JSON_DIR=../jsoncpp
JSON_INC_FILES=$(JSON_DIR)/include
JSON_SOURCES=$(shell ls $(JSON_DIR)/dist/*.cpp)
SOURCES=$(shell ls $(SRC_DIR)/*.cpp)
TEST_FILE=test_news.cpp
GTEST_FILE=gtest
GTEST_LIBS=gtest gtest_main pthread
GTEST_LINK_LIBS=$(addprefix -l,$(GTEST_LIBS))
CC=g++
CC_FLAGS=-ggdb -std=c++0x

all: gtest

$(GTEST_FILE): $(TEST_FILE) $(SOURCES)
	$(CC) $(CC_FLAGS) -I$(INC_FILES) -I$(JSON_INC_FILES) $(JSON_SOURCES) $(SOURCES) $(TEST_FILE) -o $@ $(GTEST_LINK_LIBS)

clean:
	@rm -f $(GTEST_FILE)
