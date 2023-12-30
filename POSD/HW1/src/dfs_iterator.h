#pragma once 

#include <vector>
#include <queue>
#include "iterator.h"
#include "node.h"
#include "folder.h"

#include <iostream>

class DfsIterator: public Iterator {
public:
    ~DfsIterator() {
        clear();
    }

    DfsIterator(Node* composite) : _node(composite){
        _it.push_back(_node->createIterator());
    }

    void first() override {
        clear();
        _it.push_back(_node->createIterator());
        _it[0]->first();
    }

    Node * currentItem() const override {
        if (_it.empty())
            return nullptr;
        return _it[_it.size()-1]->currentItem();
    }

    void next() override {
        if (_it.empty())
            return;
        Iterator * lastIterator = _it[_it.size()-1];
        _it.push_back(lastIterator->currentItem()->createIterator());
        lastIterator =_it[_it.size()-1];
        while (lastIterator->isDone()) {
            delete lastIterator;
            _it.pop_back();
            if (_it.empty())
                return;
            lastIterator = _it[_it.size()-1];
            lastIterator->next();
        }
    }
    
    bool isDone() const override {
        return _it.empty();
    }
private:
    Node* _node;
    vector<Iterator *> _it;

    void clear() {
        for (Iterator* it : _it){
            delete it;
        }
        _it.clear();
    }
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite) {
        _node = composite;
        _it.push(_node->createIterator());
    }

    void first() override {
        clear();
        _it.push(_node->createIterator());
        _it.front()->first();
    }

    Node * currentItem() const override {
        if (_it.empty())
            return nullptr;
        return _it.front()->currentItem();
    }

    void next() override {
        if (_it.empty())
            return;
        Iterator * firstIterator = _it.front();
        if(firstIterator->isDone()) {
            delete firstIterator;
            _it.pop();
            if(_it.empty()) {
                return;
            }
        }
        firstIterator = _it.front();
        if(firstIterator->currentItem()->type() == "folder") {
            _it.push(firstIterator->currentItem()->createIterator());
        }
        firstIterator->next();
        if(firstIterator->isDone()) {
            delete firstIterator;
            _it.pop();
            if(_it.empty()) {
                return;
            }
            firstIterator = _it.front();
        }
    }

    bool isDone() const override {
        return _it.empty();
    }
private:
    Node* _node;
    queue<Iterator *> _it;

    void clear() {
        while(!_it.empty()) {
            delete _it.front();
            _it.pop();
        }
    }
};