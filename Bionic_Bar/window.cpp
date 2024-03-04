#include "window.h"
#include "ui_window.h"
#include <QPixmap>
#include <QTimer>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/icons/color_logo.png"));
    setWindowTitle("BionicBar");
    ui->stackedWidget->setCurrentIndex(0);
    setButtonsStyleSheets();
    buyScreenSignalMapper = new QSignalMapper(this);
    myDrinksDeleteSignalMapper = new QSignalMapper(this);
    goToCustomizeDrinkSignalMapper = new QSignalMapper(this);
    historyDrinksDeleteSignalMapper = new QSignalMapper(this);
    removePieceSignalMapper = new QSignalMapper(this);
    addPieceSignalMapper = new QSignalMapper(this);
    addNewIngredientSignalMapper = new QSignalMapper(this);
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("bionicbar");
    if(db.open()) qDebug() << "Database connected.";
    else qDebug() << "Database is not connected.";
    stuff.load();

    connect(ui->signInLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->signUpLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->loginScreenLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->mainMenuLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->profileLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->buyScreenLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->chooseDrinkLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->customizeDrinkLogOutBtn, SIGNAL(clicked()), this, SLOT(logOut()));

    connect(ui->mainMenuBtnPerson, SIGNAL(clicked()), this, SLOT(goToProfile()));
    connect(ui->buyScreenBtnPerson, SIGNAL(clicked()), this, SLOT(goToProfile()));
    connect(ui->chooseDrinkBtnPerson, SIGNAL(clicked()), this, SLOT(goToProfile()));
    connect(ui->customizeDrinkBtnPerson, SIGNAL(clicked()), this, SLOT(goToProfile()));

    connect(ui->mainMenuCartBtn, SIGNAL(clicked()), this, SLOT(goToBuyScreen()));
    connect(ui->profileCartBtn, SIGNAL(clicked()), this, SLOT(goToBuyScreen()));
    connect(ui->chooseDrinkCartBtn, SIGNAL(clicked()), this, SLOT(goToBuyScreen()));
    connect(ui->customizeDrinkCartBtn, SIGNAL(clicked()), this, SLOT(goToBuyScreen()));

    connect(ui->profileGoBackBtn, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->buyScreenGoBackBtn, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->chooseDrinkGoBackBtn, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->customizeDrinkGoBackBtn, SIGNAL(clicked()), this, SLOT(goBack()));

    //enterScreen
    QPixmap enterScreenBackImage(":/backs/backs/enterSceneBack.png");
    ui->enterScreenBackLabel->setPixmap(enterScreenBackImage);
    //signInScreen
    QPixmap signInScreenBackImage(":/backs/backs/loginSceneBack.png");
    ui->signInScreenBackLabel->setPixmap(signInScreenBackImage);
    //signUpScreen
    QPixmap signUpScreenBackImage(":/backs/backs/loginSceneBack.png");
    ui->signUpScreenBackLabel->setPixmap(signUpScreenBackImage);
    //loginScreen
    QPixmap loginScreenBackImage(":/backs/backs/loginSceneBack.png");
    ui->loginScreenBackLabel->setPixmap(loginScreenBackImage);
    enteredDigitsLabels.push_back(ui->loginScreen4DigitLabel);
    enteredDigitsLabels.push_back(ui->loginScreen3DigitLabel);
    enteredDigitsLabels.push_back(ui->loginScreen2DigitLabel);
    enteredDigitsLabels.push_back(ui->loginScreen1DigitLabel);
    connect(ui->loginScreenBtn0, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn1, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn2, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn3, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn4, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn5, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn6, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn7, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn8, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtn9, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtnOK, SIGNAL(clicked()), this, SLOT(enterLogin()));
    connect(ui->loginScreenBtnDel, SIGNAL(clicked()), this, SLOT(enterLogin()));
    //mainMenu
    QPixmap mainMenuBackImage(":/backs/backs/mainMenuBack.png");
    ui->mainMenuBackLabel->setPixmap(mainMenuBackImage);
    Drink drink;
    goToCustomizeDrinkSignalMapper->setMapping(ui->mainMenuCreateNewDrinkBtn, "0");
    connect(ui->mainMenuCreateNewDrinkBtn, SIGNAL(clicked()), goToCustomizeDrinkSignalMapper, SLOT(map()));
    connect(goToCustomizeDrinkSignalMapper, SIGNAL(mapped(const QString &)), this, SLOT(goToCustomizeDrink(const QString &)));
    //profile
    QPixmap profileBackImage(":/backs/backs/profileBack.png");
    ui->profileBackLabel->setPixmap(profileBackImage);
    //buyScreen
    QPixmap buyScreenBackImage(":/backs/backs/buyScreenBack.png");
    ui->buyScreenBackLabel->setPixmap(buyScreenBackImage);
    connect(buyScreenSignalMapper, SIGNAL(mapped(int)), this, SLOT(deleteDrinkFromOrderList(int)));
    //chooseDrink
    QPixmap chooseDrinkBackImage(":/backs/backs/chooseDrinkBack.png");
    ui->chooseDrinkBackLabel->setPixmap(chooseDrinkBackImage);
    connect(myDrinksDeleteSignalMapper, SIGNAL(mapped(int)), this, SLOT(deleteMyDrink(int)));
    connect(historyDrinksDeleteSignalMapper, SIGNAL(mapped(int)), this, SLOT(deleteHistoryDrink(int)));
    //customizeDrink
    QPixmap customizeDrinkBackImage(":/backs/backs/chooseDrinkBack.png");
    ui->customizeDrinkBackLabel->setPixmap(customizeDrinkBackImage);
    connect(removePieceSignalMapper, SIGNAL(mapped(int)), this, SLOT(removePiece(int)));
    connect(addPieceSignalMapper, SIGNAL(mapped(int)), this, SLOT(addPiece(int)));
    connect(ui->strongDrinksBtn, SIGNAL(clicked()), this, SLOT(goToIngredientsPage()));
    connect(ui->softDrinksBtn, SIGNAL(clicked()), this, SLOT(goToIngredientsPage()));
    connect(ui->garnishesBtn, SIGNAL(clicked()), this, SLOT(goToIngredientsPage()));
    addNewIngredientSignalMapper->setMapping(ui->iceBtn, "0");
    connect(ui->iceBtn, SIGNAL(clicked()), addNewIngredientSignalMapper, SLOT(map()));
    connect(addNewIngredientSignalMapper, SIGNAL(mapped(const QString &)), this, SLOT(addNewIngredient(const QString &)));
    //newDrinkName
    QPixmap newDrinkNameBackImage(":/backs/backs/chooseDrinkBack.png");
    ui->newDrinkNameBackLabel->setPixmap(newDrinkNameBackImage);
    ui->newDrinkNameErrorLabel->setAlignment(Qt::AlignCenter);
}

