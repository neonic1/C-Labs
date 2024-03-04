#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "drink.h"

class Customer
{
private:
    QString login;
    QString name;
    QString surname;
    int password;
    int birthYear;
    double cash;
public:
    Customer() {}
    QVector<Drink> purchaseHistory;
    QVector<Drink> customerDrinks;
    QVector<Drink> cart;

    void setLogin(QString login) {this->login = login;}
    QString getLogin() {return login;}
    void setName(QString name) {this->name = name;}
    QString getName() {return name;}
    void setSurname(QString surname) {this->surname = surname;}
    QString getSurname() {return surname;}
    void setPassword(int password) {this->password = password;}
    bool checkCorrectPassword (int password);
    void setBirthYear(int birthYear) {this->birthYear = birthYear;}
    int getBirthYear() {return birthYear;}
    void setCash(double cash) {this->cash = cash;}
    void reduceCash(double value) {this->cash -= value;}
    double getCash() {return cash;}
    bool authorization(QString customerLogin);
    bool saveProfile();
    void clear();
};

#endif // CUSTOMER_H
