#pragma once

#include <string>
#include "iterator.h"
#include "null_iterator.h"

class Node{
private:
    std::string _id, _name, _path;
    int _size;
    Node * _parent;
public:
    Node * parent() {
        return _parent;
    }

    void parent(Node * parent) {
        _parent = parent;
    }

    virtual void remove(Node * node) {
        throw "error";
    }

    virtual Node * checkNodeById(std::string id) const {
        return nullptr;
    }

    virtual std::string id() const = 0;

    virtual std::string name() const = 0;
    
    virtual std::string route() const = 0;

    virtual double size() const = 0;

    virtual void updatePath(std::string path) = 0;
    
    virtual void addNode(Node* node) = 0;
    
    virtual Node * getNodeById(std::string id) const = 0;
    
    virtual void deleteNodeById(std::string id) = 0;

    virtual Iterator * createIterator() = 0;

    virtual ~Node() = default;
};