void Window::setButtonsStyleSheets() {

    QFont f;
        f.setBold(true);
        f.setFamily("Nirmala UI");
        f.setPointSize(25);
    QFont f2;
        f2.setBold(true);
        f2.setFamily("Nirmala UI");
        f2.setPointSize(20);
    QFont f3;
        f3.setBold(true);
        f3.setFamily("Nirmala UI");
        f3.setPointSize(18);
    //enterScreen
    ui->enterScreenSignInBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/nainMenuBtnColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/mainMenuBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/nainMenuBtnHovered.png);}");
    ui->enterScreenSignInBtn->setFont(f2);
    ui->enterScreenSignUpBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/nainMenuBtnColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/mainMenuBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/nainMenuBtnHovered.png);}");
    ui->enterScreenSignUpBtn->setFont(f2);
    //signInScreen
    ui->signInErrorLabel->setAlignment(Qt::AlignCenter);
    ui->signInLineEdit->setStyleSheet("color:white; background-color:transparent;");
    ui->signInLineEdit->setFont(f2);
    ui->signInScreenOKBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->signInScreenOKBtn->setFont(f3);
    ui->signInLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    //signUpScreen
    ui->signUpLoginLineEdit->setStyleSheet("color:white; background-color:transparent;");
    ui->signUpLoginLineEdit->setFont(f2);
    ui->signUpNameLineEdit->setStyleSheet("color:white; background-color:transparent;");
    ui->signUpNameLineEdit->setFont(f2);
    ui->signUpSurnameLineEdit->setStyleSheet("color:white; background-color:transparent;");
    ui->signUpSurnameLineEdit->setFont(f2);
    ui->signUpBirthYearLineEdit->setStyleSheet("color:white; background-color:transparent;");
    ui->signUpBirthYearLineEdit->setFont(f2);
    ui->signUpPINLineEdit->setStyleSheet("color:white; background-color:transparent;");
    ui->signUpPINLineEdit->setFont(f2);
    ui->signUpOKBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->signUpOKBtn->setFont(f3);
    ui->signUpLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    ui->signUpLoginExistErrorLabel->setAlignment(Qt::AlignCenter);
    //loginScreen
    ui->loginScreenBtn0->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn0->setFont(f);
    ui->loginScreenBtn1->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn1->setFont(f);
    ui->loginScreenBtn2->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn2->setFont(f);
    ui->loginScreenBtn3->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn3->setFont(f);
    ui->loginScreenBtn4->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn4->setFont(f);
    ui->loginScreenBtn5->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn5->setFont(f);
    ui->loginScreenBtn6->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn6->setFont(f);
    ui->loginScreenBtn7->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn7->setFont(f);
    ui->loginScreenBtn8->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn8->setFont(f);
    ui->loginScreenBtn9->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtn9->setFont(f);
    ui->loginScreenBtnDel->setStyleSheet("QPushButton {border-image: url(:/icons/icons/deleteBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/deleteBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/deleteBtnHovered.png);}");
    ui->loginScreenBtnOK->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->loginScreenBtnOK->setFont(f3);
    ui->loginScreenLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    //mainMenu
    ui->mainMenuLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    ui->mainMenuBtnPerson->setStyleSheet("QPushButton {border-image: url(:/icons/icons/personBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/personBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/personBtnHovered.png);}");
    ui->mainMenuCartBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/cartBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/cartBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/cartBtnHovered.png);}");
    ui->mainMenuCreateNewDrinkBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/nainMenuBtnColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/mainMenuBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/nainMenuBtnHovered.png);}");
    ui->mainMenuCreateNewDrinkBtn->setFont(f2);
    ui->mainMenuMyDrinksBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/nainMenuBtnColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/mainMenuBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/nainMenuBtnHovered.png);}");
    ui->mainMenuMyDrinksBtn->setFont(f2);
    ui->mainMenuBarDrinksBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/nainMenuBtnColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/mainMenuBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/nainMenuBtnHovered.png);}");
    ui->mainMenuBarDrinksBtn->setFont(f2);
    ui->mainMenuHistoryBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/nainMenuBtnColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/mainMenuBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/nainMenuBtnHovered.png);}");
    ui->mainMenuHistoryBtn->setFont(f2);
    //profile
    ui->profileLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    ui->profileGoBackBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/backBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/backBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/backBtnHovered.png);}");
    ui->profileCartBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/cartBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/cartBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/cartBtnHovered.png);}");
    //buyScreen
    ui->buyScreenLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    ui->buyScreenGoBackBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/backBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/backBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/backBtnHovered.png);}");
    ui->buyScreenBtnPerson->setStyleSheet("QPushButton {border-image: url(:/icons/icons/personBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/personBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/personBtnHovered.png);}");
    ui->buyScreenCheckoutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/checkoutBtn.png);} QPushButton:pressed{border-image:url(:/icons/icons/checkoutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/checkoutBtnHovered.png);}");
    ui->buyScreenScrollArea->setStyleSheet("background-color:transparent;");
    ui->buyScreenScrollArea->setFrameShape(QFrame::NoFrame);
    //chooseDrink
    ui->chooseDrinkGoBackBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/backBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/backBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/backBtnHovered.png);}");
    ui->chooseDrinkBtnPerson->setStyleSheet("QPushButton {border-image: url(:/icons/icons/personBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/personBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/personBtnHovered.png);}");
    ui->chooseDrinkCartBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/cartBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/cartBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/cartBtnHovered.png);}");
    ui->chooseDrinkLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    ui->chooseDrinkScrollArea->setStyleSheet("background-color:transparent;");
    ui->chooseDrinkScrollArea->setFrameShape(QFrame::NoFrame);
    //customizeDrink
    ui->customizeDrinkGoBackBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/backBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/backBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/backBtnHovered.png);}");
    ui->customizeDrinkBtnPerson->setStyleSheet("QPushButton {border-image: url(:/icons/icons/personBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/personBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/personBtnHovered.png);}");
    ui->customizeDrinkCartBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/cartBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/cartBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/cartBtnHovered.png);}");
    ui->customizeDrinkLogOutBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/signOutBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/signOutBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/signOutBtnHovered.png);}");
    ui->customizeDrinkAddToCartBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/addToCartBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/addToCartBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/addToCartBtnHovered.png);}");
    ui->backToMainDrinkPage->setStyleSheet("QPushButton {border-image: url(:/icons/icons/backBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/backBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/backBtnHovered.png);}");
    ui->strongDrinksBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/buttonPointerColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/buttonPointerPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/buttonPointerHovered.png);}");
    ui->strongDrinksBtn->setFont(f2);
    ui->softDrinksBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/buttonPointerColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/buttonPointerPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/buttonPointerHovered.png);}");
    ui->softDrinksBtn->setFont(f2);
    ui->iceBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/buttonPlusColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/buttonPlusPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/buttonPlusHovered.png);}");
    ui->iceBtn->setFont(f2);
    ui->garnishesBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/buttonPointerColor.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/buttonPointerPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/buttonPointerHovered.png);}");
    ui->garnishesBtn->setFont(f2);
    ui->customizeDrinkStackedWidget->setStyleSheet("background-color:transparent;");
    ui->customizeDrinkStackedWidget->setFrameShape(QFrame::NoFrame);
    ui->ingredientsScrollArea->setStyleSheet("background-color:transparent;");
    ui->ingredientsScrollArea->setFrameShape(QFrame::NoFrame);
    //newDrinkName
    ui->newDrinkNameOKBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/roundButton.png);} QPushButton:pressed{color: rgb(14, 118, 255); border-image:url(:/icons/icons/roundBtnWhite.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/roundButtonHovered.png);}");
    ui->newDrinkNameOKBtn->setFont(f3);
    ui->newDrinkNameLineEdit->setStyleSheet("color:white; background-color:transparent;");
    ui->newDrinkNameLineEdit->setFont(f2);
}

