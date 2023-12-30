#pragma once

#include <string>
#include <vector>
#include <dirent.h>
#include <algorithm>

using std::string;

class FileSystemScanner {
private:
    long unsigned int _index;
    struct stat sb;
    string _path;
    std::vector<string> _nodes;
public:
    bool isFile() {
        char completePath[256] = {'\0'};
        strcat(completePath, _path.c_str());
        strcat(completePath, "/");
        strcat(completePath, currentNodeName().c_str());
        stat(completePath, &sb);
        return (sb.st_mode & S_IFMT) == S_IFREG;
    }

    bool isFolder() {
        char completePath[256] = {'\0'};
        strcat(completePath, _path.c_str());
        strcat(completePath, "");
        strcat(completePath, currentNodeName().c_str());
        stat(completePath, &sb);
        return (sb.st_mode & S_IFMT) == S_IFDIR;
    }

    bool isDone() {
        return _index == _nodes.size() || _nodes.size() == 0;
    }

    static bool compare(string a, string b) {
        return strcmp(a.c_str(), b.c_str()) > 0;
    }

    void setPath(string path) {
        _path = path;
        _index = -1;
        _nodes.clear();
        DIR * dir;
        struct dirent *ent;
        if ((dir = opendir (path.c_str())) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
                if (strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name, "..")!=0) {
                    _nodes.push_back(ent->d_name);
                }
            }
            closedir(dir);
            std::sort(_nodes.begin(), _nodes.end(), compare);
        } 
        else {
            printf("error\n");
        }
    }

    string currentNodeName() {
        if(_index>=0)
            return _nodes[_index];
        else
            throw "error";
    }

    void nextNode() {
        if(!isDone())
            _index++;
    }
};
