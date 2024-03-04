#include "Classes.h"

void Basic_User::registration(vector<string>& language)
{
	string file_name;
	bool match = false;
	do
	{
		name = string_exception(language[9]);
		surname = string_exception(language[10]);
		file_name = "..\\Users\\";
		file_name += name;
		file_name += '_';
		file_name += surname;
		file_name += ".txt";
		user_file.open(file_name, ios::in | ios::out);
		if (user_file)//проверка, если есть файл с таким именем
		{
			cout << language[125] << endl;
			_getch();
			system("CLS");
			user_file.close();
		}
		else match = true;
	} while (!match);
	password = string_exception(language[11], true);
	birth_year = birth_exception(language[12]);
	money = 100.00;
	user_file_new.open(file_name, ios::out);
	if (!user_file_new)
	{
		cout << language[13] << endl;
		_getch();
		exit(EXIT_SUCCESS);
	}

	user_file_new << password << ' ' << birth_year << ' ' << money << '\n';
	user_file_new << "*|\n";
	user_file_new << "**|\n";
	user_file_new.close();

	products_from_file(language);
	drinks_from_file(language);
}

void User::authorization(vector<string>& language)
{
	do
	{
		name = string_exception(language[9]);
		surname = string_exception(language[10]);
		
		string file_name = "..\\Users\\";
		file_name += name;
		file_name += '_';
		file_name += surname;
		file_name += ".txt";
		user_file.open(file_name, ios::in | ios::out);
		if (!user_file)//если такой пользователь не найден
		{
			cout << language[14] << endl;
			_getch();
		}
	} while (!user_file);
	string pass;
	user_file >> password;
	do
	{
		pass = string_exception(language[11], true);
		if (password != pass) cout << language[15] << endl;
	} while (password != pass);
	user_from_file(language);
}

void User::user_into_file(vector<string>& language)
{
	string file_name = "..\\Users\\";
	file_name += name;
	file_name += '_';
	file_name += surname;
	file_name += ".txt";
	user_file.open(file_name, ios::in | ios::out | ios::trunc);
	if (!user_file)
	{
		cout << language[16] << endl;
		_getch();
		exit(EXIT_SUCCESS);
	}
	
	user_file << password << ' ' << birth_year << ' ' << money << '\n';

	for (int i = 0; i < my_drinks.size(); i++)
	{
		user_file << my_drinks[i].get_name() << '|';
		vector<int> compose_copy(my_drinks[i].get_compose());
		for (int j = 0; j < compose_copy.size(); j++)//запись состава напитка
			user_file << compose_copy[j] << '|';
		user_file << "#|";
		for (int j = 0; j < my_drinks[i].composition.size(); j++)//запись объема каждого ингредиента
		{
			user_file << my_drinks[i].composition[j].get_volume();
			user_file << "|";
		}
		user_file << "\n";
	}

	user_file << "*|\n";

	for (int i = 0; i < purchase_history.size(); i++)//запись истории заказов
		user_file << purchase_history[i].get_name() << "|\n";
	
	user_file << "**|\n";
	user_file.close();
}

void User::user_from_file(vector<string>& language)
{
	products_from_file(language);
	drinks_from_file(language);

	user_file >> birth_year;
	user_file >> money;
	string str;
	getline(user_file, str, '\n');
	int Number, Vol;
	int i = 0;
	while (1)
	{
		getline(user_file, str, '|');//считывание названия напитка пользователя
		if (str == "*") break;
		my_drinks.push_back(Drink(str));
		getline(user_file, str, '|');//считывание состава напитка
		while (str != "#")
		{
			Number = atoi(str.c_str());
			my_drinks[i].set_compose_elem(Number);
			getline(user_file, str, '|');
		}
		my_drinks[i].make_composition(all_products);
		for (int j = 0; j < my_drinks[i].composition.size(); j++)//считывание объема каждого ингредиента
		{
			getline(user_file, str, '|');
			Vol = atoi(str.c_str());
			my_drinks[i].composition[j].set_volume(Vol);
		}
		getline(user_file, str, '\n');
		my_drinks[i].my_price_recalculation();
		i++;
	}
	i = 0;
	getline(user_file, str, '\n');
	while (1)//считывание истории заказов
	{
		getline(user_file, str, '|');
		if (str == "**") break;
		purchase_history.push_back(Drink(str));

		purchase_history[i].make_history_drink(my_drinks, all_drinks, all_products);
		getline(user_file, str, '\n');
		i++;
	}
	user_file.close();
}

