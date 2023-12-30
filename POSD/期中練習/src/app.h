#pragma once

#include "node.h"
#include <string>

class App : public Node {
public:
    App(std::string id, std::string name, double size): _id(id), _name(name), _path(""), _size(size) {}

    std::string id() const {
        return _id;
    }

    std::string name() const {
        return _name;
    }
    
    std::string route() const override {
        return _path + "/" + name();
    }

    double size() const override {
        return _size;
    }

    void updatePath(std::string path) override {
        _path = path;
    }
    
    void addNode(Node* node) override {
        throw std::string("only folder can add node.");
    }
    
    Node * getNodeById(std::string id) const override {
        throw std::string("only folder can get node.");
    }
    
    void deleteNodeById(std::string id) override {
        throw std::string("only folder can delete node.");
    }

    Iterator * createIterator() override {
        return new NullIterator();
    }
private:
    std::string _id, _name, _path;
    double _size;
};