void Window::setProfile() {
    ui->loginScreenNameSurLabel->setText(customer.getName() + " " + customer.getSurname());
    ui->mainMenuNameSurLabel->setText(customer.getName() + " " + customer.getSurname());
    ui->mainMenuCashCounterLabel->setText("$" + QString::number(customer.getCash()));
    ui->profileNameLabel->setText(customer.getName());
    ui->profileSurnameLabel->setText(customer.getSurname());
    ui->profileBirthYearLabel->setText(QString::number(customer.getBirthYear()));
    ui->profileCashLabel->setText("$" + QString::number(customer.getCash()));
    ui->buyScreenNameSurLabel->setText(customer.getName() + " " + customer.getSurname());
    ui->buyScreenCashCounterLabel->setText("$" + QString::number(customer.getCash()));
    ui->chooseDrinkNameSurLabel->setText(customer.getName() + " " + customer.getSurname());
    ui->chooseDrinkCashCounterLabel->setText("$" + QString::number(customer.getCash()));
    ui->customizeDrinkNameSurLabel->setText(customer.getName() + " " + customer.getSurname());
    ui->customizeDrinkCashCounterLabel->setText("$" + QString::number(customer.getCash()));
    ui->mainMenuCartCounterLabel->setText("0");
    ui->profileCartCounterLabel->setText("0");
    ui->chooseDrinkCartCounterLabel->setText("0");
    ui->customizeDrinkCartCounterLabel->setText("0");
}

Window::~Window()
{
    db.close();
    db.removeDatabase("bionic");
    delete ui;
}

void Window::on_enterScreenSignInBtn_clicked() {
    ui->signInLineEdit->setText("");
    ui->signInErrorLabel->setText("");
    ui->stackedWidget->setCurrentIndex(1);
}

void Window::on_signInScreenOKBtn_clicked() {
    ui->signInErrorLabel->setText("");
    if(customer.authorization(ui->signInLineEdit->text())) {
        customer.setLogin(ui->signInLineEdit->text());
        setProfile();
        exponent = 3;
        position = 0;
        enteredPIN = 0;
        for(int i = 0; i <= 3; i++) enteredDigitsLabels[i]->setText("_");
        ui->stackedWidget->setCurrentIndex(2);
    } else ui->signInErrorLabel->setText("There is no signed up persons with this login.");
}

void Window::on_enterScreenSignUpBtn_clicked() {
    ui->signUpLoginLineEdit->setText("");
    ui->signUpNameLineEdit->setText("");
    ui->signUpSurnameLineEdit->setText("");
    ui->signUpBirthYearLineEdit->setText("");
    ui->signUpPINLineEdit->setText("");
    ui->signUpLoginExistErrorLabel->setText("");
    ui->signUpLoginErrorLabel->setText("");
    ui->signUpNameErrorLabel->setText("");
    ui->signUpSurnameErrorLabel->setText("");
    ui->signUpBirthYearErrorLabel->setText("");
    ui->signUpPINErrorLabel->setText("");
    ui->stackedWidget->setCurrentIndex(10);
}