void Basic_User::products_from_file(vector<string>& language)
{
	products_file.open("..\\Stuff\\Products.txt", ios::in);
	if (!products_file)
	{
		cout << language[17] << endl;
		_getch();
		exit(EXIT_SUCCESS);
	}
	string Name, str;
	float Price;
	int i = 0;
	while (!products_file.eof())
	{
		getline(products_file, Name, '|');//считывание названия продукта
		all_products.push_back(Product(Name));
		getline(products_file, str, '\n');//считывание цены
		Price = atof(str.c_str());
		all_products[i].set_money(Price);
		i++;
	}

	products_file.close();
}

void Basic_User::drinks_from_file(vector<string>& language)
{
	drinks_file.open("..\\Stuff\\Drinks.txt", ios::in);
	if (!drinks_file)
	{
		cout << language[18] << endl;
		_getch();
		exit(EXIT_SUCCESS);
	}
	string str;
	int Number, Vol;
	float Price;
	int i = 0;
	while (!drinks_file.eof())
	{
		getline(drinks_file, str, '|');//считывание названия напитка
		all_drinks.push_back(Drink(str));
		getline(drinks_file, str, '|');//считывание цены
		Price = atof(str.c_str());
		all_drinks[i].set_money(Price);
		getline(drinks_file, str, '|');
		while (str != "#")//считывание состава напитка
		{
			Number = atoi(str.c_str());
			all_drinks[i].set_compose_elem(Number);
			getline(drinks_file, str, '|');
		}
		all_drinks[i].make_composition(all_products);
		for (int j = 0; j < all_drinks[i].composition.size(); j++)//считывание объема каждого ингредиента
		{
			getline(drinks_file, str, '|');
			Vol = atoi(str.c_str());
			all_drinks[i].composition[j].set_volume(Vol);
		}
		getline(drinks_file, str, '\n');
		i++;
	}

	drinks_file.close();
}

void User::show_profile(vector<string>& language)
{
	int choise;
	int text[] = {19, 20, 21, 22, 23};
	do
	{
		cout << setw(18) << right << language[24] << ':' << name << endl;
		cout << setw(18) << right << language[25] << ':' << surname << endl;
		cout << setw(18) << right << language[26] << ':' << birth_year << endl;
		cout << setw(18) << right << language[27] << ':' << fixed << setprecision(2) << money << ' ' << language[121] << endl;
		cout << endl << endl;
		switch_exception(5, text, choise, language);
		switch (choise)
		{
		case 1:
		{
			settings(language);
			break;
		}
		case 2:
		{
			show_all_drinks(language);
			break;
		}
		case 3:
		{
			show_my_drinks(language);
			break;
		}
		case 4:
		{
			show_purchase_history(language);
			break;
		}
		case 5: {}
		}
	} while (choise != 5);
}

void User::settings(vector<string>& language)
{
	int choise;
	int text1[] = {28, 29, 30, 31, 32, 33, 34};
	do
	{
		cout << language[40] << endl << endl;
		switch_exception(7, text1, choise, language);
		switch (choise)
		{
		case 1://изменение имени
		{
			name = string_exception(language[35]);
			break;
		}
		case 2://изменение фамилии
		{
			surname = string_exception(language[36]);
			break;
		}
		case 3://изменение даты рождения
		{
			birth_year = birth_exception(language[37]);
			break;
		}
		case 4://изменение пароля
		{
			string pass;
			do//сначала ввести существующий
			{
				pass = string_exception(language[38], true);
			} while (password != pass);
			password = string_exception(language[39], true);
			break;
		}
		case 5://удаление всей истории заказов
		{
			if (purchase_history.empty())
			{
				cout << language[41] << endl;
				_getch();
				break;
			}
			int choise2;
			system("CLS");
			cout << language[42] << endl;
			int text3[] = {43, 44};
			switch_exception(2, text3, choise2, language);
			switch (choise2)//подтверждение удаления
			{
			case 1://удалить
			{
				purchase_history.clear();
				cout << language[45] << endl;
				_getch();
				system("CLS");
				break;
			}
			case 2: {}//не удалять
			}
			break;
		}
		case 6://удалить напитки пользователя
		{
			if (my_drinks.empty())
			{
				cout << language[46] << endl;
				_getch();
				break;
			}
			system("CLS");
			delete_my_drinks(my_drinks, language);
			break;
		}
		case 7: {}
		}
	} while (choise != 7);
}

