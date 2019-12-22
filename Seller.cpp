#include "Seller.hpp"

Seller::Seller(string email, string username, long long password, int id)
	:User(email, username, password, id) {

	type = SELLER;

}