void Window::on_signUpOKBtn_clicked() {
    ui->signUpLoginExistErrorLabel->setText("");
    ui->signUpLoginErrorLabel->setText("");
    ui->signUpNameErrorLabel->setText("");
    ui->signUpSurnameErrorLabel->setText("");
    ui->signUpBirthYearErrorLabel->setText("");
    ui->signUpPINErrorLabel->setText("");
    int counter = 0;
    QString err;
    err = stringException(ui->signUpLoginLineEdit->text(), true);
    if(err != "") {
        ui->signUpLoginErrorLabel->setText(err);
        err = "";
    } else counter++;
    err = stringException(ui->signUpNameLineEdit->text());
    if(err != "") {
        ui->signUpNameErrorLabel->setText(err);
        err = "";
    } else counter++;
    err = stringException(ui->signUpSurnameLineEdit->text());
    if(err != "") {
        ui->signUpSurnameErrorLabel->setText(err);
        err = "";
    } else counter++;
    err = intException(ui->signUpBirthYearLineEdit->text(), 1950, 2001);
    if(err != "") {
        ui->signUpBirthYearErrorLabel->setText(err);
        err = "";
    } else counter++;
    err = intException(ui->signUpPINLineEdit->text(), 1000, 9999);
    if(err != "") {
        ui->signUpPINErrorLabel->setText(err);
        err = "";
    } else counter++;
    if(counter == 5) {
        customer.setLogin(ui->signUpLoginLineEdit->text());
        customer.setName(ui->signUpNameLineEdit->text());
        customer.setSurname(ui->signUpSurnameLineEdit->text());
        customer.setBirthYear(ui->signUpBirthYearLineEdit->text().toInt());
        customer.setPassword(ui->signUpPINLineEdit->text().toInt());
        customer.setCash(500.0);
        if(customer.saveProfile()) {
            setProfile();
            ui->stackedWidget->setCurrentIndex(3);
        } else ui->signUpLoginExistErrorLabel->setText("This login is already exists.");
    }
}

void Window::enterLogin() {
    QPushButton *button = static_cast<QPushButton *>(sender());
    if(button->text() == "OK") {
        if(position == 4) {
            if(customer.checkCorrectPassword(enteredPIN)) ui->stackedWidget->setCurrentIndex(3);
            else; //анимация
            exponent = 3;
            position = 0;
            enteredPIN = 0;
            for(int i = 0; i <= 3; i++) enteredDigitsLabels[i]->setText("_");
        }
        return;
    }
    if(button->text() == "") {
        if(position > 0) {
            position--;
            enteredDigitsLabels[position]->setText("_");
            exponent++;
        }
        return;
    }
    if(position < 4) {
        enteredDigitsLabels[position]->setText(button->text());
        position++;
        int enteredNumber = (button->text()).toInt();
        enteredPIN += enteredNumber * pow(10, exponent);
        exponent--;
    }
}

void Window::logOut() {
    customer.clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void Window::goToProfile() {
    previousPages.append(ui->stackedWidget->currentIndex());
    ui->stackedWidget->setCurrentIndex(4);
}

void Window::goToBuyScreen() {
    setBuyScreenScrollAreaWidget();
    buyScreenPriceCalculation();
    previousPages.append(ui->stackedWidget->currentIndex());
    ui->stackedWidget->setCurrentIndex(5);
}

void Window::buyScreenPriceCalculation() {
    double sumPrice = 0.0;
    for(int i = 0; i < customer.cart.size(); i++)
        sumPrice += customer.cart[i].getPrice();
    ui->buyScreenTotalCounterLabel->setText("$" + QString::number(sumPrice));
}

void Window::setBuyScreenScrollAreaWidget() {
    QFont f;
    f.setBold(true);
    f.setFamily("Nirmala UI");
    f.setPointSize(20);

    QWidget *scrollAreaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    for(int i = 0; i < customer.cart.size(); i++) {
        QWidget *rowWidget = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout();
        QLabel *drinkLabel = new QLabel(customer.cart[i].getName());
        drinkLabel->setStyleSheet("QLabel {color:white;}");
        drinkLabel->setFont(f);
        drinkLabel->setMinimumSize(500, 51);
        rowLayout->addWidget(drinkLabel);

        QLabel *drinkPriceLabel = new QLabel("$" + QString::number(customer.cart[i].getPrice()));
        drinkPriceLabel->setStyleSheet("QLabel {color:white;}");
        drinkPriceLabel->setFont(f);
        drinkPriceLabel->setMinimumSize(90, 51);
        rowLayout->addWidget(drinkPriceLabel);

        QPushButton *removeDrinkBtn = new QPushButton();
        removeDrinkBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/cancelBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/cancelBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/cancelBtnHovered.png);}");
        removeDrinkBtn->setFixedSize(41, 41);
        buyScreenSignalMapper->setMapping(removeDrinkBtn, i);
        connect(removeDrinkBtn, SIGNAL(clicked()), buyScreenSignalMapper, SLOT(map()));
        rowLayout->addWidget(removeDrinkBtn);

        rowWidget->setLayout(rowLayout);
        vLayout->addWidget(rowWidget);
    }
    vLayout->addStretch(1);
    scrollAreaWidget->setLayout(vLayout);
    ui->buyScreenScrollArea->setWidget(scrollAreaWidget);
}

void Window::deleteDrinkFromOrderList(int drinkNumber) {
    customer.cart.remove(drinkNumber);
    ui->buyScreenScrollArea->widget()->deleteLater();
    buyScreenPriceCalculation();
    setBuyScreenScrollAreaWidget();
}

void Window::goBack() {
    if(!previousPages.isEmpty())
        ui->stackedWidget->setCurrentIndex(previousPages.takeLast());
}

void Window::on_mainMenuMyDrinksBtn_clicked() {
    setMyDrinksScrollAreaWidget();
    previousPages.append(ui->stackedWidget->currentIndex());
    ui->stackedWidget->setCurrentIndex(6);
}

void Window::setMyDrinksScrollAreaWidget() {
    QFont f;
    f.setBold(true);
    f.setFamily("Nirmala UI");
    f.setPointSize(20);

    QWidget *scrollAreaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    for(int i = 0; i < customer.customerDrinks.size(); i++) {
        QWidget *rowWidget = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout();
        QPushButton *drinkBtn = new QPushButton(customer.customerDrinks[i].getName());
        drinkBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/chooseDrinkBtnColor.png);} QPushButton:pressed{color: transparent; border-image:url(:/icons/icons/chooseDrinkBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/chooseDrinkBtnHovered.png);}");
        drinkBtn->setFont(f);
        drinkBtn->setMinimumSize(550, 51);
        rowLayout->addWidget(drinkBtn);
        QString drinkNumber = "1" + QString::number(i);
        goToCustomizeDrinkSignalMapper->setMapping(drinkBtn, drinkNumber);
        connect(drinkBtn, SIGNAL(clicked()), goToCustomizeDrinkSignalMapper, SLOT(map()));
        QPushButton *deleteDrinkBtn = new QPushButton();
        deleteDrinkBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/trashBinBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/trashBinBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/trashBinBtnHovered.png);}");
        deleteDrinkBtn->setFixedSize(41, 41);
        myDrinksDeleteSignalMapper->setMapping(deleteDrinkBtn, i);
        connect(deleteDrinkBtn, SIGNAL(clicked()), myDrinksDeleteSignalMapper, SLOT(map()));
        rowLayout->addWidget(deleteDrinkBtn);
        rowWidget->setLayout(rowLayout);
        vLayout->addWidget(rowWidget, 0, Qt::AlignTop);
    }

    vLayout->addStretch(1);
    scrollAreaWidget->setLayout(vLayout);
    ui->chooseDrinkScrollArea->setWidget(scrollAreaWidget);
}

