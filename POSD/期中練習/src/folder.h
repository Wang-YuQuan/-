#pragma once

#include "node.h"
#include "iterator.h"
#include "node_iterator.h"
#include <string>
#include <list>

class Folder : public Node {
    friend class NodeIterator;
private:
    Folder * recordParent;
    std::list<Node *> _nodes;
    std::string _id, _name, _path;
public:
    Folder(std::string id, std::string name): _id(id), _name(name), _path("") {}

    std::string id() const {
        return _id;
    }

    std::string name() const {
        return _name;
    }
    
    std::string route() const override {
        return _path + "/" + name();
    }

    double size() const override{
        double totalSize = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            totalSize += (*it)->size();
        }
        return totalSize;
    }

    void updatePath(std::string path) override {
        _path = path + "/" + name();
        size_t found = _path.find_last_of("/");
        _path = _path.substr(0, found);
        for(auto it=_nodes.begin();it!=_nodes.end();it++) {
            Folder * folder = dynamic_cast<Folder *>(*it);
            if(folder) {
                (*it)->updatePath(route());
            }
        }
    }
    
    void addNode(Node* node) override {
        _nodes.push_back(node);
        node->parent(this);
        node->updatePath(route());
    }

    Node * checkNodeById(std::string id) const override {
        for(auto node : _nodes) {
            if(node->id()==id) {
                return node;
            }
            Folder * folder = dynamic_cast<Folder *>(node);
            if(folder) {
                Node * result = node->checkNodeById(id);
                if(result==nullptr) {
                    continue;
                }
                else {
                    return result;
                }
            }
        }
        return nullptr;
    }
    
    Node * getNodeById(std::string id) const override {
        Node * result = checkNodeById(id);
        if(result==nullptr) {
            throw std::string("Expected get node but node not found.");
        }
        return result;
    }

    void remove(Node * node) override {
        _nodes.remove(node);
    }
    
    void deleteNodeById(std::string id) override {
        Node * result = checkNodeById(id);
        if(result==nullptr) {
            throw std::string("Expected delete node but node not found.");
        }
        result->parent()->remove(result);
    }

    Iterator * createIterator() override {
        return new NodeIterator(this);
    }
};