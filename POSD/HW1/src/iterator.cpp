#include <vector>
#include "node.h"
#include "folder.h"
#include "iterator.h"

FolderIterator::FolderIterator(Folder* folder): _folder(folder) {
    first();
}

void FolderIterator::first() {
    _it = _folder->_folders.begin();
}

Node * FolderIterator::currentItem() const {
    if(!isDone())
        return *_it;
    return nullptr;
}

void FolderIterator::next() {
    if(!isDone())
        _it++;
}

bool FolderIterator::isDone() const {
    return _folder->_folders.end() == _it;
}