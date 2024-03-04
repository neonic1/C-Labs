#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "ui_window.h"
#include <QLabel>
#include "customer.h"
#include "stuff.h"
#include "exceptions.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();


private slots:
    void on_enterScreenSignInBtn_clicked();
    void on_signInScreenOKBtn_clicked();
    void on_enterScreenSignUpBtn_clicked();
    void on_signUpOKBtn_clicked();
    void enterLogin();
    void logOut();
    void goToProfile();
    void goToBuyScreen();
    void deleteDrinkFromOrderList(int drinkNumber);
    void goBack();
    void on_mainMenuMyDrinksBtn_clicked();
    void on_mainMenuBarDrinksBtn_clicked();
    void on_mainMenuHistoryBtn_clicked();
    void deleteMyDrink(int drinkNumber);
    void deleteHistoryDrink(int drinkNumber);
    void goToCustomizeDrink(const QString &constDrinkNumber);
    void removePiece(int ingredientNumber);
    void addPiece(int ingredientNumber);
    void goToIngredientsPage();
    void addNewIngredient(const QString &constIngredientNumber);
    void on_backToMainDrinkPage_clicked();
    void on_customizeDrinkAddToCartBtn_clicked();
    void on_newDrinkNameOKBtn_clicked();
    void on_buyScreenCheckoutBtn_clicked();

private:
    Ui::Window *ui;
    Customer customer;
    Stuff stuff;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    int exponent;
    int position;
    int enteredPIN;
    QList<QLabel *> enteredDigitsLabels;
    QVector<int> previousPages;
    QSignalMapper *buyScreenSignalMapper;
    QSignalMapper *myDrinksDeleteSignalMapper;
    QSignalMapper *historyDrinksDeleteSignalMapper;
    QSignalMapper *goToCustomizeDrinkSignalMapper;
    QSignalMapper *removePieceSignalMapper;
    QSignalMapper *addPieceSignalMapper;
    QSignalMapper *addNewIngredientSignalMapper;
    Drink customDrink;
    int customDrinkPieceCounter;
    bool oldDrink = false;//если этот напиток уже был когда-то создан
    bool changes = false;//если в старый напиток были внесены изменения
    void setButtonsStyleSheets();
    void setProfile();
    void buyScreenPriceCalculation();
    void setBuyScreenScrollAreaWidget();
    void setMyDrinksScrollAreaWidget();
    void setHistoryScrollAreaWidget();
    void makeDrink();
    void refreshCartCounter();
};

#endif // WINDOW_H
