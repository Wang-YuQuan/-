#pragma once

#include "painter_mapper.h"
#include "domain_object.h"
#include <unordered_map>

class InMemoryPainterMapper : public PainterMapper {
public:
    void add(DomainObject * Painter) override;

    Painter * find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    void cleanCache() override;

    static InMemoryPainterMapper * instance();
protected:
    SQLitePainterMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames) override;

    std::string addStmt(DomainObject * domainObject) const override;
    std::string findByIdStmt(std::string id) const override;
    std::string updateStmt(DomainObject * domainObject) const override;
    std::string deleteByIdStmt(std::string id) const override;
private:
    static InMemoryPainterMapper * _instance;
    std::unordered_map<std::string, DomainObject *> _domainObjects;
};