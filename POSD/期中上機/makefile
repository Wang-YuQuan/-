.PHONY: clean dirs

UT_ALL = test/ut_all.cpp
TEST_HEADERS = test/json_test.h test/json_iterator_test.h test/json_visitor_test.h test/json_builder_test.h test/json_parser_test.h test/json_scanner_test.h

SRC_HEADERS = src/json_object.h src/value.h src/string_value.h src/json_iterator.h src/visitor.h src/beautify_visitor.h src/json_parser.h src/json_scanner.h src/json_builder.h

all: dirs bin/ut_all

bin/ut_all: $(UT_ALL) $(TEST_HEADERS) $(SRC_HEADERS)
	g++ -std=c++11 -g -Wfatal-errors -Wall -o bin/ut_all $(UT_ALL) -lgtest -lpthread

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj
