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

