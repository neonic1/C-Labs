#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>
#include <QVector>

QString stringException(QString enteredString, bool isLogin = false);
QString intException(QString enteredString, int bottomLimit, int topLimit);
QString newNameException(QString enteredString);

class MyException
{
    QString exceptionText;
public:
    MyException(QString exceptionText) { this->exceptionText = exceptionText; }

    QString what() { return exceptionText; }
};

#endif // EXCEPTIONS_H