bool User::delete_my_drinks(vector<Drink>& drinks, vector<string>& language, bool is_show)
{
	int choise1, choise2, choise3;
	int text1[] = {47, 48};
	int text2[] = {43, 44};
	int text3[] = {49, 50};
	switch_exception(2, text1, choise1, language);
	switch(choise1)
	{
	case 1://удалить все
	{
		cout << language[51] << endl;
		switch_exception(2, text2, choise2, language);
		switch (choise2)//подтверждение
		{
		case 1://удалить
		{
			my_drinks.clear();
			cout << language[52] << endl;
			_getch();
			system("CLS");
			return 1;
		}
		case 2: { return 0; }//не удалять
		}
		break;
	}
	case 2://удалить определенный
	{
		switch_exception(2, text3, choise3, language);
		string drink_name, str;
		int Number = -1;
		bool match = false;
		bool error;
		switch(choise3)
		{
		case 1://по названию
		{
			do
			{
				system("CLS");
				show_drinks(drinks, language);
				cout << endl << endl;
				cout << language[53];
				getline(cin, drink_name);
				for (int i = 0; i < my_drinks.size(); i++)
				{
					if (my_drinks[i].get_name() == drink_name)
					{
						match = true;
						Number = i;
						break;
					}
				}
			} while (!match);
			break;
		}
		case 2://по номеру
		{
			do
			{
				system("CLS");
				show_drinks(drinks, language);
				cout << endl << endl;
				string str = language[54];
				error = int_exception(str, Number, drinks.size());
				if(!error)
				{
					match = true;
					if(is_show) Number = drinks[Number].get_number();//для сортировки
				}
			} while (!match);
			break;
		}
		}
		system("CLS");
		show_drinks(drinks, language, Number);

		cout << language[55] << endl;
		switch_exception(2, text2, choise2, language);
		switch (choise2)//подтверждение
		{
		case 1://удалить
		{
			vector<Drink>::iterator p = my_drinks.begin();
			p += Number;
			my_drinks.erase(p);

			cout << language[56] << endl;
			_getch();
			system("CLS");
			return 1;
		}
		case 2: { return 0; }//не удалять
		}
		break;
	}
	}
}

void User::show_my_drinks(vector<string>& language, bool make_order)
{
	int text1[] = {57, 58};
	int choise1;
	if (my_drinks.empty())
	{
		cout << language[46] << endl;
		switch_exception(2, text1, choise1, language);
		switch (choise1)
		{
		case 1://создать новый напиток
		{
			system("CLS");
			create_my_drink(language);
			return;
		}
		case 2://назад
		{
			system("CLS");
			return;
		}
		}
	}
	vector<Drink> drinks(my_drinks);
	for (int i = 0; i < drinks.size(); i++)//начальные места сохраняются
		drinks[i].set_number(i);
	int choise;
	int text[] = {59, 60, 61, 62, 63};
	do
	{
		if (!make_order)//если вызов не из заказа напитка
		{
			system("CLS");
			show_drinks(drinks, language);
			switch_exception(5, text, choise, language);
		}
		else choise = 4;
		switch (choise)
		{
		case 1://сортировка
		{
			sorting(drinks, language);
			break;
		}
		case 2://удаление
		{
			system("CLS");
			bool return_value = delete_my_drinks(drinks, language, true);
			if (return_value) return;
			else break;
		}
		case 3://создать новый
		{
			create_my_drink(language);
			return;
		}
		case 4://заказать
		{
			bool match = false;
			bool error;
			int Number;
			do
			{
				system("CLS");
				show_drinks(drinks, language);
				cout << endl << endl;
				string str = language[64];
				error = int_exception(str, Number, drinks.size());//ввод номера для заказа
				if (!error)
				{
					match = true;
					Number = drinks[Number].get_number();
				}
			} while (!match);

			int choise2;
			int text3[] = {123, 124};
			system("CLS");
			print_drink(my_drinks[Number], language);
			cout << endl << endl;
			cout << language[122] << endl;
			switch_exception(2, text3, choise2, language);
			switch (choise2)//подтвердить заказ
			{
			case 1://заказать
			{
				if (money < my_drinks[Number].get_money())
				{
					cout << language[65] << endl;
					_getch();
					system("CLS");
					return;
				}
				else money -= my_drinks[Number].get_money();
				cout << my_drinks[Number].get_name() << language[66] << endl;
				cout << language[67] << endl;
				_getch();
				system("CLS");
				vector<Drink>::iterator p = purchase_history.begin();
				purchase_history.insert(p, my_drinks[Number]);
				return;
			}
			case 2://назад
			{
				system("CLS");
				break;
			}
			}
		}
		case 5: {}//назад
		}
	} while (choise != 5);
}

