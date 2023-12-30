#include "inmemory_drawing_mapper.h"
#include "inmemory_painter_mapper.h"
#include "painter.h"

InMemoryDrawingMapper * InMemoryDrawingMapper::_instance = nullptr;

InMemoryDrawingMapper * InMemoryDrawingMapper::instance() {
    if(_instance==nullptr) {
        _instance = new InMemoryDrawingMapper();
    }
    return _instance;
}

Drawing* InMemoryDrawingMapper::find(std::string id) {
    return static_cast<Drawing *>(_domainObjects[id]);
}

// add
void InMemoryDrawingMapper::add(DomainObject * drawing) {
    _domainObjects[id] = drawing;
}

// update
void InMemoryDrawingMapper::update(std::string id) {
    // ?
}

// delete
void InMemoryDrawingMapper::del(std::string id) {
    _domainObjects.erase[id];
}

std::string InMemoryDrawingMapper::updateStmt(DomainObject * domainObject) const {
    return "";
}

std::string InMemoryDrawingMapper::findByIdStmt(std::string id) const {
    return "";
}

std::string InMemoryDrawingMapper::addStmt(DomainObject * domainObject) const {
    return "";
}

std::string InMemoryDrawingMapper::deleteByIdStmt(std::string id) const {
    return "";
}

InMemoryDrawingMapper::InMemoryDrawingMapper() {
    _parser = new Parser(new Scanner(), new Builder());
}

int InMemoryDrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    return 0;
}

std::list<Shape *> InMemoryDrawingMapper::convertShapes(char * shape_string) {
    _parser->clear();
    _parser->setInput(shape_string);
    _parser->parse();
    return _parser->getShapes();
}

void InMemoryDrawingMapper::cleanCache() {
    _domainObjects.clear();
    _parser->clear();
}