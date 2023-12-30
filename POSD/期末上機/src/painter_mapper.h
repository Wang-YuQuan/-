#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "sqlite_abstract_mapper.h"

class PainterMapper {
public:
    static PainterMapper* instance();
    
    virtual void add(DomainObject * Painter) = 0;

    virtual Painter* find(std::string id) = 0;

    virtual void update(std::string id) = 0;

    virtual void del(std::string id) = 0;

    virtual void cleanCache() = 0;

protected:
    PainterMapper() {}
};