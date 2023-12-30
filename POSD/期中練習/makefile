.PHONY: directories clean stat

all: directories bin/ut_all

bin/ut_all: src/node.h src/app.h src/folder.h src/iterator.h src/node_iterator.h src/null_iterator.h src/utility.h obj/node_iterator.o
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_main.cpp obj/node_iterator.o -o bin/ut_all -lgtest -lpthread

obj/node_iterator.o: src/node_iterator.h src/node_iterator.cpp
	g++ -std=c++11 -c src/node_iterator.cpp -o obj/node_iterator.o

directories:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc src/* test/*