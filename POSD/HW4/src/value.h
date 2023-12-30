#pragma once

#include <string>
#include "visitor.h"
#include "json_iterator.h"

using std::string;

class Value {
public:
    Value() {};

    virtual ~Value() {};

    virtual string toString() = 0;

    virtual JsonIterator * createIterator() {
        return new NullIterator();
    }

    virtual void accept(JsonVisitor * visitor) = 0;
};