#pragma once

template<class T>
bool comparison(T obj1, T obj2, int field, int way)
{
	if (field == 1)
	{
		if (way == 1)
		{
			if (obj1.get_name() < obj2.get_name()) return true;
			else return false;
		}
		else
		{
			if (obj1.get_name() > obj2.get_name()) return true;
			else return false;
		}
	}
	else
	{
		if (way == 1)
		{
			if (obj1.get_money() < obj2.get_money()) return true;
			else return false;
		}
		else
		{
			if (obj1.get_money() > obj2.get_money()) return true;
			else return false;
		}
	}
}

template<class T>
void sorting(vector<T>& arr, vector<string>& language)
{
	int text1[] = {117, 118};
	int text2[] = {119, 120};
	int field = 0;
	int way = 0;
	switch_exception(2, text1, field, language);//по названию или по цене
	switch_exception(2, text2, way, language);//по возрастанию или по убыванию

	int size = arr.size();
	T temp;
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			if (comparison(arr[j + 1], arr[j], field, way))
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}