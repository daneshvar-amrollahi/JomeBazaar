#include "User.hpp"

User::User(string _email, string _username, long long _password, int _id)
{
	email = _email;
	username = _username;
	password = _password;
	id = _id;

	wallet.push_back(0);
}

void User::addToWallet(double charge)
{
	wallet.push_back(wallet.back() + charge);
}

