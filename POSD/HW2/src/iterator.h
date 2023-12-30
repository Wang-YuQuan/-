#pragma once 

#include<list>

class Node;
class Folder;

class Iterator {
public:
    Iterator() {isModified = false;}
    virtual ~Iterator() {}
    virtual void first() {
        if(isModified)
            throw "error";
    }
    virtual Node * currentItem() const {
        return nullptr;
    }
    virtual void next() {
        if(isModified)
            throw "error";
    }
    virtual bool isDone() const {
        return true;
    }
    virtual void modify() {
        isModified = true;
    }
protected:
    bool isModified;
};