#pragma once

#include <string>
#include <vector>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"
#include <cstring>
#include <cstddef>

using namespace std;

class Folder: public Node {
    friend class FolderIterator;
public:
    Folder(string path){
        _path = path;
        size_t found = path.find_last_of("/");
        _name = path.substr(found+1);
    }

    ~Folder() {
        // for(auto node : _folders) {
        //     Folder * folder = dynamic_cast<Folder *>(node);
        //     if(folder) {
        //         delete node;
        //     }
        // }
    }

    string type() const override {
        return "folder";
    }

    string name() const override {
        return _name;
    }

    string path() const override {
        return _path;
    }
    
    void add(Node * node) override {
        size_t found = node->path().find_last_of("/");
        string node_path = node->path().substr(0, found);
        Node * child = find(node->path());
        if(_path==node_path){
            if(!child) {
                _folders.push_back(node);
            }
            else {
                throw "Already a same name file in this folder.";
            }
        }
        else {
            throw "Already a same name file in this folder.";
        }
    }

    void remove(string path) override {
        for(size_t i=0;i<_folders.size();i++) {
            Folder * folder = dynamic_cast<Folder *>(_folders[i]);
            if(strcmp(_folders[i]->path().c_str(), path.c_str())==0) {
                // delete _folders[i];
                _folders.erase(_folders.begin() + i);
                return;
            }
            if(folder) {
                _folders[i]->remove(path);
            }
        }
    }
    
    Node * getChildByName(const char * name) const override {
        for(auto node : _folders) {
            Folder * folder = dynamic_cast<Folder *>(node);
            if(strcmp(node->name().c_str(), name)==0) {
                return node;
            }
            if(folder) {
                Node * result = node->getChildByName(name);
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

    Node * find(string path) override {
        for(auto node : _folders) {
            Folder * folder = dynamic_cast<Folder *>(node);
            if(node->path()==path) {
                return node;
            }
            if(folder) {
                Node * result = node->find(path);
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

    int numberOfFiles() const override {
        int total = 0;
        for(Node * node : _folders) {
            total += node->numberOfFiles();
        }
        return total;
    }

    Iterator * createIterator(string iteratorMode="") override {
        if(iteratorMode == "") {
            return new FolderIterator(this);
        }
        else if (iteratorMode == "DFS"){
            return new DfsIterator(this);
        }
        else if (iteratorMode == "BFS"){
            return new BfsIterator(this);
        }
        else {
            return nullptr;
        }
    }
private:
    std::vector<Node *> _folders;
    string _name, _path;
};