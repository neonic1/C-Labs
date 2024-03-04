#include "exceptions.h"

const QString messages[] = {
/*0*/"String is too short.",
/*1*/"String is too long.",
/*2*/"Numbers are not allowed.",
/*3*/"Only letters are allowed.",
/*4*/"All fields must be filled.",
/*5*/"Letters are not allowed.",
/*6*/"Entered number is too short",
/*7*/"Entered number is too long.",
/*8*/"Entered number is incorrect.",
/*9*/"No blank spaces are allowed."
};

QString stringException(QString enteredString, bool isLogin) {
    try {
        if(!enteredString.size()) throw MyException(messages[4]);
        if(enteredString.size() < 2) throw MyException(messages[0]);
        if(enteredString.size() > 20) throw MyException(messages[1]);
        for(int i = 0; i < enteredString.size(); i++) {
            if(enteredString[i] == ' ') throw MyException(messages[9]);
            if(!isLogin) {
                if(enteredString[i] >= '0' && enteredString[i] <= '9') throw MyException(messages[2]);
                if((enteredString[i] < 'a' || enteredString[i] > 'z') && (enteredString[i] < 'A' || enteredString[i] > 'Z'))
                    throw MyException(messages[3]);
            }
        }
    }
    catch(MyException ex) {
        return ex.what();
    }
    return "";
}

QString intException(QString enteredString, int bottomLimit, int topLimit) {
    try {
        if(!enteredString.size()) throw MyException(messages[4]);
        for(int i = 0; i < enteredString.size(); i++) {
           if(enteredString[i] < '0' || enteredString[i] > '9') throw MyException(messages[5]);
        }
        if(enteredString.size() < 4) throw MyException(messages[6]);
        if(enteredString.size() > 4) throw MyException(messages[7]);
        int enteredNumber = enteredString.toInt();
        if(enteredNumber < bottomLimit || enteredNumber > topLimit) throw MyException(messages[8]);
    }
    catch(MyException ex) {
        return ex.what();
    }
    return "";
}

QString newNameException(QString enteredString) {
    try {
        if(!enteredString.size()) throw MyException(messages[4]);
        if(enteredString.size() < 4) throw MyException(messages[0]);
        if(enteredString.size() > 20) throw MyException(messages[1]);
    }
    catch(MyException ex) {
        return ex.what();
    }
    return "";
}
