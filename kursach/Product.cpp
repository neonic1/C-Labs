#include "Classes.h"

Product Product::operator=(Product obj)
{
	name = obj.name;
	money = obj.money;
	volume = obj.volume;
	number = obj.number;
	return *this;
}

ostream& operator<<(ostream &out, Product &obj)
{
	cout << setw(20) << left << obj.name;
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << setw(10) << left << fixed << setprecision(2) << obj.money;
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L'\u2551' << endl;
	_setmode(_fileno(stdout), _O_TEXT);
	return out;
}