void User::show_drinks(vector<Drink>& drinks, vector<string>& language, int Number)
{
	system("CLS");
	print_head(language);//шапка таблицы

	if (Number >= 0)//вывод определенного напитка
	{
		_setmode(_fileno(stdout), _O_U16TEXT);
		wcout << setw(10) << right << L'\u2560' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u256C' << setw(30) << L'\u2550';
		wcout << L'\u256C' << setw(30) << L'\u2550' << L'\u256C' << setw(10) << L'\u2550' << L'\u256C' << setw(10) << L'\u2550' << L'\u2563' << setfill(L' ') << endl;
		wcout << setw(10) << right << L'\u2551' << setw(10) << left << Number << L'\u2551';
		_setmode(_fileno(stdout), _O_TEXT);
		cout << drinks[Number];
		
	}
	else//вывод всего списка
	{
		for (int i = 0; i < drinks.size(); i++)
		{
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << right << L'\u2560' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u256C' << setw(30) << L'\u2550';
			wcout << L'\u256C' << setw(30) << L'\u2550' << L'\u256C' << setw(10) << L'\u2550' << L'\u256C' << setw(10) << L'\u2550' << L'\u2563' << setfill(L' ') << endl;
			wcout << setw(10) << right << L'\u2551' << setw(10) << left << i << L'\u2551';
			_setmode(_fileno(stdout), _O_TEXT);
			cout << drinks[i];
		}
	}
	
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << setw(10) << right << L'\u255A' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u2569' << setw(30) << L'\u2550' << L'\u2569';
	wcout << setw(30) << L'\u2550' << L'\u2569' << setw(10) << L'\u2550' << L'\u2569' << setw(10) << L'\u2550' << L'\u255D' << setfill(L' ') << endl;
	_setmode(_fileno(stdout), _O_TEXT);
}

void User::print_head(vector<string>& language)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	wcout << setw(10) << right << L'\u2554' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u2566' << setw(30) << L'\u2550' << L'\u2566';
	wcout << setw(30) << L'\u2550' << L'\u2566' << setw(10) << L'\u2550' << L'\u2566' << setw(10) << L'\u2550' << L'\u2557' << setfill(L' ') << endl;

	wcout << setw(10) << right << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(10) << left << language[68];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(30) << left << language[69];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(30) << left << language[70];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(10) << left << language[71];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(10) << left << language[72];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551' << endl;
	_setmode(_fileno(stdout), _O_TEXT);
}

void User::show_purchase_history(vector<string>& language, bool make_order)
{
	if (purchase_history.empty())
	{
		cout << language[73] << endl;
		_getch();
		return;
	}
	vector<Drink> drinks(purchase_history);//сохранение начальных позиций
	for (int i = 0; i < drinks.size(); i++)
		drinks[i].set_number(i);
	int choise1, choise2;
	int text1[] = {74, 75, 76, 77};
	int text2[] = {43, 44};
	do
	{
		if (!make_order)//если вызов не из заказа напитков
		{
			system("CLS");
			show_drinks(drinks, language);
			switch_exception(4, text1, choise1, language);
		}
		else choise1 = 3;
		switch (choise1)
		{
		case 1://сортировка
		{
			sorting(drinks, language);
			break;
		}
		case 2://удаление истории
		{
			cout << endl;
			cout << language[42] << endl;
			switch_exception(2, text2, choise2, language);
			switch (choise2)//подтверждение
			{
			case 1:
			{
				purchase_history.clear();
				cout << language[45] << endl;
				_getch();
				system("CLS");
				return;
			}
			case 2: {}
			}
			break;
		}
		case 3://заказ
		{
			bool match = false;
			bool error;
			int Number;
			do
			{
				system("CLS");
				show_drinks(drinks, language);
				cout << endl << endl;
				string str = language[64];
				error = int_exception(str, Number, drinks.size());//ввод номера для заказа
				if (!error)
				{
					match = true;
					Number = drinks[Number].get_number();
				}
			} while (!match);

			int choise3;
			int text3[] = { 123, 124 };
			system("CLS");
			print_drink(purchase_history[Number], language);
			cout << endl << endl;
			cout << language[122] << endl;
			switch_exception(2, text3, choise3, language);
			switch (choise3)//подтверждение
			{
			case 1://заказать
			{
				if (money < purchase_history[Number].get_money())
				{
					cout << language[65] << endl;
					_getch();
					system("CLS");
					return;
				}
				else money -= purchase_history[Number].get_money();
				cout << purchase_history[Number].get_name() << language[66] << endl;
				cout << language[67] << endl;
				_getch();
				system("CLS");
				vector<Drink>::iterator p = purchase_history.begin();
				purchase_history.insert(p, purchase_history[Number]);
				return;
			}
			case 2://назад
			{
				system("CLS");
				break;
			}
			}
		}
		case 4: {}//назад
		}
	} while (choise1 != 4);
}

