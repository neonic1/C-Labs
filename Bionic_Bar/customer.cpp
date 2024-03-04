#include "customer.h"

bool Customer::checkCorrectPassword(int password) {
    if(password == this->password)
        return true;
    else return false;
}

bool Customer::authorization(QString customerLogin) {
    bool validLogin = false;
    QSqlDatabase db1 = QSqlDatabase::database("bionic");
    QSqlQuery query(db1);
    QSqlQuery query2(db1);
    QSqlQuery query3(db1);
    QSqlQuery query4(db1);
    query.prepare("SELECT customer_id, name, surname, password, birthYear, cash FROM customers WHERE login = :log");
    query.bindValue(":log", customerLogin);
    query.exec();
    if(query.next()) {
        validLogin = true;
        int customer_id = query.value(0).toInt();
        name = query.value(1).toString();
        surname = query.value(2).toString();
        password = query.value(3).toInt();
        birthYear = query.value(4).toInt();
        cash = query.value(5).toDouble();

        query2.prepare("SELECT drink_id, name FROM drinks WHERE type_id = 2 AND customer_id = :id");
        query2.bindValue(":id", customer_id);
        query2.exec();
        while(query2.next()) {
            int drink_id = query2.value(0).toInt();
            QString name = query2.value(1).toString();
            Drink drink(name);
            purchaseHistory.append(drink);

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
                purchaseHistory.last().composition.append(ingredient);
            }
            query3.seek(-1);
        }
        query2.seek(-1);

        query2.prepare("SELECT drink_id, name FROM drinks WHERE type_id = 3 AND customer_id = :id");
        query2.bindValue(":id", customer_id);
        query2.exec();
        while(query2.next()) {
            int drink_id = query2.value(0).toInt();
            QString name = query2.value(1).toString();
            Drink drink(name);
            customerDrinks.append(drink);

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
                customerDrinks.last().composition.append(ingredient);
            }
            query3.seek(-1);
        }
        query2.seek(-1);
    }
    query.seek(-1);
    if(validLogin) return true;
    else return false;
}

bool Customer::saveProfile() {
    QSqlDatabase db2 = QSqlDatabase::database("bionic");
    QSqlQuery query(db2);
    query.prepare("SELECT customer_id FROM customers WHERE login = :log");
    query.bindValue(":log", login);
    query.exec();
    if(query.next()) return false;
    else {
        query.seek(-1);
        query.prepare("INSERT INTO customers (login, name, surname, password, birthYear, cash) "
                      "VALUES (?, ?, ?, ?, ?, ?)");
        query.addBindValue(login);
        query.addBindValue(name);
        query.addBindValue(surname);
        query.addBindValue(password);
        query.addBindValue(birthYear);
        query.addBindValue(cash);
        query.exec();
        return true;
    }
}

void Customer::clear() {
    name = "";
    surname = "";
    birthYear = 0;
    password = 0;
    login = "";
    cash = 0.0;
    customerDrinks.clear();
    purchaseHistory.clear();
    cart.clear();
}
