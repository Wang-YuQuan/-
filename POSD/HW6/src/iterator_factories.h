#pragma once

#include "iterator_factory.h"
#include "order_by.h"
#include "folder.h"

class FolderIteratorFactory: public IteratorFactory {
    private:
        static FolderIteratorFactory * _instance;
    public:
        Iterator * create(Folder * node, int operationCount) override {
            return new Folder::FolderIterator(node, operationCount);
        }
        static FolderIteratorFactory * instance() {
            if(_instance==nullptr) {
                _instance = new FolderIteratorFactory();
            }
            return _instance;
        }
        void destroyInstance() override {
            if(_instance!=nullptr) {
                delete _instance;
                _instance = nullptr;
            }
        }
};

class OrderByNameIteratorFactory: public IteratorFactory {
    private:
        static OrderByNameIteratorFactory * _instance;
    public:
        Iterator * create(Folder * node, int operationCount) override {
            return new Folder::OrderByNameIterator(node, operationCount);
        }
        static OrderByNameIteratorFactory * instance() {
            if(_instance==nullptr) {
                _instance = new OrderByNameIteratorFactory();
            }
            return _instance;
        }
        void destroyInstance() override {
            if(_instance!=nullptr) {
                delete _instance;
                _instance = nullptr;
            }
        }
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
    private:
        static OrderByNameWithFolderFirstIteratorFactory * _instance;
    public:
        Iterator * create(Folder * node, int operationCount) override {
            return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
        }
        static OrderByNameWithFolderFirstIteratorFactory * instance() {
            if(_instance==nullptr) {
                _instance = new OrderByNameWithFolderFirstIteratorFactory();
            }
            return _instance;
        }
        void destroyInstance() override {
            if(_instance!=nullptr) {
                delete _instance;
                _instance = nullptr;
            }
        }
};

class OrderByKindIteratorFactory: public IteratorFactory {
    private:
        static OrderByKindIteratorFactory * _instance;
    public:
        Iterator * create(Folder * node, int operationCount) override {
            return new Folder::OrderByKindIterator(node, operationCount);
        }
        static OrderByKindIteratorFactory * instance() {
            if(_instance==nullptr) {
                _instance = new OrderByKindIteratorFactory();
            }
            return _instance;
        }
        void destroyInstance() override {
            if(_instance!=nullptr) {
                delete _instance;
                _instance = nullptr;
            }
        }
};

FolderIteratorFactory * FolderIteratorFactory::_instance = nullptr;
OrderByNameIteratorFactory * OrderByNameIteratorFactory::_instance = nullptr;
OrderByNameWithFolderFirstIteratorFactory * OrderByNameWithFolderFirstIteratorFactory::_instance = nullptr;
OrderByKindIteratorFactory * OrderByKindIteratorFactory::_instance = nullptr;