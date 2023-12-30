#pragma once

#include "node.h"

class File: public Node {
public:
    File(string path): Node(path) {
        if((sb.st_mode & S_IFMT) != S_IFREG) {
            throw "Error";
        }
    }

    void accept(Visitor * visitor) override {
        visitor->visitFile(this);
    }

    int numberOfFiles() const {
        return 1;
    }

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }
};