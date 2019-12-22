#ifndef __USER_H__
#define __USER_H__

#include <string>

#include "Offer.hpp"

using namespace std;

#define ADMIN "admin"
#define SELLER "seller"
#define BUYER "buyer"

class User
{
protected:
	string email;
	string username;
	long long password;
	string type;
	int id;

	vector <double> wallet;
public:
	User(string _email, string _username, long long _password, int _id);
	string getEmail() {return email;}
	string getUsername() {return username;}
	long long getPassword() {return password;}
	string getType() {return type;}
	int getId() {return id;}

	void addToWallet(double charge);

	vector <double> getWallet() {return wallet;}

};

#endif