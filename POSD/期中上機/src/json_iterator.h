#pragma once

class Value;

class JsonIterator {
public:
    virtual void first() {
        throw "error";
    }

    virtual std::string currentKey() const {
        throw "error";
    }

    virtual Value * currentValue() const {
        throw "error";
    }

    virtual void next() {
        throw "error";
    }

    virtual bool isDone() const {
        return true;
    }

    virtual ~JsonIterator() {}
};

class NullIterator : public JsonIterator {
    
};