#include "Classes.h"

Drink Drink::operator=(Drink obj)
{
	name = obj.name;
	money = obj.money;
	number = obj.number;
	vector<Product>::iterator start = obj.composition.begin();
	vector<Product>::iterator end = obj.composition.end();
	composition.assign(start, end);
	vector<int> compose_copy(obj.get_compose());
	vector<int>::iterator comp_start = compose_copy.begin();
	vector<int>::iterator comp_end = compose_copy.end();
	compose.assign(comp_start, comp_end);
	return *this;
}

void Drink::make_composition(vector<Product>& all_products)
{//состав напитка из номеров продуктов
	string Name;
	float Price;
	for (int i = 0; i < compose.size(); i++)
	{
		Name = all_products[compose[i]].get_name();
		composition.push_back(Product(Name));
		Price = all_products[compose[i]].get_money();
		composition[i].set_money(Price);
	}
}

void Drink::make_compose(vector<Product>& all_products)
{//состав (цифрами) из списка составляющих
	for (int i = 0; i < composition.size(); i++)
	{
		int q;
		for (int j = 0; j < all_products.size(); j++)
		{
			if (all_products[j].get_name() == composition[i].get_name())
			{
				q = j;
				break;
			}
		}
		compose.push_back(q);
	}
}

void Drink::make_history_drink(vector<Drink>& my_drinks, vector<Drink>& all_drinks, vector<Product>& all_products)
{//составить напиток по названию
	bool match;
	int j;
	for (int i = 0; i <= all_drinks.size(); i++)
	{
		if (i == all_drinks.size())
		{
			match = false;
			break;
		}
		if (all_drinks[i].get_name() == name)
		{
			j = i;
			match = true;
			break;
		}
	}
	if (!match)
	{
		for (int i = 0; i < my_drinks.size(); i++)
		{
			if (my_drinks[i].get_name() == name)
			{
				j = i;
				break;
			}
		}
	}
	if (match)
	{
		money = all_drinks[j].get_money();
		composition.resize(all_drinks[j].composition.size());
		for (int i = 0; i < all_drinks[j].composition.size(); i++)
		{
			composition[i] = all_drinks[j].composition[i];
		}
	}
	else
	{
		money = my_drinks[j].get_money();
		composition.resize(my_drinks[j].composition.size());
		for (int i = 0; i < my_drinks[j].composition.size(); i++)
		{
			composition[i] = my_drinks[j].composition[i];
		}
	}
	make_compose(all_products);
}

void Drink::my_price_recalculation()
{//пересчет цены
	money = 0.0;
	for (int i = 0; i < composition.size(); i++)
	{
		for (int j = 0; j < composition[i].get_volume(); j++)
			money += composition[i].get_money();
	}
}

ostream& operator<<(ostream &out, Drink &obj)
{
	cout << setfill(' ') << setw(30) << left << obj.name;
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(30) << left << obj.composition[0].get_name();
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551' << setw(10) << left << obj.composition[0].get_volume() << L'\u2551' << setw(10) << left << fixed << setprecision(2) << obj.money << L'\u2551' << endl;
	for (int i = 1; i < obj.composition.size(); i++)
	{
		wcout << setw(10) << right << L'\u2551' << setw(10) << L' ' << L'\u2551' << setw(30) << L' ' << L'\u255F' << setfill(L'\u2500') << setw(30) << L'\u2500' << L'\u256B';
		wcout << setw(10) << L'\u2500' << L'\u2562' << setfill(L' ') << setw(10) << L' ' << L'\u2551' << endl;
		
		wcout << setw(10) << right << L'\u2551' << setw(10) << L' ' << L'\u2551' << setw(30) << L' ' << L'\u2551';
		_setmode(_fileno(stdout), _O_TEXT);
		cout << setw(30) << left << obj.composition[i].get_name();
		_setmode(_fileno(stdout), _O_U16TEXT);
		wcout << L'\u2551' << setw(10) << left << obj.composition[i].get_volume() << L'\u2551' << setw(10) << L' ' << L'\u2551' << endl;
	}
	_setmode(_fileno(stdout), _O_TEXT);
	return out;
}