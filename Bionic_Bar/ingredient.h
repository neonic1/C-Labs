#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>
#include <QVector>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class Ingredient
{
private:
    QString name;
    double price;
    int volume;
    int kind;//1-strong; 2-soft; 3-ice; 4-garnish

public:
    Ingredient() {}
    Ingredient(QString name, double price, int volume, int kind);
    Ingredient(const Ingredient &obj);

    QString getName() {return name;}
    double getPrice() {return price;}
    int getVolume() {return volume;}
    void decreaseVolume() {volume--;}
    void increaseVolume() {volume++;}
    int getKind() {return kind;}

    void setName(QString name) {this->name = name;}
    void setPrice(double price) {this->price = price;}
    void setVolume(int volume) {this->volume = volume;}
    void setKind(int kind) {this->kind = kind;}

    Ingredient operator=(Ingredient obj);
};

#endif // INGREDIENT_H

