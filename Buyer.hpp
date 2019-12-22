#ifndef __BUYER_H__
#define __BUYER_H__

#include "User.hpp"
#include "Order.hpp"
#include <vector>

class Buyer: public User
{
private:
	vector < pair< Offer* , pair<int, double> > > cart;
	vector < vector <Order*> > orders;

public:
	Buyer(string email, string username, long long password, int id);
	
	void addToCart(Offer* offer, int number, double percent);


	vector < pair< Offer* , pair<int, double> > > getCart() {return cart;}

	void addToOrders(vector <Order*> order);

	double getCredit() {return wallet.back();}

	void reduceWallet(double value);

	vector < vector <Order*> > getOrders() {return orders;};

	void emptyCart() {cart.clear();}
};

#endif