#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include "drawing.h"
#include "painter.h"
#include <list>
#include <iostream>


UnitOfWork * UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork() {
    
}

void UnitOfWork::registerNew(DomainObject * domainObject) {
    _new[domainObject->id()] = domainObject;
}

void UnitOfWork::registerClean(DomainObject * domainObject) {
    _clean[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDirty(DomainObject * domainObject) {
    if(!inNew(domainObject->id())) {
        _dirty[domainObject->id()] = domainObject;
        _clean.erase(domainObject->id());
    }
}

void UnitOfWork::registerDeleted(DomainObject * domainObject) {
    _deleted[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
    _new.erase(domainObject->id());
    _dirty.erase(domainObject->id());
}

bool UnitOfWork::inNew(std::string id) const {
    return _new.count(id);
}

bool UnitOfWork::inClean(std::string id) const {
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const {
    return _dirty.count(id);
}

bool UnitOfWork::inDeleted(std::string id) const {
    return _deleted.count(id);
}

void UnitOfWork::commit() {
    for(auto dirtyObj : _dirty) {
        Drawing * drawing = dynamic_cast<Drawing *>(dirtyObj.second);
        if(drawing)
            DrawingMapper::instance()->update(dirtyObj.second->id());
        else
            PainterMapper::instance()->update(dirtyObj.second->id());
        registerClean(dirtyObj.second);
    }
    _dirty.clear();
    for(auto newObj : _new) {
        Drawing * drawing = dynamic_cast<Drawing *>(newObj.second);
        if(drawing)
            DrawingMapper::instance()->add(newObj.second);
        else
            PainterMapper::instance()->add(newObj.second);
        registerClean(newObj.second);
    }
    _new.clear();
    for(auto deleteObj : _deleted) {
        Drawing * drawing = dynamic_cast<Drawing *>(deleteObj.second);
        if(drawing)
            DrawingMapper::instance()->del(deleteObj.second->id());
        else
            PainterMapper::instance()->del(deleteObj.second->id());
    }
    _deleted.clear();
}

void UnitOfWork::destoryInstance() {
    if(_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

UnitOfWork * UnitOfWork::instance() {
    if (_instance == nullptr)
    {
        _instance = new UnitOfWork();
    }
    return _instance;
}