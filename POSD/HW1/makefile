.PHONY: directories clean stat

all: directories bin/ut_all

bin/ut_all: test/ut_all.cpp test/ut_folder.h src/node.h src/folder.h src/file.h src/iterator.h src/dfs_iterator.h src/null_iterator.h iterator.o
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_all.cpp obj/iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o: src/iterator.h src/iterator.cpp
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

directories:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc src/* test/*