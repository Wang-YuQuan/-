#pragma once

#include <map>
#include "painter_mapper.h"

class InMemoryPainterMapper: public PainterMapper {
public:
    static InMemoryPainterMapper* instance();

    void add(DomainObject * drawing);

    Painter* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    void cleanCache();

private:
    InMemoryPainterMapper();
    static InMemoryPainterMapper* _instance;

    std::map<std::string, Painter*> _store;
};
