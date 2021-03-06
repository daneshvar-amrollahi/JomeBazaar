#ifndef __SHOP_H__
#define __SHOP_H__

#include "User.hpp"
#include "Admin.hpp"
#include "Seller.hpp"
#include "Buyer.hpp"
#include "Order.hpp"

#include "Product.hpp"
#include "Mobile.hpp"
#include "Car.hpp"
#include "Tv.hpp"
#include "Discount.hpp"

#include <vector>
#include <cstddef>
#include <type_traits>

#include <unordered_map>
#include <math.h>

const int maxN = 2000 + 10;

class Shop
{

public:
	Shop();
	void signUp(vector <string> query);
	bool duplicateUsername(string username);
	
	void logIn(vector <string> query);
	void logOut(vector <string> query);

	void import(vector <string> query);

	void importMobile(string path);
	Mobile* getNewMobile(vector <string> splitted);
	void importCar(string path);
	Car* getNewCar(vector <string> splitted);
	void importTv(string path);
	Tv* getNewTv(vector <string> splitted);

	vector < pair<int, string> > getProducts(vector <string> query);

	bool isSeller(string username);
	bool isBuyer(string username);

	void addOffer(vector <string> query);

	bool duplicateOffer(int product_id);
	bool existsProductId(int product_id);

	Seller* findSeller(string username);
	Buyer* findBuyer(string username);

	vector < vector<string> > getMyOffers(vector <string> query);

	void changeOffer(vector <string> query);

	void printOffersForBuyer(vector <Offer> offers);
	void getOffersForBuyer();

	void getOffers(vector <string> query);

	vector < vector<string> >  getOffersOnProduct(vector <string> query);

	string getNameById(int id);

	bool isMobile(int id);
	bool isCar(int id);
	bool isTv(int id);

	Mobile* getMobileById(int id);
	Car* getCarById(int id);
	Tv* getTvById(int id);
	vector <string> getProductDetail(vector <string> query);

	void addCommentForId(int id, string s, string username);
	void postComment(vector <string> query);

	vector <string> getCommentsById(int id);
	void getComments(vector <string> query);

	void compareCars(int id1, int id2);
	void compareTvs(int id1, int id2);
	void compareMobiles(int id1, int id2);
	void getCompare(vector <string> query);

	void chargeWallet(vector <string> query);

	void addToCart(vector <string> query);

	Offer* getOfferById(int id);

	void generateDiscount(vector <string> query);

	Discount* getDiscountByCode(string code);

	Seller* getSellerByOfferId(int id);

	vector <string> getCart(vector <string> query);

	void getWalletCount(vector <string> query);

	Order* getOrderFromCart(pair< Offer* , pair<int, double> > current);

	void submitCart(vector <string> query);

	void getOrders(vector <string> query);


	long long getHash(string s);

	void evaluateModel();

	void evaluate(vector < pair<string, int> > comments, unordered_map<string, double> good, unordered_map<string, double> bad);

	unordered_map<string, double> getGoods();
	unordered_map<string, double> getBads();
	int isBad(string comment, unordered_map<string, double> good, unordered_map<string, double> bad);
	vector < pair<string, int> > readComments();

	User* getCurrentUser() {return currentUser;}



private:
	vector <Mobile*> mobiles;
	vector <Tv*> tvs;
	vector <Car*> cars;
	Admin* admin;
	vector <Seller*> sellers;
	vector <Buyer*> buyers;
	User* currentUser;
	int users_count;
	int products_count;
	int offers_count;

	vector <Discount*> discounts;

	long long MOD;
	long long base;

};

#endif