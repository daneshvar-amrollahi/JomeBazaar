#include "Discount.hpp"
#include <time.h>

Discount::Discount(double _percent, Offer* _offer, int _number)
{
	string _code = "";
	vector <char> valid_char;
	for (int i = 0 ; i < 26 ; i++)
		valid_char.push_back(i + 'a');
	for (int i = 0 ; i < 26 ; i++)
		valid_char.push_back(i + 'A');
	for (int i = 0 ; i < 10 ; i++)
		valid_char.push_back('0' + i);

	srand (time(NULL));
	percent = _percent;
	number = _number;
	offer = _offer;
	int sz = valid_char.size();
	for (int i = 0 ; i < 15 ; i++)
		_code += valid_char[rand() % sz];
	
	code = _code;
}