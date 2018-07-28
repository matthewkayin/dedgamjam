//Objects are collectable items or destroyable items that can be found on the map

#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.hpp"

class Object : public Entity{

public:
    enum Type{

        DESTROYABLE,
        COLLECTABLE
    };

    Object(Type t);
    Type getType();
    void setType(Type t);
    Object* getNext();
    void setNext(Object *other);
private:
    Type type;
    Object *next;
};

#endif
