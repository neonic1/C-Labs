#include "drink.h"

Drink::Drink(const Drink &obj) {
    name = obj.name;
    price = obj.price;
    for(int i = 0; i < obj.composition.size(); i++)
        composition.append(obj.composition[i]);
}

Drink Drink::operator=(Drink obj) {
    name = obj.name;
    price = obj.price;
    for(int i = 0; i < obj.composition.size(); i++)
        composition.append(obj.composition[i]);
    return *this;
}

void Drink::clear() {
    name = "";
    price = 0.0;
    composition.clear();
}

void Drink::recalculatePrice() {
    price = 0.0;
    for (int i = 0; i < composition.size(); i++) {
        price += (composition[i].getPrice() * composition[i].getVolume());
    }
}
