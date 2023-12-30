#pragma once

#include <string>
#include <sqlite3.h>

#include "abstract_mapper.h"

class DomainObject;
class Drawing;
class Scanner;
class Parser;
class Builder;

class DrawingMapper : public AbstractMapper
{
public:
    ~DrawingMapper();

    Drawing * find(std::string id);

    void add(DomainObject * Drawing);

    void update(std::string id);

    void del(std::string id);

    std::string updateStmt(DomainObject *domainObject) const override;

    std::string findByIdStmt(std::string id) const override;

    std::string addStmt(DomainObject *domainObject) const override;

    std::string deleteByIdStmt(std::string id) const override;

    static DrawingMapper * instance();

    void destoryInstance();

protected:
    DrawingMapper();

    static int callback(void *notUsed, int argc, char **argv, char **colNames);

    std::list<Shape *> convertShapes(int argc, char **argv);

private:
    static DrawingMapper * _instance;
    Builder * _builder;
    Scanner * _scanner;
    Parser * _parser;
};