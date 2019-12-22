#ifndef __DISCOUNT_H__
#define __DISCOUNT_H__

#include "Offer.hpp"
#include <vector>
#include <string>

using namespace std;

class Discount
{
private:
	string code;
	double percent;
	Offer* offer;
	int number;
public:
	Discount(double _percent, Offer* _offer, int _number);

	string getCode() {return code;}
	double getPercent() {return percent;}
	Offer* getOffer() {return offer;}
	int getNumber() {return number;}

	void decreaseNumber() {number--;}
};
#endif