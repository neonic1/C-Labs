#include "ingredient.h"

Ingredient::Ingredient(QString name, double price, int volume, int kind) {
    this->name = name;
    this->price = price;
    this->volume = volume;
    this->kind = kind;
}

Ingredient::Ingredient(const Ingredient &obj) {
    name = obj.name;
    price = obj.price;
    volume = obj.volume;
    kind = obj.kind;
}

Ingredient Ingredient::operator=(Ingredient obj) {
    name = obj.name;
    price = obj.price;
    volume = obj.volume;
    kind = obj.kind;
    return *this;
}
