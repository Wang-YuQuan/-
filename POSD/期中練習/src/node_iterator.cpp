#include "node_iterator.h"
#include "folder.h"
#include <string>
#include <list>

NodeIterator::NodeIterator(Folder * composite): _host(composite) {
    first();
}

void NodeIterator::first() {
    _current = _host->_nodes.begin();
}

void NodeIterator::next() {
    if(isDone())
        throw std::string("Moving past the end!");
    _current++;
}

bool NodeIterator::isDone() const {
    return _current == _host->_nodes.end();
}

Node * NodeIterator::currentItem() const {
    return (*_current);
}