#pragma once

#include <string>

#include <sqlite3.h>

#include "drawing.h"
#include "scanner.h"
#include "builder.h"
#include "parser.h"

class DrawingMapper {
public:
    static DrawingMapper* instance();

    virtual ~DrawingMapper() {
        delete _parser;
    }

    virtual void add(DomainObject * Drawing) = 0;

    virtual Drawing* find(std::string id) = 0;

    virtual void update(std::string id) = 0;

    virtual void del(std::string id) = 0;

    virtual void cleanCache() = 0;
protected:
    DrawingMapper() {
        _parser = new Parser(new Scanner(), new Builder());
    }

    Parser * _parser;
};