#include "Buyer.hpp"

Buyer::Buyer(string email, string username, long long password, int id)
	:User(email, username, password, id) {

	type = BUYER;
}


void Buyer::addToCart(Offer* offer, int number, double percent)
{
	cart.push_back(make_pair(offer, make_pair(number, percent)));
}

void Buyer::addToOrders(vector <Order*> order)	
{
	orders.push_back(order);
}

void Buyer::reduceWallet(double value)
{
	wallet.push_back(wallet.back() - value);
}