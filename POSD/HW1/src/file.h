#pragma once

#include "node.h"
#include "null_iterator.h"

class File: public Node {
public:
    File(string path) {
        _path = path;
        size_t found = path.find_last_of("/");
        _name = path.substr(found+1);
    }

    string type() const override {
        return "file";
    }

    string name() const override {
        return _name;
    }
    
    string path() const override {
        return _path;
    }
    
    void add(Node * node) override {
        
    }

    void remove(string path) override {
        
    }
    
    Node * getChildByName(const char * name) const override {
        return nullptr;
    }

    Node * find(string path) override {
        return nullptr;
    }

    int numberOfFiles() const override {
        return 1;
    }

    Iterator * createIterator(string iteratorMode="") override {
        return new NullIterator();
    }
private:
    string _name, _path;
};