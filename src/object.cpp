#include "object.hpp"

Object::Object(Type t){

    type = t;
}

typename Object::Type Object::getType(){

    return type;
}

void Object::setType(Type t){

    type = t;
}

Object* Object::getNext(){

    return next;
}

void Object::setNext(Object *other){

    next = other;
}
