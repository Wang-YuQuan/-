#include <stdlib.h>

#include "painter_mapper.h"
#include "sqlite_painter_mapper.h"
#include "inmemory_painter_mapper.h"
#include "db_mode.h"

PainterMapper* PainterMapper::instance() {
    switch (DbMode::instance()->getMode()) {
        case InMemory:
            return InMemoryPainterMapper::instance();
        case SQLite:
        default:
            return SQLitePainterMapper::instance();
    }
}