#pragma once

#include "visitor.h"
#include "order_by.h"
#include "iterator.h"
#include <vector>
#include <string>

class TreeVisitor: public Visitor {
    private:
        string _output = ".\n";
        OrderBy _orderBy;
        int _printLevel = -1;
        std::vector<bool> _levelEnd;
        const std::string _branch = "├── ";
        const std::string _lastNode = "└── ";
        const std::string _line = "│   ";
        const std::string _space = "    ";
    public:
        TreeVisitor(OrderBy orderBy): _orderBy(orderBy) {}

        void visitFile(File * file) {
            _output += file->name() + "\n";
        }

        void visitFolder(Folder * folder) {
            _printLevel++;
            Iterator * currentIterator = folder->createIterator(_orderBy);
            Iterator * nextIterator = folder->createIterator(_orderBy);
            currentIterator->first();
            nextIterator->first();
            if(!currentIterator->isDone()) {
                nextIterator->next();
            }
            _levelEnd.push_back(false);
            if(_printLevel > 0) {
                _output += folder->name() + "\n";
            }
            while(!currentIterator->isDone()) {
                for(int i=0;i<_printLevel;i++) {
                    if(_levelEnd[i])
                        _output += _space;
                    else
                        _output += _line;
                }
                int currentLevel = _printLevel;
                if(nextIterator->isDone()) {
                    _output += _lastNode;
                    if(currentLevel >= 0)
                        _levelEnd[currentLevel] = true;
                }
                else {
                    _output += _branch;
                }
                currentIterator->currentItem()->accept(this);
                currentIterator->next();
                if(!nextIterator->isDone())
                    nextIterator->next();
            }
            _printLevel--;
            _levelEnd.pop_back();
        }

        string getTree() {
            return _output;
        }
};