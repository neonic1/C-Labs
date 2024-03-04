#ifndef DRINK_H
#define DRINK_H

#include "ingredient.h"

class Drink
{
private:
    QString name;
    double price;
public:
    Drink() {}
    Drink(QString name) {this->name = name;}
    Drink(const Drink &obj);
    QVector<Ingredient> composition;

    void setName(QString name) {this->name = name;}
    QString getName() {return name;}
    void setPrice(double price) {this->price = price;}
    double getPrice() {return price;}
    void recalculatePrice();

    Drink operator=(Drink obj);
    void clear();
};

#endif // DRINK_H
