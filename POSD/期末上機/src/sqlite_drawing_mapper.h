#pragma once

#include "drawing_mapper.h"
#include "sqlite_abstract_mapper.h"

class SQLiteDrawingMapper: public DrawingMapper, public SQLiteAbstractMapper {
public:
    static SQLiteDrawingMapper* instance();

    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    void cleanCache();

private:
    SQLiteDrawingMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::list<Shape *> convertShapes(char * shape_string);

    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

    static SQLiteDrawingMapper* _instance;
};