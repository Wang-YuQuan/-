#pragma once

#include "value.h"
#include "json_object.h"
#include "string_value.h"
#include "json_iterator.h"

class BeautifyVisitor : public JsonVisitor {
private:
    std::string _output = "{\n";
    int _deep = 0;
public:
    void visitJsonObject(JsonObject * obj) override {
        JsonIterator * it = obj->createIterator();
        JsonIterator * nextNode = obj->createIterator();
        int count;
        nextNode->next();
        _deep++;
        for(it->first(); !it->isDone(); it->next()) {
            count = _deep;
            while(count>0) {
                _output += "    ";
                count--;
            }
            JsonObject * jsObj = dynamic_cast<JsonObject *>(it->currentValue());
            if(jsObj)
                _output += "\"" + it->currentKey() + "\": {\n";
            else
                _output += "\"" + it->currentKey() + "\": ";
            it->currentValue()->accept(this);
            if(jsObj) {
                count = _deep;
                _output += "\n";
                while(count>0) {
                    _output += "    ";
                    count--;
                }
                _output += "}";
            }
            if(!nextNode->isDone()) {
                nextNode->next();
                _output += ",\n";
            }
        }
        _deep--;
        delete it;
        delete nextNode;
    }

    void visitStringValue(StringValue * val) override {
        _output += val->toString();
    }

    std::string getResult() const {
        return _output + "\n}";
    }
};