void Window::deleteMyDrink(int drinkNumber) {
    QSqlDatabase db3 = QSqlDatabase::database("bionic");
    QSqlQuery query(db3);
    QSqlQuery query2(db3);
    QSqlQuery query3(db3);
    query.prepare("SELECT customer_id FROM customers WHERE login = :login");
    query.bindValue(":login", customer.getLogin());
    query.exec();
    query.next();
    int customer_id = query.value(0).toInt();
    query2.prepare("SELECT drink_id FROM drinks WHERE type_id = 3 AND customer_id = :id AND name = :name");
    query2.bindValue(":id", customer_id);
    query2.bindValue(":name", customer.customerDrinks[drinkNumber].getName());
    query2.exec();
    query2.next();
    int drink_id = query2.value(0).toInt();
    query3.prepare("DELETE FROM drinkingredients WHERE drink_id = :drink_id");
    query3.bindValue(":drink_id", drink_id);
    query3.exec();
    query2.seek(-1);
    query2.prepare("DELETE FROM drinks WHERE type_id = 3 AND customer_id = :id AND name = :name");
    query2.bindValue(":id", customer_id);
    query2.bindValue(":name", customer.customerDrinks[drinkNumber].getName());
    query2.exec();

    customer.customerDrinks.remove(drinkNumber);
    ui->chooseDrinkScrollArea->widget()->deleteLater();
    setMyDrinksScrollAreaWidget();
}

void Window::on_mainMenuBarDrinksBtn_clicked() {
    QFont f;
    f.setBold(true);
    f.setFamily("Nirmala UI");
    f.setPointSize(20);

    QWidget *scrollAreaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    for(int i = 0; i < stuff.barDrinks.size(); i++) {
        QPushButton *drinkBtn = new QPushButton(stuff.barDrinks[i].getName());
        drinkBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/chooseDrinkBtnColor.png);} QPushButton:pressed{color: transparent; border-image:url(:/icons/icons/chooseDrinkBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/chooseDrinkBtnHovered.png);}");
        drinkBtn->setFont(f);
        drinkBtn->setMinimumHeight(51);
        QString drinkNumber = "2" + QString::number(i);
        goToCustomizeDrinkSignalMapper->setMapping(drinkBtn, drinkNumber);
        connect(drinkBtn, SIGNAL(clicked()), goToCustomizeDrinkSignalMapper, SLOT(map()));
        vLayout->addWidget(drinkBtn, 0, Qt::AlignTop);
    }

    vLayout->addStretch(1);
    scrollAreaWidget->setLayout(vLayout);
    ui->chooseDrinkScrollArea->setWidget(scrollAreaWidget);

    previousPages.append(ui->stackedWidget->currentIndex());
    ui->stackedWidget->setCurrentIndex(6);
}

void Window::on_mainMenuHistoryBtn_clicked() {
    setHistoryScrollAreaWidget();
    previousPages.append(ui->stackedWidget->currentIndex());
    ui->stackedWidget->setCurrentIndex(6);
}

void Window::setHistoryScrollAreaWidget() {
    QFont f;
    f.setBold(true);
    f.setFamily("Nirmala UI");
    f.setPointSize(20);

    QWidget *scrollAreaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    for(int i = 0; i < customer.purchaseHistory.size(); i++) {
        QWidget *rowWidget = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout();
        QPushButton *drinkBtn = new QPushButton(customer.purchaseHistory[i].getName());
        drinkBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/chooseDrinkBtnColor.png);} QPushButton:pressed{color: transparent; border-image:url(:/icons/icons/chooseDrinkBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/chooseDrinkBtnHovered.png);}");
        drinkBtn->setFont(f);
        drinkBtn->setMinimumSize(550, 51);
        rowLayout->addWidget(drinkBtn);
        QString drinkNumber = "3" + QString::number(i);
        goToCustomizeDrinkSignalMapper->setMapping(drinkBtn, drinkNumber);
        connect(drinkBtn, SIGNAL(clicked()), goToCustomizeDrinkSignalMapper, SLOT(map()));
        QPushButton *deleteDrinkBtn = new QPushButton();
        deleteDrinkBtn->setStyleSheet("QPushButton {border-image: url(:/icons/icons/trashBinBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/trashBinBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/trashBinBtnHovered.png);}");
        deleteDrinkBtn->setFixedSize(41, 41);
        historyDrinksDeleteSignalMapper->setMapping(deleteDrinkBtn, i);
        connect(deleteDrinkBtn, SIGNAL(clicked()), historyDrinksDeleteSignalMapper, SLOT(map()));
        rowLayout->addWidget(deleteDrinkBtn);
        rowWidget->setLayout(rowLayout);
        vLayout->addWidget(rowWidget, 0, Qt::AlignTop);
    }

    vLayout->addStretch(1);
    scrollAreaWidget->setLayout(vLayout);
    ui->chooseDrinkScrollArea->setWidget(scrollAreaWidget);
}

