#include "painter_mapper.h"
#include "db_mode.h"
#include "sqlite_painter_mapper.h"
#include "inmemory_painter_mapper.h"

PainterMapper * PainterMapper::_instance = nullptr;

PainterMapper * PainterMapper::instance() {
    if(_instance==nullptr) {
        switch (DbMode::instance())
        {
            case DbMode::SQLite:
                _instance = SQLitePainterMapper::instance();
                break;
            default:
                _instance = InMemoryPainterMapper::instance();
                break;
        }
    }
    return _instance;
}