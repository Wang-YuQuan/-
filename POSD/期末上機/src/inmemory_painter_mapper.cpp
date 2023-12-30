#include <map>
#include "inmemory_painter_mapper.h"
#include "unit_of_work.h"

InMemoryPainterMapper* InMemoryPainterMapper::instance() {
    if (_instance == nullptr) {
        _instance = new InMemoryPainterMapper();
    }
    return _instance;
}

void InMemoryPainterMapper::add(DomainObject * painter) {
    if (Painter * d = dynamic_cast<Painter *>(painter)) {
        if (_store.count(d->id())) {
            delete _store.at(d->id());
            _store.erase(d->id());
        }
        _store[d->id()] = d;
    }
}

Painter* InMemoryPainterMapper::find(std::string id) {
    if (_store.count(id) == 0) {
        return nullptr;
    }
    Painter * p = _store.at(id);

    UnitOfWork::instance()->registerClean(p);

    return p;
}

void InMemoryPainterMapper::update(std::string id) {
    if (_store.count(id)) {
        // no need to do anything, since they share the same instance.
    } else {
        throw std::string("object corresponding to ID is not in id map");
    }
}

void InMemoryPainterMapper::del(std::string id) {
    if (_store.count(id)) {
        delete _store.at(id);
        _store.erase(id);
    } else {
        throw std::string("object corresponding to ID is not in id map");
    }
}

void InMemoryPainterMapper::cleanCache() {
    // there is no cache
}

InMemoryPainterMapper::InMemoryPainterMapper() {}

InMemoryPainterMapper* InMemoryPainterMapper::_instance = nullptr;
