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
	try
	{

		MyServer server(argc > 1 ? atoi(argv[1]) : 5000);

		User *currentUser = shop.getCurrentUser();

		server.get("/nobodyLoggedIn", new ShowPage("static/home.html"));

		server.get("/", new ShowPage("static/admin_home.html"));
		server.get("/adminHome", new ShowPage("static/admin_home.html"));

		server.get("/buyerHome", new BuyerHomeHandler(&shop));

		server.get("/sellerHome", new ShowPage("static/seller_home.html"));

		server.get("/buyerHome", new BuyerHomeHandler(&shop));

		server.get("/home.png", new ShowImage("static/home.png"));

		server.get("/signup", new ShowPage("static/signup.html"));
		server.post("/signup", new SignUpHandler(&shop));

		server.post("/adminUp", new UploadHandler(&shop));

		server.post("/logout", new LogOutHandler(&shop));

		server.run();
	}
	catch (Server::Exception ex)
	{
		cerr << ex.what() << endl;
	}
	return 0;
}
