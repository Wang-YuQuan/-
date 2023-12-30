#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>

class StreamOutVisitor : public Visitor {
public:
    StreamOutVisitor(): content("") {}
     
    void visitFile(File * file) override {
        std::ifstream ifs;
        char buffer[256] = {'\0'};
        ifs.open(file->path());
        if (!ifs.is_open()) {
            throw "error";
        }
        content += base_line + '\n' + file->path() + '\n' + slash_line + '\n';
        while (!ifs.eof()) {
            ifs.getline(buffer, sizeof(buffer));
            std::string str(buffer);
            content += str + "\n";
        }
        ifs.close();
        content += base_line + "\n\n";
    }

    void visitFolder(Folder * folder) override {
        passFolderTimes++;
        auto it = folder->createIterator();
        for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
    }

    std::string getResult() const {
        if(passFolderTimes >= 1)
            return content;
        return content.substr(0, content.length()-1);
    }
private:
    std::string content;
    int passFolderTimes = 0;
    const std::string base_line = "_____________________________________________";
    const std::string slash_line = "---------------------------------------------";
};