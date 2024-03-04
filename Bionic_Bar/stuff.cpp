#include "stuff.h"

void Stuff::load() {
    ice.setName("Ice");
    ice.setPrice(0.01);
    ice.setVolume(1);
    ice.setKind(3);

    QSqlDatabase db = QSqlDatabase::database("bionic");

    QSqlQuery query1(db);
    query1.exec("SELECT name, price, kind FROM basicingredients");
    while(query1.next()) {
        QString name = query1.value(0).toString();
        double price = query1.value(1).toDouble();
        int kind = query1.value(2).toInt();
        Ingredient ingredient(name, price, 1, kind);
        switch(kind) {
        case 1: {
            strongDrinks.append(ingredient);
            break;
        }
        case 2: {
            softDrinks.append(ingredient);
            break;
        }
        case 4: {
            garnishes.append(ingredient);
            break;
        }
        }
    }
    QSqlQuery query2(db);
    QSqlQuery query3(db);
    QSqlQuery query4(db);
    query2.exec("SELECT drink_id, name FROM drinks WHERE type_id = 1");
    while(query2.next()) {
        int drink_id = query2.value(0).toInt();
        QString name = query2.value(1).toString();
        Drink drink(name);
        barDrinks.append(drink);

        query3.prepare("SELECT basicIngredient_id, volume FROM drinkingredients WHERE drink_id = :number");
        query3.bindValue(":number", drink_id);
        query3.exec();
        while(query3.next()) {
            Ingredient ingredient;
            int basicIngredient_id = query3.value(0).toInt();
            int ingredientVolume = query3.value(1).toInt();

            query4.prepare("SELECT name, price, kind FROM basicingredients WHERE basicIngredient_id = :number2");
            query4.bindValue(":number2", basicIngredient_id);
            query4.exec();
            query4.next();
            QString ingredientName = query4.value(0).toString();
            double ingredientPrice = query4.value(1).toDouble();
            int ingredientKind = query4.value(2).toInt();
            query4.seek(-1);
            ingredient.setName(ingredientName);
            ingredient.setPrice(ingredientPrice);
            ingredient.setVolume(ingredientVolume);
            ingredient.setKind(ingredientKind);
            barDrinks.last().composition.append(ingredient);
        }
        query3.seek(-1);
    }

    for(int i = 0; i < barDrinks.size(); i++) barDrinks[i].recalculatePrice();

}
