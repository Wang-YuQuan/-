#include "inmemory_painter_mapper.h"

InMemoryPainterMapper * InMemoryPainterMapper::_instance = nullptr;

InMemoryPainterMapper * InMemoryPainterMapper::instance() {
    if(_instance==nullptr) {
        _instance = new InMemoryPainterMapper();
    }
    return _instance;
}

Painter * InMemoryPainterMapper::find(std::string id) {
    return static_cast<Painter *>(_domainObjects[painter->id()]);
}

// add
void InMemoryPainterMapper::add(DomainObject * painter) {
    _domainObjects[painter->id()] = painter;
}

// update
void InMemoryPainterMapper::update(std::string id) {
    Painter * painter = static_cast<Painter *>(_domainObjects[id]);
    painter->setName("...");
}

// delete
void InMemoryPainterMapper::del(std::string id) {
    _domainObjects.erase(id);
}

std::string InMemoryPainterMapper::updateStmt(DomainObject * domainObject) const {
    return "";
}

std::string InMemoryPainterMapper::findByIdStmt(std::string id) const {
    return "";
}

std::string InMemoryPainterMapper::addStmt(DomainObject * domainObject) const {
    return "";
}

std::string InMemoryPainterMapper::deleteByIdStmt(std::string id) const {
    return "";
}

InMemoryPainterMapper::InMemoryPainterMapper() {
}

int InMemoryPainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    return 0;
}

void InMemoryPainterMapper::cleanCache() {
    _domainObjects.clear();
}