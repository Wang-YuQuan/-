#pragma once

class File;
class Folder;

class Visitor {
public:
    virtual void visitFile(File * file) {}
    virtual void visitFolder(Folder * folder) {}
};