void Window::deleteHistoryDrink(int drinkNumber) {
    QSqlDatabase db3 = QSqlDatabase::database("bionic");
    QSqlQuery query(db3);
    QSqlQuery query2(db3);
    QSqlQuery query3(db3);
    query.prepare("SELECT customer_id FROM customers WHERE login = :login");
    query.bindValue(":login", customer.getLogin());
    query.exec();
    query.next();
    int customer_id = query.value(0).toInt();
    query2.prepare("SELECT drink_id FROM drinks WHERE type_id = 2 AND customer_id = :id AND name = :name");
    query2.bindValue(":id", customer_id);
    query2.bindValue(":name", customer.purchaseHistory[drinkNumber].getName());
    query2.exec();
    query2.next();
    int drink_id = query2.value(0).toInt();
    query3.prepare("DELETE FROM drinkingredients WHERE drink_id = :drink_id");
    query3.bindValue(":drink_id", drink_id);
    query3.exec();
    query2.seek(-1);
    query2.prepare("DELETE FROM drinks WHERE type_id = 2 AND customer_id = :id AND name = :name");
    query2.bindValue(":id", customer_id);
    query2.bindValue(":name", customer.purchaseHistory[drinkNumber].getName());
    query2.exec();

    customer.purchaseHistory.remove(drinkNumber);
    ui->chooseDrinkScrollArea->widget()->deleteLater();
    setHistoryScrollAreaWidget();
}

void Window::goToCustomizeDrink(const QString &constDrinkNumber) {
    QString drinkNumberString = constDrinkNumber;
    QString numberString(drinkNumberString[0]);
    int number = numberString.toInt();
    customDrink.clear();
    if(number == 0) {
        oldDrink = false;
    } else {
        drinkNumberString.remove(0, 1);
        int drinkNumber = drinkNumberString.toInt();
        oldDrink = true;
        changes = false;
        switch(number) {
        case 1: {
            customDrink = customer.customerDrinks[drinkNumber];
            break;
        }
        case 2: {
            customDrink = stuff.barDrinks[drinkNumber];
            break;
        }
        case 3: {
            customDrink = customer.purchaseHistory[drinkNumber];
            break;
        }
        }
    }
    makeDrink();

    previousPages.append(ui->stackedWidget->currentIndex());
    ui->stackedWidget->setCurrentIndex(7);
    ui->customizeDrinkStackedWidget->setCurrentIndex(0);
}

void Window::makeDrink() {
    QFont f;
    f.setBold(true);
    f.setFamily("Nirmala UI");
    f.setPointSize(20);
    //int yPos[] = {614, 558, 502, 446, 390, 334, 278, 222, 166, 110};
    customDrinkPieceCounter = 0;
    int strongBackgroundCounter = 1;
    int softBackgroundCounter = 1;
    qDeleteAll(ui->customDrinkWidget1->children());
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setDirection(QBoxLayout::BottomToTop);
    for(int i = 0; i < customDrink.composition.size(); i++) {
        for(int j = 1; j <= customDrink.composition[i].getVolume(); j++) {

            customDrinkPieceCounter++;
            if(customDrinkPieceCounter == 11) {
                customDrinkPieceCounter--;
                break;
            }
            QLabel *piece = new QLabel();
            switch(customDrink.composition[i].getKind()) {
            case 1: {//strong
                switch(strongBackgroundCounter) {
                case 1: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece4.png);}");
                    break;
                }
                case 2: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece6.png);}");
                    break;
                }
                case 3: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece5.png);}");
                    break;
                }
                case 4: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece7.png);}");
                    break;
                }
                case 5: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece8.png);}");
                    break;
                }
                }
                break;
            }
            case 2: {//soft
                if(customDrink.composition[i].getName() == "Coca-Cola") {
                     piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/cola.png);}");
                     break;
                }
                if(customDrink.composition[i].getName() == "Fanta") {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/fanta.png);}");
                    break;
                }
                if(customDrink.composition[i].getName() == "Sprite") {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/sprite.png);}");
                    break;
                }

                switch(softBackgroundCounter) {
                case 1: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece1.png);}");
                    break;
                }
                case 2: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece2.png);}");
                    break;
                }
                case 3: {
                    piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/drinkPiece3.png);}");
                    break;
                }
                }
                break;
            }
            case 3: {//ice
                piece->setStyleSheet("QLabel {border-image: url(:/icons/icons/drinkPieceIce.png);}");
                break;
            }
            case 4: {//garnish
                if(customDrink.composition[i].getName() == "lemon") {
                     piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/lemon.png);}");
                     break;
                }
                if(customDrink.composition[i].getName() == "lime") {
                     piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/lime.png);}");
                     break;
                }
                if(customDrink.composition[i].getName() == "mint leaves") {
                     piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/mintLeaves.png);}");
                     break;
                }
                if(customDrink.composition[i].getName() == "sugar") {
                     piece->setStyleSheet("QLabel {color:white; border-image: url(:/icons/icons/sugar.png);}");
                     break;
                }
                break;
            }
            }
            piece->setFont(f);
            piece->setAlignment(Qt::AlignCenter);
            //piece->setGeometry(QRect(180, yPos[customDrinkPieceCounter - 1], 314, 61));
            piece->setFixedSize(314, 61);

            if(j == customDrink.composition[i].getVolume()) {
                QWidget *rowWidget = new QWidget();
                QHBoxLayout *rowLayout = new QHBoxLayout();

                QPushButton *minusButton = new QPushButton();
                minusButton->setStyleSheet("QPushButton {border-image: url(:/icons/icons/minusBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/minusBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/minusBtnHovered.png);}");
                //minusButton->setGeometry(115, (yPos[customDrinkPieceCounter - 1] + 6), 51, 51);
                minusButton->setFixedSize(51, 51);
                removePieceSignalMapper->setMapping(minusButton, i);
                connect(minusButton, SIGNAL(clicked()), removePieceSignalMapper, SLOT(map()));
                rowLayout->addWidget(minusButton);

                if(customDrink.composition[i].getKind() != 4 && customDrink.composition[i].getKind() != 3)
                    piece->setText(customDrink.composition[i].getName());
                rowLayout->addWidget(piece);

                QPushButton *plusButton = new QPushButton();
                plusButton->setStyleSheet("QPushButton {border-image: url(:/icons/icons/plusBtnColor.png);} QPushButton:pressed{border-image:url(:/icons/icons/plusBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/plusBtnHovered.png);}");
                //plusButton->setGeometry(509, (yPos[customDrinkPieceCounter - 1] + 6), 51, 51);
                plusButton->setFixedSize(51, 51);
                addPieceSignalMapper->setMapping(plusButton, i);
                connect(plusButton, SIGNAL(clicked()), addPieceSignalMapper, SLOT(map()));
                rowLayout->addWidget(plusButton);

                rowWidget->setLayout(rowLayout);
                vLayout->addWidget(rowWidget, 0, Qt::AlignBottom);
            } else vLayout->addWidget(piece, 0, Qt::AlignHCenter);
        }
        switch(customDrink.composition[i].getKind()) {
        case 1: {
            strongBackgroundCounter++;
            if(strongBackgroundCounter == 6) strongBackgroundCounter = 1;
            break;
        }
        case 2: {
            softBackgroundCounter++;
            if(softBackgroundCounter == 4) softBackgroundCounter = 1;
            break;
        }
        }
    }
    ui->customDrinkWidget1->setLayout(vLayout);
    customDrink.recalculatePrice();
    ui->customizeDrinkPriceLabel->setText("$" + QString::number(customDrink.getPrice()));
}

