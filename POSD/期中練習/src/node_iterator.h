#pragma once

#include "iterator.h"
#include <string>
#include <list>

class NodeIterator : public Iterator {
private:
    Folder * _host;
    std::list<Node *>::iterator _current;
public:
    NodeIterator(Folder * composite);

    void first() override;
    
    void next() override;
    
    bool isDone() const override;
    
    Node * currentItem() const override;
};