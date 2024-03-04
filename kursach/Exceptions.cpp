#include "Exceptions.h"

void switch_exception(int ms_size, int *text, int &choise, vector<string>& language, int precision)
{//ввод для множественного выбора
	string str;
	int number;
	bool error;
	do
	{
		for (int i = 0; i < ms_size; i++)
			cout << setw(precision) << left << language[text[i]] << endl;
		try
		{
			getline(cin, str);
			if (str.size() != 1) throw MyException(1, "Enter one number.");
			if (str[0] < '0' || str[0] > '9') throw MyException(2, "Letters and other characters are not allowed.");
			number = atoi(str.c_str());
			if (number < 1 || number > ms_size) throw MyException(3, "Wrong entered number.");
			system("CLS");
			error = false;
			choise = number;
		}
		catch (MyException ex)
		{
			error = true;
			system("CLS");
			cout << "Error #" << ex.get_excep_number() << endl;
			cout << ex.get_message() << endl;
		}
	} while (error);
}

bool int_exception(string text, int &Number, int limit)
{//ввод цифр
	string str;
	int number;
	bool error;
	cout << text;
	try
	{
		getline(cin, str);
		for(int i = 0; i < str.size(); i++)
			if (str[i] < '0' || str[i] > '9') throw MyException(2, "Letters and other characters are not allowed.");
		number = atoi(str.c_str());
		if (number < 0 || number >= limit) throw MyException(3, "Wrong entered number.");
		system("CLS");
		error = false;
		Number = number;
	}
	catch (MyException ex)
	{
		system("CLS");
		error = true;
		cout << "Error #" << ex.get_excep_number() << endl;
		cout << ex.get_message() << endl;
		_getch();
	}
	return error;
}

string string_exception(string text, bool is_pass)
{//ввод строк
	string str;
	bool error;
	do
	{
		cout << text;
		try 
		{
			getline(cin, str);
			if (str.size() < 4) throw MyException(4, "Entered string is too short.");
			if (str.size() > 20) throw MyException(5, "Entered string is too long.");
			int count = 0;
			char symbol;
			for (int i = 0; i < str.size(); i++)
			{
				if (str[i] == ' ') throw MyException(8, "Blank spaces are not allowed.");
				if (!is_pass)
				{
					if (i)
						if (symbol == str[i]) count++;
					symbol = str[i];
					if (count == 3) throw MyException(6, "Entering of 3 and more same characters together is not allowed.");
					if (symbol >= '0' && symbol <= '9') throw MyException(7, "Numbers are not allowed.");
				}
			}
			if(!is_pass) str[0] = toupper(str[0]);
			system("CLS");
			error = false;
		}
		catch (MyException ex)
		{
			error = true;
			system("CLS");
			cout << "Error #" << ex.get_excep_number() << endl;
			cout << ex.get_message() << endl;
		}
	} while (error);
	return str;
}

int birth_exception(string text)
{//ввод года рождения
	string str;
	int number;
	bool error;
	do
	{
		cout << text;
		try
		{
			getline(cin, str);
			if (str.size() == 0) throw MyException(9, "Enter birth year.");
			for (int i = 0; i < str.size(); i++)
				if (str[i] < '0' || str[i] > '9') throw MyException(10, "Letters are not allowed.");
			number = atoi(str.c_str());
			if (number < 1928 || number > 2000) throw MyException(11, "Entered incorrect birth year.");
			system("CLS");
			error = false;
		}
		catch(MyException ex)
		{
			error = true;
			system("CLS");
			cout << "Error #" << ex.get_excep_number() << endl;
			cout << ex.get_message() << endl;
		}
	} while (error);
	return number;
}