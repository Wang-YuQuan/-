#pragma once 

#include <list>
#include <sys/stat.h>
#include "node.h"
#include "order_by.h"
#include "iterator.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    int _operationCount = 0;

protected:
    void removeChild(Node * target) override {
        _nodes.remove(target);
        _operationCount++;
    }

public:
    Folder(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    void add(Node * node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node * getChildByName(const char * name) const override {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator(OrderBy order = OrderBy::Normal) override {
        switch(order) {
            case OrderBy::Normal:
                return new FolderIterator(this, _operationCount);
                break;
            case OrderBy::Name:
                return new OrderByNameIterator(this, _operationCount);
                break;
            case OrderBy::NameWithFolderFirst:
                return new OrderByNameWithFolderFirstIterator(this, _operationCount);
                break;
            case OrderBy::Kind:
                return new OrderByKindIterator(this, _operationCount);
                break;
            default:
                return nullptr;
                break;
        }
    }

    Node * find(string path) override {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }

    void remove(string path) override {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~FolderIterator() {}

        void first() {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }
    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameIterator: public Iterator {
        private:
            Folder* const _host;
            std::list<Node *>::iterator _current;
            std::list<Node *> _copyContainer;
            int _operationCount;

            void checkAvailable() const {
                if(_host->_operationCount != _operationCount) {
                    throw "Iterator Not Avaliable";
                }
            }

            static bool compare(Node * first, Node * second) {
                return strcmp(first->name().c_str(), second->name().c_str()) < 0;
            }
        public:
            OrderByNameIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

            ~OrderByNameIterator() {}

            void first() {
                checkAvailable();
                _copyContainer = _host->_nodes;
                _copyContainer.sort(compare);
                _current = _copyContainer.begin();
            }

            Node * currentItem() const {
                return *_current;
            }

            void next() {
                checkAvailable();
                _current++;
            }

            bool isDone() const {
                return _current == _copyContainer.end();
            }
    };

    class OrderByNameWithFolderFirstIterator: public Iterator {
        private:
            Folder* const _host;
            std::list<Node *>::iterator _current;
            std::list<Node *> _copyContainer;
            std::list<Node *> _copyFolder;
            std::list<Node *> _copyFile;
            int _operationCount;

            void checkAvailable() const {
                if(_host->_operationCount != _operationCount) {
                    throw "Iterator Not Avaliable";
                }
            }

            static bool compare(Node * first, Node * second) {
                return strcmp(first->name().c_str(), second->name().c_str()) < 0;
            }

            void classifyNode() {
                for(auto it=_host->_nodes.begin();it!=_host->_nodes.end();it++) {
                    Folder * folder = dynamic_cast<Folder *>(*it);
                    if(folder)
                        _copyFolder.push_back(*it);
                    else
                        _copyFile.push_back(*it);
                }
            }

            void combineNode() {
                for(auto it=_copyFolder.begin();it!=_copyFolder.end();it++) {
                    _copyContainer.push_back(*it);
                }
                for(auto it=_copyFile.begin();it!=_copyFile.end();it++) {
                    _copyContainer.push_back(*it);
                }
            }
        public:
            OrderByNameWithFolderFirstIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

            ~OrderByNameWithFolderFirstIterator() {}

            void first() {
                checkAvailable();
                classifyNode();
                _copyFolder.sort(compare);
                _copyFile.sort(compare);
                combineNode();
                _current = _copyContainer.begin();
            }

            Node * currentItem() const {
                return *_current;
            }

            void next() {
                checkAvailable();
                _current++;
            }

            bool isDone() const {
                return _current == _copyContainer.end();
            }
    };

    class OrderByKindIterator: public Iterator {
        private:
            Folder* const _host;
            std::list<Node *>::iterator _current;
            std::list<Node *> _copyContainer;
            std::list<Node *> _copyNoExtensionName;
            std::list<Node *> _copyFolder;
            std::list<Node *> _copyFile;
            int _operationCount;

            void checkAvailable() const {
                if(_host->_operationCount != _operationCount) {
                    throw "Iterator Not Avaliable";
                }
            }

            static bool compare(Node * first, Node * second) {
                size_t found1 = first->name().find_last_of(".");
                size_t found2 = second->name().find_last_of(".");
                string _name1 = first->name().substr(found1+1);
                string _name2 = second->name().substr(found2+1);
                if(_name1 == _name2)
                    return strcmp(first->name().c_str(), second->name().c_str()) < 0;
                return strcmp(_name1.c_str(), _name2.c_str()) < 0;
            }

            void classifyNode() {
                for(auto it=_host->_nodes.begin();it!=_host->_nodes.end();it++) {
                    Folder * folder = dynamic_cast<Folder *>(*it);
                    if(folder)
                        _copyFolder.push_back(*it);
                    else {
                        size_t find = (*it)->name().rfind('.');
                        if(find == std::string::npos) {
                            _copyNoExtensionName.push_back(*it);
                            continue;
                        }
                        else {
                            _copyFile.push_back(*it);
                        }
                    }
                }
            }

            void combineNode() {
                for(auto it=_copyNoExtensionName.begin();it!=_copyNoExtensionName.end();it++) {
                    _copyContainer.push_back(*it);
                }
                for(auto it=_copyFolder.begin();it!=_copyFolder.end();it++) {
                    _copyContainer.push_back(*it);
                }
                for(auto it=_copyFile.begin();it!=_copyFile.end();it++) {
                    _copyContainer.push_back(*it);
                }
            }
        public:
            OrderByKindIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

            ~OrderByKindIterator() {}

            void first() {
                checkAvailable();
                classifyNode();
                _copyNoExtensionName.sort(compare);
                _copyFolder.sort(compare);
                _copyFile.sort(compare);
                combineNode();
                _current = _copyContainer.begin();
            }

            Node * currentItem() const {
                return *_current;
            }

            void next() {
                checkAvailable();
                _current++;
            }

            bool isDone() const {
                return _current == _copyContainer.end();
            }
    };
};
