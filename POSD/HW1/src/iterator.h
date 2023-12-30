#pragma once 

#include <vector>

class Node;
class Folder;

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void first() = 0;
    virtual Node * currentItem() const = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* folder);
    void first() override;
    Node * currentItem() const override;
    void next() override;
    bool isDone() const override;
private:
    Folder * _folder;
    std::vector<Node *>::iterator _it;
};