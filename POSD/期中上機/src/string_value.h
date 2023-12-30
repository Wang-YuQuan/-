#pragma once

#include <string>

using namespace std;

class StringValue : public Value {
private:
    string _value;
public:
    StringValue(string value): _value(value) {}

    ~StringValue() {}

    string toString() override {
        return "\"" + _value + "\"";
    }

    void accept(JsonVisitor * visitor) override {
        visitor->visitStringValue(this);
    }
};