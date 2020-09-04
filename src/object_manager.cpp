#include "object_manager.hpp"

#include "object.hpp"

ObjectManager::ObjectManager() : _objects()
{
}

ObjectManager::~ObjectManager()
{
    for (auto object : _objects)
    {
        delete object;
    }
}

void ObjectManager::addObject(Object *object)
{
    _objects.push_back(object);
}

std::vector<Object *> const &ObjectManager::getObjects() const
{
    return _objects;
}
