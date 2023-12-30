#pragma once

#include <string>
using namespace std;

class Iterator;

class Node {
public:
    virtual ~Node() = default;

    virtual string type() const = 0;

    virtual string name() const = 0;
    
    virtual string path() const = 0;
    
    virtual void add(Node * node) = 0;

    virtual void remove(string path) = 0;
    
    virtual Node * getChildByName(const char * name) const = 0;

    virtual Node * find(string path) = 0;

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator(string iteratorMode="") = 0;
};