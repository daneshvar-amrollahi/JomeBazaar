#include <iostream>
#include "Shop.hpp"
#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time

using namespace std;

#define POST "POST"
#define GET "GET"
#define firstIndex 0
#define SINGUP_INDEX 1
#define QUESTIONMARK_INDEX 2
#define EMAIL_INDEX 3
#define USERNAME_INDEX 5
#define PASSWORD_INDEX 7
#define TYPE_INDEX 9
#define TYPE_INDEXX 10
#define LOGIN_INDEX 1
#define LOGOUT_INDEX 1
#define IMPORT_INDEX 1
#define PATH_INDEX 5
#define OFFER_INDEX 1
#define CHANGE_OFFER_INDEX 1


<<<<<<< HEAD
vector <string> splitBySpace(string s)
{
	vector <string> ans;
	string current = "";
	for (int i = 0 ; i < s.size() ; i++)
	{
		if (s[i] ==' ')
		{
			ans.push_back(current);
			current = "";
		}
		else
			current += s[i];
	}
	ans.push_back(current);
	return ans;
}

bool isSignUp(vector <string> query)
{
	if (query[SINGUP_INDEX] == "signup")
		return 1;
	return 0;
}

bool isLogin(vector <string> query)
{
	if (query[LOGIN_INDEX] == "login")
		return 1;
	return 0;
}

bool islogOut(vector <string> query)
{
	if (query[LOGOUT_INDEX] != "logout")
		return 0;
	return 1;
}

bool isImport(vector <string> query)
{
	if (query[IMPORT_INDEX] != "importProducts") 
		return 0;
	return 1;

}

bool isOffer(vector <string> query)
{
	if (query[1] == "offer")
		return 1;
	return 0;

}

bool isChangeOffer(vector <string> query)
{
	if (query[CHANGE_OFFER_INDEX] == "changeOffer")
		return 1;
	return 0;

}

bool isComment(vector <string> query)
{
	if (query[1] != "comment")
		return 0;
	return 1;
}

bool isChargeWallet(vector <string> query)
{
	if (query[1] != "chargeWallet")
		return 0;
	return 1;
}

bool isAddToCart(vector <string> query)
{
	if (query[1] != "addToCart")
		return 0;
	return 1;
}

bool isDiscountCode(vector <string> query)
{
	if (query[1] != "generateDiscountCode")
		return 0;
	return 1;
}

bool isSubmitCart(vector <string> query)
{
	if (query[1] != "submitCart")
		return 0;
	return 1;
}


bool isEvaluateModel(vector <string> query)
{
	if (query[1] != "evaluateModel")
		return 0;
	return 1;
}

void executePost(vector <string> query, Shop* shop)
{
	int sz = query.size();
	if (isSignUp(query))
	{
		shop->signUp(query);
		cout << "OK" << endl;
		return;
	}
	
	if (isLogin(query))
	{
		shop->logIn(query);
		cout << "OK" << endl;
		return;
	}
	if (islogOut(query))
	{
		shop->logOut(query);
		cout << "OK" << endl;
		return;
	}
	if (isImport(query))
	{
		shop->import(query);
		cout << "OK" << endl;
		return;
	}

	if (isOffer(query))
	{
		shop->addOffer(query);
		cout << "OK" << endl;
		return;
	}

	if (isChangeOffer(query))
	{
		shop->changeOffer(query);
		cout << "OK" << endl;
		return;
	}

	if (isComment(query))
	{
		shop->postComment(query);
		cout << "OK" << endl;
		return;
	}
	
	if (isChargeWallet(query))
	{
		shop->chargeWallet(query);
		cout << "OK" << endl;
		return;
	} 
	
	if (isDiscountCode(query))
	{
		shop->generateDiscount(query);
		return;
	}

	if (isAddToCart(query))
	{
		shop->addToCart(query);
		cout << "OK" << endl;
		return;
	}

	if (isSubmitCart(query))
	{
		shop->submitCart(query);
		cout << "OK" << endl;
		return;
	}
	if (isEvaluateModel(query))
	{
		shop->evaluateModel();
		return;
	}
	cout << "Not Found" << endl;
}

