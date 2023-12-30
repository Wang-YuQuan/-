#pragma once

#include <list>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    class FolderIterator : public Iterator {
        public:
            FolderIterator(Folder* composite):_host(composite) {

            }

            ~FolderIterator() {

            }

            void first() {
                Iterator::first();
                _current = _host->_nodes.begin();
            }

            Node * currentItem() const {
                if(!isDone())
                    return *_current;
                return nullptr;
            }

            void next() {
                Iterator::next();
                if(!isDone())
                    _current++;
            }

            bool isDone() const {
                return _current == _host->_nodes.end();
            }
        private:
            Folder* const _host;
            std::list<Node *>::iterator _current;
    };

protected:
    void removeChild(Node * target) {
        _nodes.remove(target);
    }

public:
    Folder(string path): Node(path) {
        if((sb.st_mode & S_IFMT) != S_IFDIR) {
            throw "Error";
        }
    }

    void add(Node * node) {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        if(it)
            it->modify();
        _nodes.push_back(node);
        node->parent(this);
    }

    Node * getChildByName(const char * name) const {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }
        return nullptr;
    }

    int numberOfFiles() const {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    void accept(Visitor * visitor) {
        visitor->visitFolder(this);
    }

    Iterator * createIterator() {
        Iterator * iterator = new FolderIterator(this);
        if(it)
            delete it;
        it = iterator;
        return iterator;
    }

    Iterator * dfsIterator() {
        return new DfsIterator(this);
    }

    Node * find(string path) {
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

    void remove(string path) {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
            if(it)
                it->modify();
        }
    }
};