void User::choose_vector(vector<string>& language)
{
	//заказ напитков из главного меню
	//выбор вектора
	system("CLS");
	int choise;
	int text[] = {78, 79, 80, 77};
	cout << language[81] << endl;
	switch_exception(4, text, choise, language);
	switch (choise)
	{
	case 1://напитки пользователя
	{
		show_my_drinks(language, true);
		break;
	}
	case 2://история заказов
	{
		show_purchase_history(language, true);
		break;
	}
	case 3://стандартные напитки
	{
		show_all_drinks(language, true);
		break;
	}
	case 4: { return; }
	}
}

void User::show_all_drinks(vector<string>& language, bool make_order)
{
	vector<Drink> drinks(all_drinks);//сохранение наального положения в векторе
	for (int i = 0; i < drinks.size(); i++)
		drinks[i].set_number(i);
	int choise;
	int text[] = {82, 83, 84};
	do
	{
		if (!make_order)//если вызов не из заказа напитков
		{
			system("CLS");
			show_drinks(drinks, language);
			switch_exception(3, text, choise, language);
		}
		else choise = 2;
		switch (choise)
		{
		case 1://сортировка
		{
			sorting(drinks, language);
			break;
		}
		case 2://заказ
		{
			bool match = false;
			bool error;
			int Number;
			do
			{
				system("CLS");
				show_drinks(drinks, language);
				cout << endl << endl;
				string str = language[64];
				error = int_exception(str, Number, drinks.size());//ввод номера для заказа
				if (!error)
				{
					match = true;
					Number = drinks[Number].get_number();
				}
			} while (!match);

			int choise3;
			int text3[] = { 123, 124 };
			system("CLS");
			print_drink(all_drinks[Number], language);
			cout << endl << endl;
			cout << language[122] << endl;
			switch_exception(2, text3, choise3, language);
			switch (choise3)//подтверждение
			{
			case 1://заказать
			{
				if (money < all_drinks[Number].get_money())
				{
					cout << language[65] << endl;
					_getch();
					system("CLS");
					return;
				}
				else money -= all_drinks[Number].get_money();
				cout << all_drinks[Number].get_name() << language[66] << endl;
				cout << language[67] << endl;
				_getch();
				system("CLS");
				vector<Drink>::iterator p = purchase_history.begin();
				purchase_history.insert(p, all_drinks[Number]);
				return;
			}
			case 2://назад
			{
				system("CLS");
				break;
			}
			}
		}
		case 3: {}//назад
		}
	} while (choise != 3);
}

