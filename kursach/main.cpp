#include "Classes.h"

ifstream open_language_file();
void enter(int &choise, vector<string>& language);
void main_menu(int &choise, vector<string>& language);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream Language;
	Language = open_language_file();
	system("CLS");
	vector<string> language;
	string str;
	while (!Language.eof())
	{
		getline(Language, str, '\n');
		language.push_back(str);
	}
	Language.close();
	int choise;
	enter(choise, language);
	User client;
	switch (choise)
	{
	case 1:
	{
		client.registration(language);
		break;
	}
	case 2:
	{
		client.authorization(language);
		break;
	}
	case 3:
	{
		cout << language[0] << endl;
		_getch();
		return 0;
	}
	}
	do
	{
		system("CLS");
		main_menu(choise, language);
		switch (choise)
		{
		case 1:
		{
			client.show_profile(language);
			break;
		}
		case 2:
		{
			client.create_my_drink(language);
			break;
		}
		case 3:
		{
			client.choose_vector(language);
			break;
		}
		case 4: {}
		}
	} while (choise != 4);


	client.user_into_file(language);
	cout << language[0] << endl;
	_getch();
	return 0;
}

ifstream open_language_file()
{
	int choise;
	string str;
	bool match = false;
	do
	{
		system("CLS");
		cout << "1. Русский." << endl;
		cout << "2. English." << endl;
		cin >> str;
		if (str.size() == 1)
		{
			if (str[0] == '1' || str[0] == '2') match = true;
			else
			{
				system("CLS");
				cout << "Wrong entered number." << endl;
				_getch();
			}
		}
	} while (!match);
	choise = atoi(str.c_str());
	ifstream file;
	switch (choise)
	{
	case 1:
	{
		file.open("..\\Language\\Russian.txt", ios::in);
		break;
	}
	case 2:
	{
		file.open("..\\Language\\English.txt", ios::in);
		break;
	}
	}
	if (!file)
	{
		cout << "Can't open the language file." << endl;
		_getch();
		exit(EXIT_SUCCESS);
	}
	cin.ignore();
	return file;
}

void enter(int &choise, vector<string>& language)
{
	cout << language[1] << endl << endl;
	int text[] = {2, 3, 4};
	switch_exception(3, text, choise, language);
}

void main_menu(int &choise, vector<string>& language)
{
	int text[] = {5, 6, 7, 8};
	switch_exception(4, text, choise, language);
}