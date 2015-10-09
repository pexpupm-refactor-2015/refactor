JSON_SRC_DIR=../jsoncpp
INC_FILES=../jsoncpp/include
TEST_FILE=test_jsoncpp.cpp
TEST_BIN=test_jsoncpp
TEST_TUITS_FILE=test_tuits_jsoncpp.cpp
TEST_TUITS_BIN=test_tuits_jsoncpp
TEST_DUMP_FILE=test_dump_json.cpp
TEST_DUMP_BIN=test_dump

GTEST_LINK_LIBS=$(addprefix -l,$(GTEST_LIBS))
CC=g++
CC_FLAGS=-ggdb
JSON_SOURCES=$(shell ls $(JSON_SRC_DIR)/dist/jsoncpp.cpp)

all: $(TEST_BIN) $(TEST_TUITS_BIN) $(TEST_DUMP_BIN)

$(TEST_BIN): $(TEST_FILE) $(JSON_SOURCES)
	$(CC) $(CC_FLAGS) -I$(INC_FILES) $(JSON_SOURCES) $(TEST_FILE) -o $@

$(TEST_TUITS_BIN): $(TEST_TUITS_FILE) $(JSON_SOURCES)
	$(CC) $(CC_FLAGS) -I$(INC_FILES) $(JSON_SOURCES) $(TEST_TUITS_FILE) -o $@

$(TEST_DUMP_BIN): $(TEST_DUMP_FILE) $(JSON_SOURCES)
	$(CC) $(CC_FLAGS) -I$(INC_FILES) $(JSON_SOURCES) $(TEST_DUMP_FILE) -o $@

clean:
	@rm -f $(TEST_BIN) $(TEST_TUITS_BIN) $(TEST_DUMP_BIN) *~
