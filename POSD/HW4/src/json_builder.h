#pragma once

#include "value.h"
#include "json_object.h"
#include "string_value.h"
#include <stack>

class JsonBuilder {
private:
    std::stack<JsonObject *> _nodes;
    std::stack<string> _keys;
    JsonObject * _root;
public:
    JsonBuilder() {
        while(!_nodes.empty())
            _nodes.pop();
        _root = nullptr;
    }

    void buildValue(std::string key, std::string value) {
        StringValue * _value = new StringValue(value);
        _nodes.top()->set(key, _value);
    }

    void buildObject(std::string key) {
        JsonObject * object = new JsonObject();
        _nodes.push(object);
        _keys.push(key);
    }

    void endObject() {
        if(_nodes.size() > 1) {
            Value * value = _nodes.top();
            _nodes.pop();
            _nodes.top()->set(_keys.top(), value);
            _keys.pop();
        }
    }

    JsonObject * getJsonObject() {
        _root = _nodes.top();
        while(!_nodes.empty())
            _nodes.pop();
        while(!_keys.empty())
            _keys.pop();
        return _root;
    }
};
