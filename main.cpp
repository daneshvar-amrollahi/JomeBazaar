#include <iostream>
#include "Shop.hpp"
#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time

using namespace std;

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