bool isGetProducts(vector <string> query)
{
	if (query[1] != "getProducts")
		return 0;
	return 1;
}

bool isGetMyOffers(vector <string> query)
{
	if (query[1] != "myOffers")
		return 0;
	return 1;
}

bool isGetOffers(vector <string> query)
{
	if (query[1] != "offers")
		return 0;
	return 1;
}

bool isGetOffersOnProduct(vector <string> query)
{
	if (query[1] != "offersOnProduct")
		return 0;
	return 1;
}

bool isGetProductDetail(vector <string> query)
{
	if (query[1] != "productDetail")
		return 0;
	return 1;
}

bool isGetComments(vector <string> query)
{
	if (query[1] != "comments")
		return 0;
	return 1;
}

bool isGetCompare(vector <string> query)
{
	if (query[1] != "compare")
		return 0;
	return 1;
}

bool isGetCart(vector <string> query)
{
	if (query[1] != "cart")
		return 0;
	return 1;
}

bool isGetWalletCount(vector <string> query)
{
	if (query[1] != "wallet")
		return 0;
	return 1;
}

bool isGetOrders(vector <string> query)
{
	if (query[1] != "orders")
		return 0;
	return 1;
}

void executeGet(vector <string> query, Shop* shop)
{
	if (isGetProducts(query))
	{
		shop->getProducts(query);
		return;
	}
	if (isGetMyOffers(query))
	{
		shop->getMyOffers(query);
		return;
	}
	if (isGetOffers(query))
	{
		shop->getOffers(query);
		return;
	}
	if (isGetOffersOnProduct(query))
	{
		shop->getOffersOnProduct(query);
		return;
	}
	if (isGetProductDetail(query))
	{	
		shop->getProductDetail(query);
		return;
	}
	if (isGetComments(query))
	{
		shop->getComments(query);
		return;
	}
	if (isGetCompare(query))
	{
		shop->getCompare(query);
		return;
	}
	if (isGetCart(query))
	{
		shop->getCart(query);
		return;
	}
	if (isGetWalletCount(query))
	{
		shop->getWalletCount(query);
		return;
	}
	if (isGetOrders(query))
	{
		shop->getOrders(query);
		return;
	}
	cout << "Not Found" << endl;
}

void executeQuery(string line, Shop* shop)
{
	vector <string> query = splitBySpace(line);
	string firstWord = query[firstIndex];
	if (firstWord == POST)
	{
		executePost(query, shop); 
		return;
	}
	if (firstWord == GET)
	{
		executeGet(query, shop);
		return;
	}

	cout << "Bad Request" << endl;
}
=======
>>>>>>> b1

/*
int main()
{
	Shop shop;
	string line;
	while (getline(cin, line))
	{
		try{
			executeQuery(line, &shop);
		}
		catch (exception *ex) {
			cout << ex->what() << "\n";
		}
	}
	return 0;
<<<<<<< HEAD
}
=======
}
*/

int main(int argc, char **argv) 
{
	Shop shop;
	srand(time(NULL)); // for rand
	try {
    	MyServer server(argc > 1 ? atoi(argv[1]) : 5000);

		if (shop.getCurrentUser() == NULL)
			server.get("/", new ShowPage("static/home.html"));

		string logged_in_type = (shop.getCurrentUser())->getType();
		if (logged_in_type == "admin")
			server.get("/", new ShowPage("static/admin_home.html"));
		
		server.get("/home.png", new ShowImage("static/home.png"));


		server.get("/signup", new ShowPage("static/signup.html"));
		server.post("/signup", new SignUpHandler(&shop));

    	server.run();
  	} catch (Server::Exception *ex) {
    	cerr << ex->what() << endl;
  }
}

>>>>>>> b1
