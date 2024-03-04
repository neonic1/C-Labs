#ifndef STUFF_H
#define STUFF_H

#include "drink.h"
#include "ingredient.h"

class Stuff
{
private:
    Ingredient ice;
public:
    Stuff() {}

    QVector<Drink> barDrinks;
    QVector<Ingredient> strongDrinks;
    QVector<Ingredient> softDrinks;
    QVector<Ingredient> garnishes;
    Ingredient getIce() {return ice;}
    void load();
};

#endif // STUFF_H
