#pragma once

#include "iterator.h"
#include <string>

class NullIterator : public Iterator {
public:
    void first() override {
        throw std::string("No child member!");
    }
    
    void next() override {
        throw std::string("No child member!");
    }
    
    bool isDone() const override {
        return true;
    }
    
    Node * currentItem() const override {
        throw std::string("No child member!");
    }
};