#pragma once

#include "node.h"
#include <string>

class Link : public Node {
private:
    Node * _proxyNode;
public:
    Link(std::string path, Node * proxyNode): Node(path) {
        _proxyNode = proxyNode;
    }

    int numberOfFiles() const override {
        return _proxyNode->numberOfFiles();
    }

    Node * find(string path) override {
        return _proxyNode->find(path);
    }

    std::list<string> findByName(string name) override {
        return _proxyNode->findByName(name);
    }

    void add(Node * node) override {
        _proxyNode->add(node);
    }

    void remove(string path) override {
        _proxyNode->remove(path);
    }

    Node * getChildByName(const char * name) const override {
        return _proxyNode->getChildByName(name);
    }

    Node * getTarget() {
        return _proxyNode;
    }

    void updateChildPath(std::string path) override {
        
    }

    void accept(Visitor * visitor) {
        visitor->visitLink(this);
    }
};