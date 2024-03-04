#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include "Exceptions.h"
#include "Sorting.h"


using namespace std;

class Base
{
protected:
	string name;
	float money;
public:
	Base() { money = 0.0; }
	Base(string Name) { name = Name; money = 0.0; }

	string get_name() { return name; }
	void set_name(string Name) { name = Name; }
	float get_money() { return money; }
	void set_money(float Cash) { money = Cash; }
};

class Product : public Base
{
protected:
	int volume;
	int number;
public:
	Product() { volume = 0; number = 0; }
	Product(string Name) : Base(Name) { volume = 0; number = 0; }

	int get_volume() { return volume; }
	void set_volume(int Vol) { volume = Vol; }
	void plus_volume(int Vol) { volume += Vol; }
	int get_number() { return number; }
	void set_number(int Num) { number = Num; }

	Product operator=(Product obj);
	friend ostream& operator<<(ostream &out, Product &obj);
};

class Drink : public Base
{
protected:
	int number;
	vector<int> compose;
public:
	vector<Product> composition;
	Drink() { number = 0; }
	Drink(string Name) : Base(Name) { number = 0; }

	int get_number() { return number; }
	void set_number(int Num) { number = Num; }
	vector<int> get_compose() { return compose; }
	void set_compose_elem(int Elem) { compose.push_back(Elem); }
	void make_composition(vector<Product>& all_products);
	void make_compose(vector<Product>& all_products);
	void my_price_recalculation();
	void make_history_drink(vector<Drink>& my_drinks, vector<Drink>& all_drinks, vector<Product>& all_products);
	
	Drink operator=(Drink obj);
	friend ostream& operator<<(ostream &out, Drink &obj);
};

class Basic_User : public Base
{
protected:
	string surname;
	string password;
	int birth_year;
	ifstream products_file;
	ifstream drinks_file;
	ofstream user_file_new;
	fstream user_file;
	vector<Product> all_products;
	vector<Drink> all_drinks;
public:
	Basic_User() {}

	void registration(vector<string>& language);
	void products_from_file(vector<string>& language);
	void drinks_from_file(vector<string>& language);
};

class User : public Basic_User
{
protected:
	vector<Drink> purchase_history;
	vector<Drink> my_drinks;
public:
	User() {}
	
	void authorization(vector<string>& language);
	void user_into_file(vector<string>& language);
	void user_from_file(vector<string>& language);
	void show_profile(vector<string>& language);
	void settings(vector<string>& language);
	void show_drinks(vector<Drink>& drinks, vector<string>& language, int Number = -1);
	void print_head(vector<string>& language);
	void show_my_drinks(vector<string>& language, bool make_order = false);
	void show_purchase_history(vector<string>& language, bool make_order = false);
	void show_all_drinks(vector<string>& language, bool make_order = false);
	void choose_vector(vector<string>& language);
	bool delete_my_drinks(vector<Drink>& drinks, vector<string>& language, bool is_show = false);
	void create_my_drink(vector<string>& language);
	int choose_product(int choise1, Drink new_drink, vector<string>& language, bool is_all = false);
	void print_drink(Drink &new_drink, vector<string>& language);
	void print_engredients(vector<Product>& engredients, vector<string>& language);
};