void User::create_my_drink(vector<string>& language)
{
	Drink new_drink;
	int choise1;
	int text1[] = { 85, 86, 87, 88, 89, 90 };
	do
	{
		system("CLS");
		new_drink.my_price_recalculation();
		print_drink(new_drink, language);//вывод напиитка
		switch_exception(6, text1, choise1, language, 30);
		switch (choise1)
		{
		case 1://ввод названия
		{
			system("CLS");
			cout << language[91];
			string str;
			getline(cin, str, '\n');
			new_drink.set_name(str);
			break;
		}
		case 2://добавить ингредиент
		{
			int layers = 0;
			for (int i = 0; i < new_drink.composition.size(); i++)
				layers += new_drink.composition[i].get_volume();
			if (layers == 17)//подсчет слоев
			{//если стакан полон - возврат
				cout << language[92] << endl;
				_getch();
				break;
			}
			int Number;
			Number = choose_product(0, new_drink, language, true);//выбор ингредиента, возвращает номер
			bool match = false;
			bool error;
			int Vol;
			do//ввод объема ингредиента
			{
				string str = language[93];
				error = int_exception(str, Vol, 17);
				if (!error) match = true;
				if ((Vol + layers) > 17)//проверка, если стакан будет переполнен
				{
					match = false;
					cout << language[94] << endl;
					_getch();
					system("CLS");
				}
			} while (!match);
			match = false;
			for (int i = 0; i < new_drink.composition.size(); i++)//если такой уже есть, то +к его объему
			{
				if (new_drink.composition[i].get_name() == all_products[Number].get_name())
				{
					new_drink.composition[i].plus_volume(Vol);
					match = true;
					break;
				}
			}
			if (!match)//если нету - занесение в начало
			{
				vector<Product>::iterator p = new_drink.composition.begin();
				new_drink.composition.insert(p, all_products[Number]);
				new_drink.composition[0].set_name(all_products[Number].get_name());
				new_drink.composition[0].set_money(all_products[Number].get_money());
				new_drink.composition[0].set_volume(Vol);
			}
			break;
		}
		case 3://удаление ингредиента
		{
			if (new_drink.composition.size() == 0)
			{
				cout << language[95] << endl;
				_getch();
				system("CLS");
				break;
			}
			int Number;
			Number = choose_product(1, new_drink, language);
			vector<Product>::iterator p = new_drink.composition.begin();
			p += Number;
			new_drink.composition.erase(p);
			cout << language[96] << endl;
			_getch();
			system("CLS");
			break;
		}
		case 4://изменение объема ингредиента
		{
			if (new_drink.composition.size() == 0)
			{
				cout << language[95] << endl;
				_getch();
				system("CLS");
				break;
			}
			int Number;
			Number = choose_product(2, new_drink, language);//определение ингредиента, возвращает его номер
			bool match = false;
			bool error;
			int Vol;
			int layers;
			do
			{
				layers = 0;
				system("CLS");
				string str = language[97];
				error = int_exception(str, Vol, 17);//ввести новый объем
				if (!error) match = true;
				for (int i = 0; i < new_drink.composition.size(); i++)
				{
					if (i != Number)
						layers += new_drink.composition[i].get_volume();
				}
				layers += Vol;
				if (layers > 17)//проверка на переполнение
				{
					match = false;
					cout << language[94] << endl;
					_getch();
					system("CLS");
				}
			} while (!match);
			new_drink.composition[Number].set_volume(Vol);
			break;
		}
		case 5:
		{ break; }//заказать
		case 6://выход
		{
			int text4[] = {98, 99};
			int choise3;
			system("CLS");
			cout << language[100] << endl;
			switch_exception(2, text4, choise3, language);
			switch (choise3)
			{
			case 1://сохранить напиток
			{
				new_drink.make_compose(all_products);
				new_drink.my_price_recalculation();
				my_drinks.push_back(new_drink);
				system("CLS");
				return;
			}
			case 2://не сохранять
			{
				system("CLS");
				return;
			}
			}
		}
		}
		if (choise1 == 5)//перед заказом, если нету названия - назад
		{
			if (new_drink.get_name() == "")
			{
				system("CLS");
				cout << language[101] << endl;
				_getch();
				choise1 = 0;
			}
			if (new_drink.composition.size() == 0)//если стакан пуст - назад
			{
				system("CLS");
				cout << language[95] << endl;
				_getch();
				choise1 = 0;
			}
		}
	} while (choise1 != 5);

	new_drink.make_compose(all_products);
	new_drink.my_price_recalculation();//пересчет цены
	my_drinks.push_back(new_drink);
	if (money >= new_drink.get_money())//если достаточно на балансе
	{
		money -= new_drink.get_money();
		vector<Drink>::iterator p = purchase_history.begin();
		purchase_history.insert(p, new_drink);
		system("CLS");
		cout << new_drink.get_name() << language[66] << endl;
		cout << language[67] << endl;
		_getch();
		system("CLS");
	}
	else
	{
		system("CLS");
		cout << language[65] << endl;
		_getch();
		system("CLS");
	}
}

