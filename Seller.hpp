#ifndef __SELLER_H__
#define __SELLER_H__

#include "User.hpp"
#include <vector>
#include "Offer.hpp"

class Seller: public User
{
private:
	vector <Offer*> offers;
public:
	Seller(string email, string username, long long password, int id);
	
	vector <Offer*> getOffers() {return offers;}

	void addNewOffer(Offer* newOffer) { offers.push_back(newOffer); };

};

#endif