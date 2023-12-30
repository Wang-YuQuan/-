#pragma once

#include <sqlite3.h>
#include <unordered_map>
#include <iostream>
#include "domain_object.h"
#include "unit_of_work.h"
#include <string>
#include "painter.h"
#include "sqlite_abstract_mapper.h"
#include "painter_mapper.h"

class SQLitePainterMapper : public SQLiteAbstractMapper, public PainterMapper {
public:
    void add(DomainObject * Painter) override;

    Painter * find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    void cleanCache() override;

    static PainterMapper * instance() override;
protected:
    SQLitePainterMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames) override;

    std::string addStmt(DomainObject * domainObject) const override;
    std::string findByIdStmt(std::string id) const override;
    std::string updateStmt(DomainObject * domainObject) const override;
    std::string deleteByIdStmt(std::string id) const override;
private:
    static SQLitePainterMapper * _instance;
};