#pragma once

#include "iterator.h"

class NullIterator : public Iterator {
    ~NullIterator() = default;
    void first() override {}
    Node * currentItem() const override {return nullptr;}
    void next() override {}
    bool isDone() const override {return true;}
};