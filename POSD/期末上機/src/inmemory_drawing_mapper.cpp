#include "inmemory_drawing_mapper.h"
#include "painter_mapper.h"
#include "unit_of_work.h"

InMemoryDrawingMapper* InMemoryDrawingMapper::instance() {
    if (_instance == nullptr) {
        _instance = new InMemoryDrawingMapper();
    }
    return _instance;
}

void InMemoryDrawingMapper::add(DomainObject * drawing) {
    if (Drawing * d = dynamic_cast<Drawing *>(drawing)) {
        if (_store.count(d->id())) {
            delete _store.at(d->id());
            _store.erase(d->id());
        }
        _store[d->id()] = d;
    }
}

Drawing* InMemoryDrawingMapper::find(std::string id) {
    Drawing * d = _store.at(id);

    UnitOfWork::instance()->registerClean(d);

    return d;
}

void InMemoryDrawingMapper::update(std::string id) {
    if (_store.count(id)) {
        // no need to do anything, since they share the same instance.
    } else {
        throw std::string("object corresponding to ID is not in id map");
    }
}

void InMemoryDrawingMapper::del(std::string id) {
    if (_store.count(id)) {
        delete _store.at(id);
        _store.erase(id);
    } else {
        throw std::string("object corresponding to ID is not in id map");
    }
}

void InMemoryDrawingMapper::cleanCache() {
    // there is no cache
}

InMemoryDrawingMapper::InMemoryDrawingMapper() {}

InMemoryDrawingMapper* InMemoryDrawingMapper::_instance = nullptr;
