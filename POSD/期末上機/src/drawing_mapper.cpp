#include "drawing_mapper.h"
#include "db_mode.h"
#include "sqlite_drawing_mapper.h"
#include "inmemory_drawing_mapper.h"

DrawingMapper * DrawingMapper::_instance = nullptr;

DrawingMapper * DrawingMapper::instance() {
    if(_instance==nullptr) {
        switch (DbMode::instance())
        {
            case DbMode::SQLite:
                _instance = SQLiteDrawingMapper::instance();
                break;
            default:
                _instance = InMemoryDrawingMapper::instance();
                break;
        }
    }
    return _instance;
}