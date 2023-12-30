#pragma once

#include <sqlite3.h>
#include <unordered_map>
#include <iostream>
#include "domain_object.h"
#include "unit_of_work.h"
#include "drawing.h"
#include <string>
#include "sqlite_abstract_mapper.h"

class SQLiteDrawingMapper: public SQLiteAbstractMapper, public DrawingMapper {
public:
    static SQLiteDrawingMapper * instance() override;

    void add(DomainObject * Drawing) override;

    Drawing* find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    void cleanCache() override;
protected:
    SQLiteDrawingMapper() override;

    static int callback(void* notUsed, int argc, char** argv, char** colNames) override;

    std::list<Shape *> convertShapes(char * shape_string) override;

    std::string addStmt(DomainObject * domainObject) const override;
    std::string findByIdStmt(std::string id) const override;
    std::string updateStmt(DomainObject * domainObject) const override;
    std::string deleteByIdStmt(std::string id) const override;
private:
    static SQLiteDrawingMapper * _instance;
};