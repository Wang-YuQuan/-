#pragma once

#include <map>
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "unit_of_work.h"

class InMemoryDrawingMapper: public DrawingMapper {
public:
    static InMemoryDrawingMapper* instance();

    void add(DomainObject * drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    void cleanCache();

private:
    InMemoryDrawingMapper();
    static InMemoryDrawingMapper* _instance;

    std::map<std::string, Drawing*> _store;
};