int User::choose_product(int choise1, Drink new_drink, vector<string>& language, bool is_all)
{
	vector<Product> products;
	if (is_all)
	{
		vector<Product>::iterator start = all_products.begin();
		vector<Product>::iterator end = all_products.end();
		products.assign(start, end);
	}
	else
	{
		vector<Product>::iterator start = new_drink.composition.begin();
		vector<Product>::iterator end = new_drink.composition.end();
		products.assign(start, end);
	}
	for (int i = 0; i < products.size(); i++)//сохранение начальных позиций продуктов
		products[i].set_number(i);
	int text1[] = {102, 103};
	int text2[] = {104, 105, 106};
	int text3[] = {107, 108};
	int choise2, choise3, Number;
	do
	{
		system("CLS");
		print_engredients(products, language);
		cout << endl << endl;
		switch_exception(2, text1, choise2, language);
		switch (choise2)
		{
		case 1://сортировка
		{
			system("CLS");
			sorting(products, language);
			break;
		}
		case 2://выбор
		{
			cout << language[text2[choise1]] << endl;
			switch_exception(2, text3, choise3, language);
			switch (choise3)
			{
			case 1://по номеру
			{
				bool match = false;
				bool error;
				do
				{
					system("CLS");
					print_engredients(products, language);
					cout << endl << endl;
					string str = language[109];
					error = int_exception(str, Number, products.size());
					if (!error)
						match = true;
				} while (!match);
				break;
			}
			case 2://по названию
			{
				bool match = false;
				string Name;
				do
				{
					system("CLS");
					print_engredients(products, language);
					cout << endl << endl;
					cout << language[110];
					getline(cin, Name);
					for (int i = 0; i < products.size(); i++)
					{
						if (products[i].get_name() == Name)
						{
							match = true;
							Number = i;
							break;
						}
					}
					if (!match)
					{
						cout << language[111] << endl;
						_getch();
					}
				} while (!match);
				break;
			}
			}
			break;
		}
		}
	} while (choise2 != 2);
	system("CLS");
	Number = products[Number].get_number();//переопределение номера
	return Number;
}

void User::print_engredients(vector<Product>& engredients, vector<string>& language)
{
	system("CLS");
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << endl;
	wcout << setw(10) << right << L'\u2554' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u2566' << setw(20) << L'\u2550' << L'\u2566' << setw(10) << L'\u2550' << L'\u2557' << setfill(L' ') << endl;
	wcout << setw(10) << right << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(10) << left << language[112];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(20) << left << language[113];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(10) << left << language[114];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551' << endl;
	
	for (int i = 0; i < engredients.size(); i++)
	{
		wcout << setw(10) << right << L'\u2560' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u256C' << setw(20) << L'\u2550' << L'\u256C' << setw(10) << L'\u2550' << L'\u2563' << setfill(L' ') << endl;
		wcout << setw(10) << right << L'\u2551' << setw(10) << left << i << L'\u2551';
		_setmode(_fileno(stdout), _O_TEXT);
		cout << engredients[i];
		_setmode(_fileno(stdout), _O_U16TEXT);
	}

	wcout << setw(10) << right << L'\u255A' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u2569' << setw(20) << L'\u2550' << L'\u2569' << setw(10) << L'\u2550' << L'\u255D' << setfill(L' ') << endl;
	wcout << endl;
	_setmode(_fileno(stdout), _O_TEXT);
}

//█219	L'\u2588'
//
//▓178	L'\u2593'
//
//▒177	L'\u2592'
//
//░176	L'\u2591'
//¤253	L'\u00A4'
//°248	L'\u00B0'
//☼15	L'\u263C'
//╓214	L'\u2553'
//╖183	L'\u2556'
//║186	L'\u2551'
//╚200	L'\u255A'
//╝188	L'\u255D'
//═205	L'\u2550'
//╔201	L'\u2554'
//╦203	L'\u2566'
//╗187	L'\u2557'
//╠204	L'\u2560'
//╣185	L'\u2563'
//╬206	L'\u256C'
//╩202	L'\u2569'
//╟199	L'\u255F'
//╫215	L'\u256B'
//╢182	L'\u2562'
//
//╟     L'\u255F'
//╢     L'\u2562'
//╫     L'\u256B'
//─     L'\u2500'

