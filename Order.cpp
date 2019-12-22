#include "Order.hpp"

Order::Order(int _product_id, string _product_name, int _offer_id, int _seller_id, double _sold_price, int _amount)
{
	product_id = _product_id;
	product_name = _product_name;
	offer_id = _offer_id;
	seller_id = _seller_id;
	sold_price = _sold_price;
	amount = _amount;
}	