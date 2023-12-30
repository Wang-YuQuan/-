#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>
#include "painter.h"
#include "sqlite_abstract_mapper.h"

class PainterMapper : public SQLiteAbstractMapper {
public:
    
    virtual void add(DomainObject * Painter) = 0;

    virtual Painter* find(std::string id) = 0;

    virtual void update(std::string id) = 0;

    virtual void del(std::string id) = 0;

    virtual void cleanCache() = 0;

    virtual static PainterMapper * instance() = 0;

protected:
    PainterMapper();

    virtual static int callback(void* notUsed, int argc, char** argv, char** colNames) = 0;

    virtual std::string addStmt(DomainObject * domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string updateStmt(DomainObject * domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;
    
private:
    static PainterMapper* _instance;
};