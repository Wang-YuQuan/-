#pragma once

#include "iterator.h"

class Folder;

class IteratorFactory {
public:
    virtual Iterator * create(Folder * node, int operationCount) = 0;
    virtual void destroyInstance() = 0;
    virtual ~IteratorFactory() {}
};