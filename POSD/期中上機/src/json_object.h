#pragma once

#include "value.h"
#include "string_value.h"
#include "json_iterator.h"
#include <list>
#include <map>

using namespace std;

class JsonObject : public Value {
private:
    string output;
    std::map<string,Value *> _nodes;
    class JsonObjectIterator : public JsonIterator {
        public:
            JsonObjectIterator(JsonObject * composite): _host(composite) {
                first();
            }

            void first() {
                _current = _host->_nodes.begin();
            }

            std::string currentKey() const override {
                return (*_current).first;
            }

            Value * currentValue() const override {
                return (*_current).second;
            }

            void next() override {
                if(!isDone())
                    _current++;
            }

            bool isDone() const override {
                return _current == _host->_nodes.end();
            }
        private:
            JsonObject * _host;
            std::map<string, Value *>::iterator _current;
    };
public:
    JsonObject() {}

    ~JsonObject() {
        for(auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            delete it->second;
        }
        _nodes.clear();
    }

    void set(string key, Value * string_value) {
        _nodes[key] = string_value;
    }

    Value * getValue(string key) {
        if(_nodes.count(key)==0)
            throw "error";
        return _nodes[key];
    }

    string toString() override {
        output = "";
        std::map<string,Value *>::iterator _nextNode = _nodes.begin();
        _nextNode++;
        for(auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            output += "\"" + it->first + "\":";
            output += it->second->toString();
            if(_nextNode != _nodes.end()) {
                _nextNode++;
                output += ",\n";
            }
        }
        return "{\n" + output + "\n}";
    }

    JsonIterator * createIterator() override {
        return new JsonObjectIterator(this);
    }

    void accept(JsonVisitor * visitor) override {
        visitor->visitJsonObject(this);
    }
};