void User::print_drink(Drink &new_drink, vector<string>& language)
{
	char fill_symbols[] = {
	(char)219,
	(char)178,
	(char)177,
	(char)176,
	(char)253,
	(char)248
	};

	_setmode(_fileno(stdout), _O_U16TEXT);
	system("CLS");
	int blank_layers = 17;
	for (int i = 0; i < new_drink.composition.size(); i++)//количество пустых мест в стакане
	{
		blank_layers -= new_drink.composition[i].get_volume();
	}
	//вывод названия и цены
	wcout << endl;
	wcout << setw(20) << right << L'\u2554' << setfill(L'\u2550') << setw(20) << L'\u2550' << L'\u2566' << setfill(L'\u2550') << setw(20) << L'\u2550' << L'\u2557' << setfill(L' ') << endl;
	wcout << setw(20) << right << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(20) << left << language[113];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(20) << left << new_drink.get_name();
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551' << endl;
	wcout << setw(20) << right << L'\u2560' << setfill(L'\u2550') << setw(20) << L'\u2550' << L'\u256C' << setw(20) << L'\u2550' << L'\u2563' << endl;
	wcout << setfill(L' ') << setw(20) << right << L'\u2551' << setfill(L' ');
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setfill(' ') << setw(20) << left << language[114];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(20) << left << fixed << setprecision(2) << new_drink.get_money();
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551' << endl;
	wcout << setw(20) << right << L'\u255A' << setfill(L'\u2550') << setw(20) << L'\u2550' << L'\u2569' << setw(20) << L'\u2550' << setfill(L' ') << L'\u255D' << endl;
	wcout << endl << endl;
	//вывод стакана
	wcout << setw(30) << right << L'\u2553' << setw(21) << L' ' << L'\u2556' << endl;
	for (int i = 0; i < blank_layers; i++)
	{
		wcout << setw(30) << right << L'\u2551' << setw(21) << L' ' << L'\u2551' << endl;
	}
	for (int i = 0; i < new_drink.composition.size(); i++)
	{
		char symbol = fill_symbols[rand() % 6];
		for (int j = 0; j < new_drink.composition[i].get_volume(); j++)
		{
			wcout << setw(30) << right << L'\u2551';
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleOutputCP(866);
			cout << setfill(symbol) << setw(21) << symbol;
			SetConsoleOutputCP(1251);
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setfill(L' ') << L'\u2551';
			if (j == (new_drink.composition[i].get_volume() - 1))
			{
				_setmode(_fileno(stdout), _O_TEXT);
				cout << new_drink.composition[i].get_name() << endl;
				_setmode(_fileno(stdout), _O_U16TEXT);
			}
			else wcout << endl;
		}
	}
	wcout << setw(30) << right << L'\u255A' << setfill(L'\u2550') << setw(21) << L'\u2550' << setfill(L' ') << L'\u255D' << endl;
	//вывод ингредиентов
	wcout << endl << endl;
	wcout << setw(20) << right << L'\u2554' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u2566' << setw(20) << L'\u2550' << L'\u2566' << setw(10) << L'\u2550' << L'\u2557' << setfill(L' ') << endl;
	wcout << setw(20) << right << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setfill(' ') << setw(10) << left << language[112];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setfill(' ') << setw(20) << left << language[115];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setfill(' ') << setw(10) << left << language[116];
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551' << endl;
	for (int i = 0; i < new_drink.composition.size(); i++)
	{
		wcout << setw(20) << right << L'\u2560' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u256C' << setw(20) << L'\u2550' << L'\u256C' << setw(10) << L'\u2550' << setfill(L' ') << L'\u2563' << endl;
		wcout << setw(20) << right << L'\u2551' << setw(10) << left << i << L'\u2551';
		_setmode(_fileno(stdout), _O_TEXT);
		cout << setfill(' ') << setw(20) << left << new_drink.composition[i].get_name();
		_setmode(_fileno(stdout), _O_U16TEXT);
		wcout << L'\u2551' << setw(10) << left << new_drink.composition[i].get_volume() << L'\u2551' << endl;
	}
	if (new_drink.composition.size() == 0)
	{
		wcout << setw(20) << right << L'\u2560' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u256C' << setw(20) << L'\u2550' << L'\u256C' << setw(10) << L'\u2550' << setfill(L' ') << L'\u2563' << endl;
		wcout << setw(20) << right << L'\u2551' << setfill(L' ') << setw(10) << L' ' << L'\u2551' << setw(20) << L' ' << L'\u2551' << setw(10) << L' ' << L'\u2551' << endl;
	}
	wcout << setw(20) << right << L'\u255A' << setfill(L'\u2550') << setw(10) << L'\u2550' << L'\u2569' << setw(20) << L'\u2550' << L'\u2569' << setw(10) << L'\u2550' << L'\u255D' << setfill(L' ') << endl;
	wcout << endl << endl;

	_setmode(_fileno(stdout), _O_TEXT);
}