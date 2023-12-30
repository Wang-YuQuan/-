#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name): _compareName(name) {

    }

    void visitFile(File * file) {
        if(file->name() == _compareName) {
            _paths.push_back(file->path());
        }
    }

    void visitFolder(Folder * folder) {
        auto it = folder->createIterator();
        for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
    }

    std::list<string> getPaths() const {
        return _paths;
    }
private:
    std::string _compareName;
    std::list<std::string> _paths;
};