#ifndef __ORDER_H__
#define __ORDER_H__

#include <string>

using namespace std;

class Order
{
private:
	int product_id;
	string product_name;
	int offer_id;
	int seller_id;
	double sold_price;
	int amount;

public:
	Order(int _product_id, string _product_name, int _offer_id, int _seller_id, double _sold_price, int _amount);

	int getProductId() {return product_id;}
	string getProductName() {return product_name;}
	int getOfferId() {return offer_id;}
	int getSellerId() {return seller_id;}
	double getSoldPrice() {return sold_price;}
	int getAmount() {return amount;}
};
#endif