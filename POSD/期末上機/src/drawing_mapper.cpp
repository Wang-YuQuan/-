#include <stdlib.h>

#include <string>
#include "drawing_mapper.h"
#include "sqlite_drawing_mapper.h"
#include "inmemory_drawing_mapper.h"
#include "db_mode.h"

DrawingMapper* DrawingMapper::instance() {
    switch (DbMode::instance()->getMode()) {
        case InMemory:
            return InMemoryDrawingMapper::instance();
        case SQLite:
        default:
            return SQLiteDrawingMapper::instance();
    }
}