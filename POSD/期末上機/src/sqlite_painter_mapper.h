#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter_mapper.h"
#include "painter.h"
#include "sqlite_abstract_mapper.h"


class SQLitePainterMapper: public PainterMapper, public SQLiteAbstractMapper {
public:
    
    void add(DomainObject * Painter);

    Painter* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    void cleanCache();

    static SQLitePainterMapper* instance();

protected:
    SQLitePainterMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;
    
private:
    static SQLitePainterMapper* _instance;
};