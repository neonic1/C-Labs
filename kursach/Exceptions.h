#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <vector>

using namespace std;

class Exception
{
protected:
	string message;
public:
	Exception(string str) { message = str; }

	string get_message() { return message; }
};

class MyException : public Exception
{
protected:
	int excep_number;
public:
	MyException(int number, string str) :Exception(str) { excep_number = number; }

	int get_excep_number() { return excep_number; }
};

string string_exception(string text, bool is_pass = false);
void switch_exception(int ms_size, int *text, int &choise, vector<string>& language, int precision = 0);
int birth_exception(string text);
bool int_exception(string text, int &Number, int limit);