void Window::removePiece(int ingredientNumber) {
    changes = true;
    if(customDrink.composition[ingredientNumber].getVolume() == 1)
        customDrink.composition.remove(ingredientNumber);
    else customDrink.composition[ingredientNumber].decreaseVolume();
    makeDrink();
}

void Window::addPiece(int ingredientNumber) {
    if(customDrinkPieceCounter < 10) {
        changes = true;
        customDrink.composition[ingredientNumber].increaseVolume();
        makeDrink();
    }
}

void Window::goToIngredientsPage() {
    QPushButton *button = static_cast<QPushButton *>(sender());

    QFont f;
    f.setBold(true);
    f.setFamily("Nirmala UI");
    f.setPointSize(15);

    QWidget *scrollAreaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    if(button->text() == "STRONG DRINKS") {
        for(int i = 0; i < stuff.strongDrinks.size(); i++) {
            QPushButton *ingredientBtn = new QPushButton(stuff.strongDrinks[i].getName());
            ingredientBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/chooseDrinkBtnColor.png);} QPushButton:pressed{color: transparent; border-image:url(:/icons/icons/chooseDrinkBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/chooseDrinkBtnHovered.png);}");
            ingredientBtn->setFont(f);
            ingredientBtn->setMinimumHeight(51);
            QString ingredientNumber = "1" + QString::number(i);
            addNewIngredientSignalMapper->setMapping(ingredientBtn, ingredientNumber);
            connect(ingredientBtn, SIGNAL(clicked()), addNewIngredientSignalMapper, SLOT(map()));
            vLayout->addWidget(ingredientBtn, 0, Qt::AlignTop);
        }
    }
    if(button->text() == "SOFT DRINKS") {
        for(int i = 0; i < stuff.softDrinks.size(); i++) {
            QPushButton *ingredientBtn = new QPushButton(stuff.softDrinks[i].getName());
            ingredientBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/chooseDrinkBtnColor.png);} QPushButton:pressed{color: transparent; border-image:url(:/icons/icons/chooseDrinkBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/chooseDrinkBtnHovered.png);}");
            ingredientBtn->setFont(f);
            ingredientBtn->setMinimumHeight(51);
            QString ingredientNumber = "2" + QString::number(i);
            addNewIngredientSignalMapper->setMapping(ingredientBtn, ingredientNumber);
            connect(ingredientBtn, SIGNAL(clicked()), addNewIngredientSignalMapper, SLOT(map()));
            vLayout->addWidget(ingredientBtn, 0, Qt::AlignTop);
        }
    }
    if(button->text() == "GARNISHES") {
        for(int i = 0; i < stuff.garnishes.size(); i++) {
            QPushButton *ingredientBtn = new QPushButton(stuff.garnishes[i].getName());
            ingredientBtn->setStyleSheet("QPushButton {color:white; border-image: url(:/icons/icons/chooseDrinkBtnColor.png);} QPushButton:pressed{color: transparent; border-image:url(:/icons/icons/chooseDrinkBtnPressed.png);} QPushButton:hover:!pressed{border-image: url(:/icons/icons/chooseDrinkBtnHovered.png);}");
            ingredientBtn->setFont(f);
            ingredientBtn->setMinimumHeight(51);
            QString ingredientNumber = "3" + QString::number(i);
            addNewIngredientSignalMapper->setMapping(ingredientBtn, ingredientNumber);
            connect(ingredientBtn, SIGNAL(clicked()), addNewIngredientSignalMapper, SLOT(map()));
            vLayout->addWidget(ingredientBtn, 0, Qt::AlignTop);
        }
    }

    vLayout->addStretch(1);
    scrollAreaWidget->setLayout(vLayout);
    ui->ingredientsScrollArea->setWidget(scrollAreaWidget);

    ui->customizeDrinkStackedWidget->setCurrentIndex(1);
}

void Window::addNewIngredient(const QString &constIngredientNumber) {
    if(customDrinkPieceCounter < 10) {
        changes = true;
        Ingredient ingredient;
        QString ingredientNumberString = constIngredientNumber;
        QString numberString(ingredientNumberString[0]);
        int number = numberString.toInt();
        if(number == 0) {
            ingredient = stuff.getIce();
        } else {
            ingredientNumberString.remove(0, 1);
            int ingredientNumber = ingredientNumberString.toInt();
            switch(number) {
            case 1: {
                ingredient = stuff.strongDrinks[ingredientNumber];
                break;
            }
            case 2: {
                ingredient = stuff.softDrinks[ingredientNumber];
                break;
            }
            case 3: {
                ingredient = stuff.garnishes[ingredientNumber];
                break;
            }
            }
        }
        bool isMatch = false;
        for(int i = 0; i < customDrink.composition.size(); i++) {
            if(customDrink.composition[i].getName() == ingredient.getName()) {
                customDrink.composition[i].increaseVolume();
                isMatch = true;
                break;
            }
        }
        if(!isMatch) customDrink.composition.append(ingredient);
        makeDrink();
        ui->customizeDrinkStackedWidget->setCurrentIndex(0);
    }
}

void Window::on_backToMainDrinkPage_clicked(){
    ui->customizeDrinkStackedWidget->setCurrentIndex(0);
}

