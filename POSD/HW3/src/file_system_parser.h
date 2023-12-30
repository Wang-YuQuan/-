#pragma once

#include <string>
#include "folder.h"
#include <stack>
#include "file_system_scanner.h"
#include "file_system_builder.h"

using std::string;

class FileSystemParser {
private:
    string _path;
    stack<FileSystemScanner *> _scanners;
    FileSystemBuilder * _builder;
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder) {}

    Folder * getRoot() const {
        return _builder->getRoot();
    }

    void parse() {
        if(getRoot() == nullptr) {
            _builder->buildFolder(_path);
        }
        FileSystemScanner * scanner = new FileSystemScanner();
        scanner->setPath(_path);
        _scanners.push(scanner);
        while(!_scanners.top()->isDone() && !_scanners.empty()) {
            _scanners.top()->nextNode();
            if(_scanners.top()->isDone())
                break;
            if(_scanners.top()->isFile()) {
                _builder->buildFile(_path + "/" + _scanners.top()->currentNodeName());
            }
            else {
                _path += "/" + _scanners.top()->currentNodeName();
                _builder->buildFolder(_path);
                parse();
                size_t found = _path.find_last_of("/");
                _path = _path.substr(0, found);
                _builder->endFolder();
            }
        }
        _scanners.pop();
        if(_scanners.empty()) {
            _builder->endFolder();
        }
    }

    void setPath(string path) {
        _path = path;
    }
};
