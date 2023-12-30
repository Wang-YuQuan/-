#pragma once

#include <string>
#include <stack>
#include "node.h"
#include "folder.h"
#include "file.h"

using std::string;

class FileSystemBuilder {
private:
    std::stack<Folder *> _nodes;
    Folder * _root;
public:
    FileSystemBuilder() {
        while(!_nodes.empty())
            _nodes.pop();
        _root = nullptr;
    }

    Folder * getRoot() const {
        return _root;
    }

    void buildFile(string path) {
        File * file = new File(path);
        _nodes.top()->add(file);
    }

    void buildFolder(string path) {
        Folder * folder = new Folder(path);
        if(_nodes.empty()) {
            _root = folder;
            _nodes.push(_root);
            return;
        }
        _nodes.push(folder);
    }

    void endFolder() {
        if(_nodes.size() > 1) {
            Folder * folder = _nodes.top();
            _nodes.pop();
            _nodes.top()->add(folder);
            return;
        }
        _nodes.pop();
    }
};