void Window::on_customizeDrinkAddToCartBtn_clicked() {
    if(customDrink.composition.size()) {
        if(oldDrink == true && changes == false) {
            customer.cart.append(customDrink);
            refreshCartCounter();
            ui->stackedWidget->setCurrentIndex(3);
            previousPages.clear();
        } else {
            if(customDrink.getName() != "")
                ui->newDrinkNameLineEdit->setText(customDrink.getName());
            else ui->newDrinkNameLineEdit->setText("My perfect drink");
            ui->newDrinkNameErrorLabel->setText("");
            ui->stackedWidget->setCurrentIndex(8);
        }
    }
}

void Window::refreshCartCounter() {
    ui->mainMenuCartCounterLabel->setText(QString::number(customer.cart.size()));
    ui->profileCartCounterLabel->setText(QString::number(customer.cart.size()));
    ui->chooseDrinkCartCounterLabel->setText(QString::number(customer.cart.size()));
    ui->customizeDrinkCartCounterLabel->setText(QString::number(customer.cart.size()));
}

void Window::on_newDrinkNameOKBtn_clicked() {
    ui->newDrinkNameErrorLabel->setText("");
    QString err = newNameException(ui->newDrinkNameLineEdit->text());
    if(err != "") {
       ui->newDrinkNameErrorLabel->setText(err);
    } else {
        customDrink.setName(ui->newDrinkNameLineEdit->text());
        customer.cart.append(customDrink);
        customer.customerDrinks.append(customDrink);

        QSqlDatabase db4 = QSqlDatabase::database("bionic");
        QSqlQuery query(db4);
        QSqlQuery query2(db4);
        QSqlQuery query3(db4);
        QSqlQuery query4(db4);
        QSqlQuery query5(db4);
        query.prepare("SELECT customer_id FROM customers WHERE login = :login");
        query.bindValue(":login", customer.getLogin());
        query.exec();
        query.next();
        int customer_id = query.value(0).toInt();
        query.seek(-1);
        query2.prepare("INSERT INTO drinks (type_id, customer_id, name) VALUES (3, ?, ?)");
        query2.addBindValue(customer_id);
        query2.addBindValue(customDrink.getName());
        query2.exec();
        QVector<int> basicingredient_id;
        for(int i = 0; i < customDrink.composition.size(); i++) {
            query3.prepare("SELECT basicIngredient_id FROM basicingredients WHERE name = :name AND kind = :kind");
            query3.bindValue(":name", customDrink.composition[i].getName());
            query3.bindValue(":kind", customDrink.composition[i].getKind());
            query3.exec();
            query3.next();
            basicingredient_id.append(query3.value(0).toInt());
            query3.seek(-1);
        }
        query5.prepare("SELECT drink_id FROM drinks WHERE type_id = 3 AND customer_id = :customer_id AND name = :name");
        query5.bindValue(":customer_id", customer_id);
        query5.bindValue(":name", customDrink.getName());
        query5.exec();
        query5.next();
        int drink_id = query5.value(0).toInt();
        query5.seek(-1);
        for(int i = 0; i < customDrink.composition.size(); i++) {
            query4.prepare("INSERT INTO drinkingredients (drink_id, basicIngredient_id, volume) "
                           "VALUES (?, ?, ?)");
            query4.addBindValue(drink_id);
            query4.addBindValue(basicingredient_id.takeFirst());
            query4.addBindValue(customDrink.composition[i].getVolume());
            query4.exec();
        }

        refreshCartCounter();
        ui->stackedWidget->setCurrentIndex(3);
        previousPages.clear();
    }
}

void Window::on_buyScreenCheckoutBtn_clicked() {
    double sumPrice = 0.0;
    for(int i = 0; i < customer.cart.size(); i++)
        sumPrice += customer.cart[i].getPrice();
    if(customer.getCash() >= sumPrice) {
        customer.reduceCash(sumPrice);
        for(int i = 0; i < customer.cart.size(); i++)
            customer.purchaseHistory.append(customer.cart[i]);

        QSqlDatabase db5 = QSqlDatabase::database("bionic");
        QSqlQuery query(db5);
        QSqlQuery query2(db5);
        QSqlQuery query3(db5);
        QSqlQuery query4(db5);
        QSqlQuery query5(db5);
        QSqlQuery query6(db5);
        query.prepare("SELECT customer_id FROM customers WHERE login = :login");
        query.bindValue(":login", customer.getLogin());
        query.exec();
        query.next();
        int customer_id = query.value(0).toInt();

        query6.prepare("UPDATE customers SET cash = :cash WHERE login = :login");
        query6.bindValue(":cash", customer.getCash());
        query6.bindValue(":login", customer.getLogin());
        query6.exec();

        for(int j = 0; j < customer.cart.size(); j++) {
            query2.prepare("INSERT INTO drinks (type_id, customer_id, name) VALUES (2, ?, ?)");
            query2.addBindValue(customer_id);
            query2.addBindValue(customer.cart[j].getName());
            query2.exec();
            QVector<int> basicingredient_id;
            for(int i = 0; i < customer.cart[j].composition.size(); i++) {
                query3.prepare("SELECT basicIngredient_id FROM basicingredients WHERE name = :name AND kind = :kind");
                query3.bindValue(":name", customer.cart[j].composition[i].getName());
                query3.bindValue(":kind", customer.cart[j].composition[i].getKind());
                query3.exec();
                query3.next();
                basicingredient_id.append(query3.value(0).toInt());
                query3.seek(-1);
            }
            query5.prepare("SELECT drink_id FROM drinks WHERE type_id = 2 AND customer_id = :customer_id AND name = :name");
            query5.bindValue(":customer_id", customer_id);
            query5.bindValue(":name", customer.cart[j].getName());
            query5.exec();
            query5.next();
            int drink_id = query5.value(0).toInt();
            query5.seek(-1);
            for(int i = 0; i < customer.cart[j].composition.size(); i++) {
                query4.prepare("INSERT INTO drinkingredients (drink_id, basicIngredient_id, volume) "
                               "VALUES (?, ?, ?)");
                query4.addBindValue(drink_id);
                query4.addBindValue(basicingredient_id.takeFirst());
                query4.addBindValue(customer.cart[j].composition[i].getVolume());
                query4.exec();
            }
        }

        customer.cart.clear();
        previousPages.clear();
        ui->stackedWidget->setCurrentIndex(9);
        QTimer::singleShot(4500, this, SLOT(logOut()));
    }
}




