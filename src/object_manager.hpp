#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

class Object;

#include <vector>

class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    void addObject(Object *object);
    template <typename T>
    T const &getObject() const;
    std::vector<Object *> const &getObjects() const;

protected:
    std::vector<Object *> _objects;
};

template <typename T>
T const &ObjectManager::getObject() const
{
    for (auto object : _objects)
    {
        T *castedObject = dynamic_cast<T *>(object);

        if (castedObject != NULL)
        {
            return *castedObject;
        }
    }

    throw "Exception in ObjectManager::getObject(): No object of given type.\n";
}

#endif
