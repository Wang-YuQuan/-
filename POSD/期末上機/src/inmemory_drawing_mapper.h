#pragma once

#include "drawing_mapper.h"
#include "domain_object.h"
#include <unordered_map>

class InMemoryDrawingMapper : public DrawingMapper {
public:
    static InMemoryDrawingMapper * instance();

    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);
protected:
    InMemoryDrawingMapper() override;

    static int callback(void* notUsed, int argc, char** argv, char** colNames) override;

    std::list<Shape *> convertShapes(char * shape_string) override;

    std::string addStmt(DomainObject * domainObject) const override;
    std::string findByIdStmt(std::string id) const override;
    std::string updateStmt(DomainObject * domainObject) const override;
    std::string deleteByIdStmt(std::string id) const override;
private:
    static InMemoryDrawingMapper * _instance;
    std::unordered_map<std::string, DomainObject *> _domainObjects;
};