#ifndef __OFFER_H__
#define __OFFER_H__

#include <vector>

class Offer
{
private:
	int product_id;
	int id;
	double unit_price;
	int amount;

public:

	Offer(int _product_id, int _id, double _unit_price, int _amount);

	void setUnitPrice(double _unit_price) {unit_price = _unit_price;}
	int setAmount(int _amount) {amount = _amount;}
	
	int getProductId() {return product_id;}
	int getId() {return id;}
	double getUnitPrice() {return unit_price;}
	int getAmount() {return amount;}
};

#endif