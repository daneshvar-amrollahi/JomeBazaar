#include "Shop.hpp"
#include "Admin.hpp"
#include "BadRequestException.hpp"
#include "PermissionDeniedException.hpp"
#include "NotFoundException.hpp"

#define ADMIN_EMAIL "admin@gmail.com"

#include "Product.hpp"
#include "Mobile.hpp"
#include "Car.hpp"
#include "Tv.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

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


using namespace std;

Shop::Shop()
{
	Admin* newAdmin = new Admin;
	admin = newAdmin;
	currentUser = admin;
	users_count = 0;
	products_count = 0;
	offers_count = 0;
	MOD = 1e9 + 7;
	base = 727;
}


long long Shop::getHash(string s)
{
	long long h = 0;
	for (int i = 1 ; i <= s.size() ; i++)
	{
		h *= base;
		h %= MOD;
		h += (s[i - 1] - '0' + 1);
		h %= MOD;
	}
	return h;
}

void Shop::signUp(vector <string> query)
{
	if (query.size() > 11)
		throw &not_found;
	if (query.size() < 9)
		throw &bad_request;
	if (query.size() == 10)
		throw &bad_request;

	string type;
	if (query.size() == 9)
		type = BUYER;
	else
		type = query[10];

	if (query[QUESTIONMARK_INDEX] != "?" || query[3] != "email" || query[5] != "username" || query[7] != "password")
		throw &bad_request;

	if (query.size() == 11)
		if (query[9] != "type")
			throw &bad_request;

	string email = query[4];
	string username = query[6];
	long long password = getHash(query[8]);

	if (this->duplicateUsername(username))
	{
		throw &bad_request;
		return;
	}

	users_count++;
	if (type == SELLER)
	{
		Seller* newSeller = new Seller(email, username, password, users_count);
		sellers.push_back(newSeller);
		currentUser = newSeller;
	}
	if (type == BUYER)
	{
		Buyer* newBuyer = new Buyer(email, username, password, users_count);
		buyers.push_back(newBuyer);
		currentUser = newBuyer;
	}
}

bool Shop::duplicateUsername(string username)
{
	for (int i = 0 ; i < sellers.size() ; i++)
		if (sellers[i]->getUsername() == username)
			return 1;
	for (int i = 0 ; i < buyers.size() ; i++)
		if (buyers[i]->getUsername() == username)
			return 1;
	if (username == "admin")
		return 1;
	return 0;
}

void Shop::logIn(vector <string> query)
{
	if (query.size() < 7)
		throw &bad_request;
	if (query.size() > 7)
		throw &not_found;

	if (query[LOGIN_INDEX] != "login" || query[QUESTIONMARK_INDEX] != "?" || query[EMAIL_INDEX] != "email" || 
		query[PASSWORD_INDEX - 2] != "password")
		throw &bad_request;

	string email = query[EMAIL_INDEX + 1];
	long long password = getHash(query[6]);

	for (int i = 0 ; i < sellers.size() ; i++)
		if (sellers[i]->getEmail() == email && sellers[i]->getPassword() == password)
		{
			currentUser = sellers[i];
			return;
		}
	for (int i = 0 ; i < buyers.size() ; i++)
		if (buyers[i]->getEmail() == email && buyers[i]->getPassword() == password)
		{
			currentUser = buyers[i];
			return;
		}
	if (email == ADMIN_EMAIL && query[6] == "admin")
	{
		currentUser = admin;
		return;
	}


	throw &bad_request;

}

void Shop::logOut(vector <string> query)
{
	if (query.size() > 2)
		throw &not_found;
	if (currentUser == NULL)
	{
		throw &permission_denied;
		return;
	}

	if (isBuyer(currentUser->getUsername()))
	{
		Buyer* buyer = findBuyer(currentUser->getUsername());
		buyer->emptyCart();
	}

	currentUser = NULL;
}

#define MOBILE 0
#define CAR 1
#define TV 2

vector <string> split_by_comma(string line)
{
	vector <string> ans;
	string cur = "";
	for (int i = 0 ; i < line.size() ; i++)
	{
		if (line[i] == ',')
		{
			ans.push_back(cur);
			cur = "";
			continue;
		}
		cur += line[i];
	}				
	ans.push_back(cur);
	return ans;
}

int getType(string path)
{
	char c = path[path.size() - 5];
	if (c == 'e')
		return 0;
	if (c == 'r')
		return 1;
	if (c == 'V' || c == 'v')
		return 2;
}

int string_to_int(string s)
{
	int ans = 0;
	for (int i = 0 ; i < s.size() ; i++)
		ans *= 10, ans += (s[i] - 'a');
	return ans;
}

Car* Shop::getNewCar(vector <string> splitted)
{
	string name = splitted[0];
	int weight = stoi(splitted[1]);
	int num_of_seats = stoi(splitted[2]);
	int num_of_cylinders = stoi(splitted[3]);
	int engine_capacity = stoi(splitted[4]);
	int reverse_parking_sensors = stoi(splitted[5]);
	return new Car(name, weight, num_of_seats, num_of_cylinders, engine_capacity, reverse_parking_sensors, ++products_count);
}

Mobile* Shop::getNewMobile(vector <string> splitted)
{
	string name = splitted[0];
	int weight = stoi(splitted[1]);
	double cpu_frequency = stod(splitted[2]);
	int built_in_memory = stoi(splitted[3]);
	int ram = stoi(splitted[4]);
	double display_size = stod(splitted[5]);
	int camera_resolution = stoi(splitted[6]);
	string operating_system = splitted[7];
	return new Mobile(name, weight, cpu_frequency, built_in_memory, ram, display_size, camera_resolution, operating_system, ++products_count);
}

Tv* Shop::getNewTv(vector <string> splitted)
{
	string name = splitted[0];
	int screen_size = stoi(splitted[1]);
	string screen_type = splitted[2];
	string resolution = splitted[3];
	int three_d = stoi(splitted[4]);
	int hdr = stoi(splitted[5]);
	return new Tv(name, screen_size, screen_type, resolution, three_d, hdr, ++products_count);
}

string get_name(string loc)
{
	if ((loc[0] >= 'a' && loc[0] <= 'z') || (loc[0] >= 'A' && loc[0] <= 'Z'))
		return loc;
	string ret = ".//";
	for (int i = 3 ; i < loc.size() ; i++)
	{
		if (loc[i] == '/')
			ret += "//";
		else
			ret += loc[i];
	}

	return ret;
}

void Shop::importMobile(string path)
{
	ifstream fin(path.c_str());
	string line;
	getline(fin, line);

	while (getline(fin, line))
	{
		vector<string> splitted = split_by_comma(line);
		Mobile* newMobile = getNewMobile(splitted);
		mobiles.push_back(newMobile);
	}
}

void Shop::importCar(string path)
{
	ifstream fin(get_name(path).c_str());
	string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		vector<string> splitted = split_by_comma(line);
		Car* newCar = getNewCar(splitted);
		cars.push_back(newCar);
	}
}



void Shop::importTv(string path)
{
	cout << "importing tvzzzzzzzz" << endl;
	ifstream fin(get_name(path).c_str());
	string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		vector<string> splitted = split_by_comma(line);
		Tv* newTv = getNewTv(splitted);
		tvs.push_back(newTv);
	}

}

void Shop::import(vector <string> query)
{

	if (currentUser->getUsername() != ADMIN)
		throw &permission_denied;	

	if (query.size() < 7)
		throw &bad_request;
	if (query.size() > 7)
		throw &not_found;

	if(query[QUESTIONMARK_INDEX] != "?" || query[3] != "type" || (query[4] != "mobile" && query[4] != "car" && query[4]!= "tv") 
		|| (query[PATH_INDEX] != "filePath") )
		throw &bad_request;

	string path = query[PATH_INDEX + 1];


	int type = getType(path);
	if (type == MOBILE)
		this->importMobile(path);

	if (type == CAR)
		this->importCar(path);

	if (type == TV)
		this->importTv(path);
}

bool cmp(pair<int, string> A, pair<int, string> B)
{
	return A.first < B.first;
}

bool Shop::isSeller(string username)
{
	for (int i = 0 ; i < sellers.size() ; i++)
		if (sellers[i]->getUsername() == username)
			return 1;
	return 0;
}

vector < pair<int, string> > Shop::getProducts(vector <string> query)
{
	if (currentUser->getType() != SELLER && currentUser->getType() != BUYER)
		throw &permission_denied;

	if (query.size() > 2)
		throw &not_found;

	vector < pair<int, string> > products;
	for (int i = 0 ; i < mobiles.size() ; i++)
	{
		Mobile* current = mobiles[i];
		products.push_back(make_pair(current->getProductId(), current->getName()));
	}
	
	for (int i = 0 ; i < cars.size() ; i++)
	{
		Car* current = cars[i];
		products.push_back(make_pair(current->getProductId(), current->getName()));
	}
	
	for (int i = 0 ; i < tvs.size() ; i++)
	{
		Tv* current = tvs[i];
		products.push_back(make_pair(current->getProductId(), current->getName()));
	}

	sort(products.begin(), products.end(), cmp);
	cout << "productId | productName" << endl;
	for (int i = 0 ; i < products.size() ; i++)
	{
		int id = products[i].first;
		string name = products[i].second;
		cout << id << " | "<< name << endl;
	}
	return products;
}


bool Shop::duplicateOffer(int product_id)
{
	vector <Offer*> offers = (this->findSeller(currentUser->getUsername()))->getOffers();
	for (int i = 0 ; i < offers.size() ; i++)
		if (offers[i]->getProductId() == product_id)
			return 1;
	return 0;
}

Seller* Shop::findSeller(string username)
{
	for (int i = 0 ; i < sellers.size() ; i++)
		if (sellers[i]->getUsername()== username)
			return sellers[i];
}

Buyer* Shop::findBuyer(string username)
{
	for (int i = 0 ; i < buyers.size() ; i++)
		if (buyers[i]->getUsername() == username)
			return buyers[i];
}

void Shop::addOffer(vector <string> query)
{
	if (query.size() < 9)
		throw &bad_request;
	if (query.size() > 9)
		throw &not_found;

	if (query[OFFER_INDEX] != "offer" || query[QUESTIONMARK_INDEX] != "?" || query[3] != "productId" || query[5] != "offerUnitPrice" ||
			query[7] != "offerAmount")
		throw &bad_request;

	int product_id = stoi(query[4]);
	double price = stod(query[6]);
	int amount = stoi(query[8]);

	if (this->duplicateOffer(product_id))
		throw &bad_request;

	if (!(this->existsProductId(product_id)))
		throw &not_found;

	Offer* newOffer = new Offer(product_id, ++offers_count, price, amount);
		
	Seller* current_seller = this->findSeller(currentUser->getUsername());
	current_seller->addNewOffer(newOffer);
}

bool Shop::existsProductId(int product_id)
{
	for (int i = 0 ; i < mobiles.size() ; i++)
		if (mobiles[i]->getProductId() == product_id)
			return 1;

	for (int i = 0 ; i < cars.size() ; i++)
		if (cars[i]->getProductId() == product_id)
			return 1;

	for (int i = 0 ; i < tvs.size() ; i++)
		if (tvs[i]->getProductId() == product_id)
			return 1;	

	return 0;
}

vector < vector <string> > Shop::getMyOffers(vector <string> query)
{
	if (!isSeller(currentUser->getUsername()))
		throw &permission_denied;

	if (query.size() > 2)
		throw &not_found;

	Seller* current_seller = this->findSeller(currentUser->getUsername());
	vector <Offer*> offers = current_seller->getOffers();

	vector < vector<string> > res;
	cout << "productId | offerId | offerUnitPrice | offerAmount" << endl;
	for (int i = 0 ; i < offers.size() ; i++)
	{
		vector <string> current;
		Offer* current_offer = offers[i];
		cout << current_offer->getProductId() << " | "<< current_offer->getId() << " | " << current_offer->getUnitPrice() << " | " << current_offer->getAmount() << endl;
		
		current.push_back(to_string(current_offer->getProductId()));
		current.push_back(to_string(current_offer->getId()));
		current.push_back(to_string(current_offer->getUnitPrice()));
		current.push_back(to_string(current_offer->getAmount()));

		res.push_back(current);
	}

	return res;
}

void Shop::changeOffer(vector <string> query)
{
	if (query.size() < 9)
		throw &bad_request;

	if (query[QUESTIONMARK_INDEX] != "?" || query[3] != "offerId" || query[5] != "offerUnitPrice" || query[7] != "offerAmount")
		throw &bad_request;


	int offer_id = stoi(query[4]);
	double offer_unit_price = stod(query[6]);
	int offer_amount = stoi(query[8]);

	Seller* current_seller = this->findSeller(currentUser->getUsername());

	vector <Offer*> offers = current_seller->getOffers();
	for (int i = 0 ; i < offers.size() ; i++)
	{
		Offer* current_offer = offers[i];
		if (offers[i]->getId() == offer_id)
		{
			offers[i]->setUnitPrice(offer_unit_price);
			offers[i]->setAmount(offer_amount);
			return;
		}
	}
	throw &not_found;
}

Offer getOffer(Offer* current_offer)
{
	int product_id = current_offer->getProductId();
	int id = current_offer->getId();
	double price = current_offer->getUnitPrice();
	int amount = current_offer->getAmount();
	return Offer(product_id, id, price, amount);
}

bool cmp1(Offer A, Offer B)
{
	return A.getId() < B.getId();
}

bool cmp2(Offer A, Offer B)
{
	return A.getUnitPrice() < B.getUnitPrice();
}

bool cmp3(Offer A, Offer B)
{	
	return A.getId() > B.getId();
}

bool cmp4(Offer A, Offer B)
{
	return A.getUnitPrice() > B.getUnitPrice();
}

void printOffers(vector <Offer> offers)
{
	cout << "productId | offerId | offerUnitPrice | offerAmount" << endl;
	for (int i = 0 ; i < offers.size() ; i++)
	{
		Offer offer = offers[i];
		cout << offer.getProductId() << " | " << offer.getId() << " | " << offer.getUnitPrice() << " | " << offer.getAmount() << endl;
	}
}

bool getOffersHasBadRequest(vector <string> query)
{
	if (query.size() < 7)
		return 1;
	if (query[2] != "?")
		return 1;
	if (query[3] != "order" || query[5] != "field")
		return 1;
	if ((query[4] != "ASCEND" && query[4] != "DESCEND") || (query[6] != "offerId" && query[6]!= "offerPrice"))
		return 1;
	return 0;
}

void Shop::printOffersForBuyer(vector <Offer> offers)
{
	cout << "productId | productName | offerId | offerUnitPrice | offerAmount" << endl;
	for (int i = 0 ; i < offers.size() ; i++)
	{
		Offer offer = offers[i];
		int product_id = offer.getProductId();
		string name;
		if (isMobile(product_id))
		{
			Mobile* mobile = getMobileById(product_id);
			name = mobile->getName();
		}
		if (isTv(product_id))
		{
			Tv* tv = getTvById(product_id);
			name = tv->getName();
		}
		if (isCar(product_id))
		{
			Car* car = getCarById(product_id);
			name = car->getName();
		}

		cout << offer.getProductId() << " | " << name << " | " << offer.getId() << " | " << offer.getUnitPrice() << " | " << offer.getAmount() << endl;
	}
}

void Shop::getOffersForBuyer()
{
	vector <Offer> offers;
	for (int i = 0 ; i < sellers.size() ; i++)
	{
		vector <Offer*> current_offers = sellers[i]->getOffers();
		for (int j = 0 ; j < current_offers.size() ; j++)
		{
			Offer* current_offer = current_offers[j];
			offers.push_back(getOffer(current_offer));
		}
	}

	sort(offers.begin(), offers.end(), cmp1);
	printOffersForBuyer(offers);
}

void Shop::getOffers(vector <string> query)
{
	if (query.size() == 2)
	{
		if (isBuyer(currentUser->getUsername()))
		{
			this->getOffersForBuyer();
			return;
		}
	}


	if (getOffersHasBadRequest(query))
		throw &bad_request;
	if (currentUser->getUsername() != ADMIN)
		throw &permission_denied;

	if (query.size() > 7)
		throw &not_found;

	vector <Offer> offers;
	for (int i = 0 ; i < sellers.size() ; i++)
	{
		vector <Offer*> current_offers = sellers[i]->getOffers();
		for (int j = 0 ; j < current_offers.size() ; j++)
		{
			Offer* current_offer = current_offers[j];
			offers.push_back(getOffer(current_offer));
		}
	}

	if (query[4] == "ASCEND")
	{
		if (query[6] == "offerId")
			sort(offers.begin(), offers.end(), cmp1);
		if (query[6] == "offerPrice")
			sort(offers.begin(), offers.end(), cmp2);
	}
	if (query[4] == "DESCEND")
	{
		if (query[6] == "offerId")
			sort(offers.begin(), offers.end(), cmp3);
		if (query[6] == "offerPrice")
			sort(offers.begin(), offers.end(), cmp4);
	}

	printOffers(offers);
}


vector < vector<string> > printOffersOnProduct(vector <Offer> offers, string name)
{
	vector < vector<string> > ret; 
	cout << "productId | productName | offerId | offerUnitPrice | offerAmount" << endl;
	for (int i = 0 ; i < offers.size() ; i++)
	{
		Offer current_offer = offers[i];
		vector <string> current;
		current.push_back(to_string(current_offer.getId()));
		current.push_back(to_string(current_offer.getUnitPrice()));
		current.push_back(to_string(current_offer.getAmount()));
		ret.push_back(current);
		cout << current_offer.getProductId() << " | " << name << " | " << current_offer.getId() << " | "
		<< current_offer.getUnitPrice() << " | " << current_offer.getAmount() << endl;
	}
	return ret;
}

string Shop::getNameById(int id)
{
	for (int i = 0 ; i < mobiles.size() ; i++)
		if (mobiles[i]->getProductId() == id)
			return mobiles[i]->getName();
	for (int i = 0 ; i < cars.size() ; i++)
		if (cars[i]->getProductId() == id)
			return cars[i]->getName();
	for (int i = 0 ; i < tvs.size() ; i++)
		if (tvs[i]->getProductId() == id)
			return tvs[i]->getName();
	return "product_not_found";
}

vector< vector<string> > Shop::getOffersOnProduct(vector <string> query)
{
	if (query.size() < 5)
		throw &bad_request;

	if (query[2] != "?" || query[3] != "productId")
		throw &bad_request;

	if (query.size() > 5)
		throw &not_found;

	int product_id = stoi(query[4]);
	vector <Offer> offers_on_product;
	for (int i = 0 ; i < sellers.size() ; i++)
	{
		vector <Offer*> current_offers = sellers[i]->getOffers();
		for (int j = 0 ; j < current_offers.size() ; j++)
		{
			Offer* current_offer = current_offers[j];
			if (current_offer->getProductId() == product_id)
				offers_on_product.push_back(getOffer(current_offer));
		}
	}

	string name = this->getNameById(product_id);
	if (name == "product_not_found")
		throw &not_found;
	sort(offers_on_product.begin(), offers_on_product.end(), cmp1);
	return printOffersOnProduct(offers_on_product, name);
}

bool Shop::isMobile(int id)
{
	for (int i = 0 ; i < mobiles.size() ; i++)
		if (mobiles[i]->getProductId() == id)
			return 1;
	return 0;
}

bool Shop::isCar(int id)
{
	for (int i = 0 ; i < cars.size() ; i++)
		if (cars[i]->getProductId() == id)
			return 1;
	return 0;
}

bool Shop::isTv(int id)
{
	for (int i = 0 ; i < tvs.size() ; i++)
		if (tvs[i]->getProductId() == id)
			return 1;
	return 0;
}

Mobile* Shop::getMobileById(int id)
{
	for (int i = 0 ; i < mobiles.size() ; i++)
		if (mobiles[i]->getProductId() == id)
			return mobiles[i];
}

Car* Shop::getCarById(int id)
{
	for (int i = 0 ; i < cars.size() ; i++)
		if (cars[i]->getProductId() == id)
			return cars[i];	
}

Tv* Shop::getTvById(int id)
{
	for (int i = 0 ; i < tvs.size() ; i++)
		if (tvs[i]->getProductId() == id)
			return tvs[i];
}

vector <string> printTv(Tv* tv)
{
	vector <string> res;
	cout << tv->getName() << endl; 
	res.push_back(tv->getName());

	cout << "Screen Size: " << tv->getScreenSize() << endl; 
	res.push_back("Screen Size: " + to_string(tv->getScreenSize()));

	cout << "Screen Type: " << tv->getScreenType() << endl; 
	res.push_back("Screen Type: " + tv->getScreenType());

	cout << "Resolution: " << tv->getResolution() << endl; 
	res.push_back("Resolution: " + tv->getResolution());

	cout << "3D: " << tv->getThreeD() << endl; 
	res.push_back("3D: " + to_string(tv->getThreeD()));

	cout << "HDR: " << tv->getHdr() << endl; 
	res.push_back("HDR: " + to_string(tv->getHdr()));
	return res;
}

vector <string> printMobile(Mobile* mobile)
{
	vector <string> res;
	cout << mobile->getName() << endl; 
	res.push_back(mobile->getName());

	cout << "Weight: " << mobile->getWeight() << endl; 
	res.push_back("Weight: " + to_string(mobile->getWeight()));

	cout << "CPUFrequency: " << mobile->getCpuFrequency() << endl; 
	res.push_back("CPUFrequency: " + to_string(mobile->getCpuFrequency()));

	cout << "Built-in Memory: " << mobile->getBuiltInMemory() << endl; 
	res.push_back("Built-in Memory: " + to_string(mobile->getBuiltInMemory()));

	cout << "RAM: " << mobile->getRam() << endl; 
	res.push_back("RAM: " + to_string(mobile->getRam()));

	cout << "Display Size: " << mobile->getDisplaySize() << endl; 
	res.push_back("Display Size: " + to_string(mobile->getDisplaySize()));

	cout << "Camera Resolution: " << mobile->getCameraResolution() << endl; 
	res.push_back("Camera Resolution: " + to_string(mobile->getCameraResolution()));

	cout << "Operating System: " << mobile->getOperatingSystem() << endl; 
	res.push_back("Operating System: " + mobile->getOperatingSystem());
	return res;
}

vector <string> printCar(Car* car)
{
	vector <string> res;
	cout << car->getName() << endl;
	res.push_back(car->getName());

	cout << "Weight: " << car->getWeight() << endl; 
	res.push_back("Weight: " + to_string(car->getWeight()));

	cout << "Num. of Seats: " << car->getNumOfSeats() << endl; 
	res.push_back("Num. of Seats: " + to_string(car->getNumOfSeats()));

	cout << "Num. of Cylinders: " << car->getNumOfCylinders() << endl; 
	res.push_back("Num. of Cylinders: " + to_string(car->getNumOfCylinders()));

	cout << "Engine Capacity: " << car->getEngineCapacity() << endl; 
	res.push_back("Engine Capacity: " + to_string(car->getEngineCapacity()));

	cout << "Reverse Parking Sensors: " << car->getReverseParkingSensors() << endl; 
	res.push_back("Reverse Parking Sensors: " + to_string(car->getReverseParkingSensors()));
	return res;
}

bool Shop::isBuyer(string username)
{
	for (int i = 0 ; i < buyers.size() ; i++)
		if (buyers[i]->getUsername() == username)
			return 1;
	return 0;
}

vector <string> Shop::getProductDetail(vector <string> query)
{
	if (query.size() < 5)
		throw &bad_request;
	if (query.size() > 5)
		throw &not_found;

	if (query[2] != "?" || query[3] != "productId")
		throw &bad_request;

	if (!isBuyer(currentUser->getUsername()))
		throw &permission_denied;

	int id = stoi(query[4]);
	if (isTv(id))
	{
		Tv* tv = getTvById(id);
		return printTv(tv);
	}
	if (isMobile(id))
	{
		Mobile* mobile = getMobileById(id);
		return printMobile(mobile);	
	}
	if (isCar(id))
	{
		Car* car = getCarById(id);
		return printCar(car);
	}

	throw &not_found;
}

void Shop::addCommentForId(int id, string s, string username)
{
	if (isTv(id))
	{
		Tv* tv = this->getTvById(id);
		tv->addComment(username, s);
	}
	if (isCar(id))
	{
		Car* car = this->getCarById(id);
		car->addComment(username, s);
	}
	if (isMobile(id))
	{
		Mobile* mobile = this->getMobileById(id);
		mobile->addComment(username, s);
	}
}

void Shop::postComment(vector <string> query)
{
	if (query.size() < 7)
		throw &bad_request;
	
	if (query[2] != "?" || query[3] != "productId" || query[5] != "comment")
		throw &not_found;
	if (!isBuyer(currentUser->getUsername()))
		throw &permission_denied;

	int product_id = stoi(query[4]);
	if (!(this->existsProductId(product_id)))
		throw &not_found;

	string comment = "";
	for (int i = 6 ; i < query.size() ; i++)
		comment += query[i] + " ";
	while (comment[comment.size() - 1] == ' ')
		comment.resize(comment.size() - 1);

	unordered_map<string, double> good = this->getGoods();
	unordered_map<string, double> bad = this->getBads();
	if (isBad(comment, good, bad))
	{
		return;
	}

	addCommentForId(product_id, comment, currentUser->getUsername());
}

vector <string> Shop::getCommentsById(int id)
{
	vector <string> ans;
	if (isTv(id))
	{
		Tv* tv = this->getTvById(id);
		vector < pair<string, string> > comments = tv->getComments();
		ans.push_back(tv->getName());
		for (int i = 0 ; i < comments.size() ; i++)
			ans.push_back((comments[i].first) + " | " + (comments[i].second));
	}
	if (isCar(id))
	{
		Car* car = this->getCarById(id);
		vector < pair<string, string> > comments = car->getComments();
		ans.push_back(car->getName());
		for (int i = 0 ; i < comments.size() ; i++)
			ans.push_back((comments[i].first) + " | " + (comments[i].second));	
	}
	if (isMobile(id))
	{
		Mobile* mobile = this->getMobileById(id);
		vector < pair<string, string> > comments = mobile->getComments();
		ans.push_back(mobile->getName());
		for (int i = 0 ; i < comments.size() ; i++)
			ans.push_back((comments[i].first) + " | " + (comments[i].second));
	}
	return ans;
}

void Shop::getComments(vector <string> query)
{
	if (query.size() < 5)
		throw &bad_request;
	if (query[2] != "?" || query[3] != "productId")
		throw &bad_request;
	if (query.size() > 5)
		throw &bad_request;

	int product_id = stoi(query[4]);
	if (!(this->existsProductId(product_id)))
		throw &not_found;

	vector <string> comments = this->getCommentsById(product_id);
	for (int i = 0 ; i < comments.size() ; i++)
		cout << comments[i] << endl;
}

void Shop::compareTvs(int id1, int id2)
{
	Tv* tv1 = this->getTvById(id1);
	Tv* tv2 = this->getTvById(id2);
	cout << tv1->getName() << " | " << tv2->getName() << endl;
	cout << "Screen Size: " << tv1->getScreenSize() << " | " << tv2->getScreenSize() << endl;
	cout << "Screen Type: " << tv1->getScreenType() << " | " << tv2->getScreenType() << endl;
	cout << "Resolution: " << tv1->getResolution() << " | " << tv2->getResolution() << endl;
	cout << "3D: " << tv1->getThreeD() << " | " << tv2->getThreeD() << endl;
	cout << "HDR: " << tv1->getHdr() << " | " << tv2->getHdr() << endl;
}

void Shop::compareCars(int id1, int id2)
{
	Car* car1 = this->getCarById(id1);
	Car* car2 = this->getCarById(id2);

	cout << car1->getName() << " | " << car2->getName() << endl;
	cout << "Weight: " << car1->getWeight() << " | " << car2->getWeight() << endl;
	cout << "Num. of Seats: " << car1->getNumOfSeats() << " | " << car2->getNumOfSeats() << endl;
	cout << "Num. of Cylinders: " << car1->getNumOfCylinders() << " | " << car2->getNumOfCylinders() << endl;
	cout << "Engine Capacity: " << car1->getEngineCapacity() << " | " << car2->getEngineCapacity() << endl;
	cout << "Reverse Parking Sensors: " << car1->getReverseParkingSensors() << " | " << car2->getReverseParkingSensors() << endl;

}

void Shop::compareMobiles(int id1, int id2)
{
	Mobile* mobile1 = this->getMobileById(id1);
	Mobile* mobile2 = this->getMobileById(id2);

	cout << mobile1->getName() << " | " << mobile2->getName() << endl;
	cout << "Weight: " << mobile1->getWeight() << " | " << mobile2->getWeight() << endl;
	cout << "CPUFrequency: " << mobile1->getCpuFrequency() <<  " | " << mobile2->getCpuFrequency() << endl;
	cout << "Built-in Memory: " << mobile1->getBuiltInMemory() << " | " << mobile2->getBuiltInMemory() << endl;
	cout << "RAM: " << mobile1->getRam() << " | " << mobile2->getRam() << endl;
	cout << "Display Size: " << mobile1->getDisplaySize() << " | " << mobile2->getDisplaySize() << endl;
	cout << "Camera Resolution: " << mobile1->getCameraResolution() << " | " << mobile2->getCameraResolution() << endl; 
	
	cout << "salam" << endl;
	cout << mobile1->getOperatingSystem() << endl;
	cout << mobile2->getOperatingSystem() << endl;
	 string temp1 = mobile1->getOperatingSystem();
	 string temp2 = mobile2->getOperatingSystem();
	 cout << temp1 << endl << temp2 << endl;
	cout << "Operating System: " << mobile1->getOperatingSystem() << " | " << mobile2->getOperatingSystem() << endl;
}

void Shop::getCompare(vector <string> query)
{
	if (query.size() < 7)
		throw &bad_request;
	if (query[2] != "?" || query[3] != "productId1" || query[5] != "productId2")
		throw &not_found;

	int product_id1 = stoi(query[4]);
	int product_id2 = stoi(query[6]);
	if (!(this->existsProductId(product_id1)))
		throw &not_found;
	if (!(this->existsProductId(product_id2)))
		throw &not_found;

	if (!isBuyer(currentUser->getUsername()))
		throw &permission_denied;

	if (isTv(product_id1) && isTv(product_id2))
	{
		compareTvs(product_id1, product_id2);
		return;
	}
	
	if (isCar(product_id1) && isCar(product_id2))
	{
		compareCars(product_id1, product_id2);
		return;
	}

	if (isMobile(product_id1) && isMobile(product_id2))
	{
		compareMobiles(product_id1, product_id2);
		return;
	}

	throw &bad_request;
}

void Shop::chargeWallet(vector <string> query)
{
	if (query.size() < 5)
		throw &bad_request;
	if (query[2] != "?" || query[3] != "amount")
		throw &bad_request;

	if (query.size() > 5)
		throw &not_found;

	if (!(this->isBuyer(currentUser->getUsername())))
		throw &permission_denied;

	double charge = stod(query[4]);
	if (charge <= 0)
		throw &bad_request;
	Buyer* currentBuyer = findBuyer(currentUser->getUsername());
	currentBuyer->addToWallet(charge);
}

Offer* Shop::getOfferById(int id)
{
	for (int i = 0 ; i < sellers.size() ; i++)
	{
		vector <Offer*> offers = sellers[i]->getOffers();
		for (int j = 0 ; j < offers.size() ; j++)
		{
			Offer* current_offer = offers[j];
			if (current_offer->getId() == id)
				return current_offer;
		}
	}
	return NULL;
}

Discount* Shop::getDiscountByCode(string code)
{
	for (int i = 0 ; i < discounts.size() ; i++)
		if (discounts[i]->getCode() == code)
			return discounts[i];
	return NULL;
}

void Shop::addToCart(vector <string> query)
{
	if (query.size() > 9)
		throw &not_found;

	if (query.size() != 7 && query.size() != 9)
		throw &bad_request;

	if (query[2] != "?" || query[3] != "offerId" || query[5] != "amount")
		throw &bad_request;

	
	if (query.size() == 9)
		if (query[7] != "discountCode")
			throw &bad_request;
				
	
	if (!(this->isBuyer(currentUser->getUsername())))
		throw &permission_denied;


	Buyer* buyer = findBuyer(currentUser->getUsername());
	
	int offer_id = stoi(query[4]);
	Offer* offer = getOfferById(offer_id);

	int want = stoi(query[6]);

	if (want > offer->getAmount())
		throw &bad_request;

	double disc = 0;
	if (query.size() == 9)
	{
		
		Discount* d = getDiscountByCode(query[8]);

		if (d == NULL)
			throw &bad_request;

		//discount besooze
		for (int i = 0 ; i < discounts.size() ; i++)
			if (discounts[i]->getCode() == query[8])
			{
				discounts.erase(discounts.begin() + i);
				return;
			}
			

		if (d->getOffer() != offer)
			throw &bad_request;
		disc = d->getPercent();
	}

	buyer->addToCart(offer, want, disc);
}

void Shop::generateDiscount(vector <string> query)
{
	if (!isSeller(currentUser->getUsername()))
		throw &permission_denied;

	if (query.size() < 9)
		throw &bad_request;
	if (query.size() > 9)
		throw &not_found;
	if (query[2] != "?" || query[3] != "offerId" || query[5] != "discountPercent" || query[7] != "discountNumber")
		throw &not_found;

	int offer_id = stoi(query[4]);
	Offer* offer = this->getOfferById(offer_id);
	if (offer == NULL)
		throw &bad_request;

	double percent = stod(query[6]);
	int number = stoi(query[8]);
	for (int i = 0 ; i < number ; i++)
	{
		Discount* d = new Discount(percent, offer);
		cout << d->getCode() << endl;
		discounts.push_back(d);
	}
}

Seller* Shop::getSellerByOfferId(int id)
{
	for (int i = 0 ; i < sellers.size() ; i++)
	{
		Seller* seller = sellers[i];
		vector <Offer*> offers = seller->getOffers();
		for (int j = 0 ; j < offers.size() ; j++)
			if (offers[j]->getId() == id)
				return seller;
	}
	return NULL;
}

vector<string> Shop::getCart(vector <string> query)
{
	if (!isBuyer(currentUser->getUsername()))
		throw &permission_denied;

	Buyer* buyer = findBuyer(currentUser->getUsername());
	vector < pair< Offer* , pair<int, double> > > cart = buyer->getCart();

	if (cart.size() == 0)
	{
		cout << "Empty" << endl;
		vector <string> ans;
		return ans;
	}

	vector <string> ret;
	cout << "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount" << endl; 
	ret.push_back("productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount");
	for (int i = 0 ; i < cart.size() ; i++)
	{
		pair< Offer* , pair<int, double> >  current = cart[i];
		Offer* offer = cart[i].first;
		int product_id = offer->getProductId();
		string product_name = (this->getNameById(product_id));
		int offer_id = offer->getId();
		Seller* seller = getSellerByOfferId(offer_id);
		int seller_id = seller->getId();
		int amount = current.second.first;
		double price = amount * (offer->getUnitPrice());

		ret.push_back(to_string(product_id) + " | " + product_name + " | " + to_string(offer_id) + " | " + to_string(seller_id) + " | " + to_string(price) + " | " + to_string(amount));
		cout << product_id << " | " << product_name << " | " << offer_id << " | " << seller_id << " | " << price << " | " << amount << endl; 
	}
	return ret;
}


void Shop::getWalletCount(vector <string> query)
{
	if (query.size() < 5)
		throw &bad_request;
	if (query.size() > 5)
		throw &not_found;
	if (query[2] != "?" || query[3] != "count")
		throw &bad_request;

	int count = stoi(query[4]);
	vector <double> wallet = currentUser->getWallet();
	cout << "credit" << endl;
	for (int i = wallet.size() - 1 ; i >= 0 && count > 0 ; i--, count--)
		cout << wallet[i] << endl;
}

Order* Shop::getOrderFromCart(pair< Offer* , pair<int, double> > current)
{
	Offer* offer = current.first;
	int product_id = offer->getProductId();
	string product_name = getNameById(product_id);
	int offer_id = offer->getId();
	Seller* seller = getSellerByOfferId(offer_id);
	int seller_id = seller->getId();

	double discount = current.second.second;
	int amount = current.second.first;
	double total_price = amount * (offer->getUnitPrice()); 
	double price = total_price - (discount / 100.0) * total_price;
	

	return new Order(product_id, product_name, offer_id, seller_id, price, amount);
}

void Shop::submitCart(vector <string> query)
{
	if (query.size() > 2)
		throw &not_found;

	if (!isBuyer(currentUser->getUsername()))
		throw &permission_denied;
	Buyer* buyer = findBuyer(currentUser->getUsername());
	vector < pair< Offer* , pair<int, double> > > cart = buyer->getCart();
	vector <Order*> currentOrders;;

	double total_price_buyer = 0;
	for (int i = 0 ; i < cart.size() ; i++)
	{
		pair< Offer* , pair<int, double> > current = cart[i];
		Order* currentOrder = this->getOrderFromCart(current);
		total_price_buyer += currentOrder->getSoldPrice();
		currentOrders.push_back(currentOrder);
	}

	if (total_price_buyer > buyer->getCredit())
		throw &bad_request;

	buyer->reduceWallet(total_price_buyer);
	for (int i = 0 ; i < cart.size() ; i++)
	{
		pair< Offer* , pair<int, double> > current = cart[i];
		Offer* offer = current.first;
		int offer_id = offer->getId();
		Seller* seller = getSellerByOfferId(offer_id);
		
		double discount = current.second.second;
		int amount = current.second.first;
		double total_price = amount * (offer->getUnitPrice()); 
		double price = total_price - (discount / 100.0) * total_price;

		seller->addToWallet(price);

		offer->setAmount(offer->getAmount() - amount);
	}

	buyer->emptyCart();
	buyer->addToOrders(currentOrders);
}

void Shop::getOrders(vector <string> query)
{
	if (!isBuyer(currentUser->getUsername()))
		throw &permission_denied;

	if (query.size() < 5)
		throw &bad_request;
	if (query.size() > 5)
		throw &not_found;

	if (query[2] != "?" || query[3] != "count")
		throw &bad_request;

	Buyer* buyer = findBuyer(currentUser->getUsername());
	vector < vector <Order*> > orders = buyer->getOrders();
	if (orders.size() == 0)
		throw &not_found;
	
	cout << "ProductId | productName | offerId | sellerId | soldPrice | amount" << endl;
	for (int i = 0 ; i < orders.size() ; i++)
	{
		for (int j = 0 ; j < orders[i].size() ; j++)
		{
			Order* currentOrder = orders[i][j];
			int product_id = currentOrder->getProductId();
			string product_name = currentOrder->getProductName();
			int offer_id = currentOrder->getOfferId();
			int seller_id = currentOrder->getSellerId();
			double sold_price = currentOrder->getSoldPrice();
			int amount = currentOrder->getAmount();
			cout << product_id << " | " << product_name << " | " << offer_id << " | " << seller_id << " | " << sold_price << " | " << amount << endl;
			if (i != orders.size() - 1)
				cout << "****" << endl;
		}
	}
}


unordered_map<string, double> Shop::getGoods()
{
	unordered_map <string, double> good;
	ifstream fin("train.csv");
	string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		if (line[0] - '0' >= 0 && line[0] - '0' < 10)
			continue;
		vector <string> q = split_by_comma(line);
		string word = q[0];
		double p_good = stod(q[1]);

		good[word] = p_good;
	}	
	return good;
}

unordered_map<string, double> Shop::getBads()
{
	unordered_map <string, double> bad;
	ifstream fin("train.csv");
	string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		if (line[0] - '0' >= 0 && line[0] - '0' < 10)
			continue;
		vector <string> q = split_by_comma(line);
		string word = q[0];
		double p_bad = stod(q[2]);
		bad[word] = p_bad;
	}	
	return bad;
}

vector < pair<string, int> > Shop::readComments()
{
	ifstream fin("test.csv");
	string line;
	vector < pair<string, int> > ans;
	getline(fin, line);
	while (getline(fin, line))
	{
		int last = line[line.size() - 1] - '0';
		line.resize(line.size() - 1);
		ans.push_back(make_pair(line, last));
	}
	return ans;
} 

vector <string> split_by_space(string line)
{
	vector <string> ans;
	string cur = "";
	for (int i = 0 ; i < line.size() ; i++)
	{
		if (line[i] == ' ')
		{
			if (cur != "")
				ans.push_back(cur);
			cur = "";
			continue;
		}
		cur += line[i];
	}			
	if (cur != "")	
		ans.push_back(cur);
	return ans;
}

int Shop::isBad(string comment, unordered_map<string, double> good, unordered_map<string, double> bad)
{
	long double spam = 0, ham = 0;
	vector <string> words = split_by_space(comment);
	for (int i = 0 ; i < words.size() ; i++)
	{
		string word = words[i];
		if (good.find(word) != good.end())
		{
			ham += (long double)(log(good[word]));
			spam += (long double)(log(bad[word]));
		}
		
	}
	ham += (long double)(log(0.91175));
	spam += (long double)(log(1-0.91175));
	return (spam > ham);
}

void Shop::evaluate(vector < pair<string, int> > comments, unordered_map<string, double> good, unordered_map<string, double> bad)
{
	int correct_detected_appropriate = 0, all_appropriate = 0;
	int detected_appropriate = 0, correct_detected = 0;
	for (int i = 0 ; i < comments.size() ; i++)
	{
		string comment = comments[i].first;
		int is_bad = comments[i].second;
		int detected_bad = isBad(comment, good, bad);
		correct_detected_appropriate += ( (!is_bad) && (!detected_bad) );
		all_appropriate += (!is_bad);

		detected_appropriate += (!detected_bad);

		correct_detected += (is_bad == detected_bad);
	}

	cout << "Recall: " << (double(correct_detected_appropriate) / double(all_appropriate)) * 100.0 << endl;
	cout << "Precision: " << (double(correct_detected_appropriate) / double(detected_appropriate)) * 100.0 << endl;
	cout << "Accuracy: " << (double(correct_detected) / double(comments.size())) * 100.0 << endl;
}

void Shop::evaluateModel()
{
	unordered_map<string, double> good = this->getGoods();
	unordered_map<string, double> bad = this->getBads();
	vector < pair<string, int> > comments = this->readComments();
	this->evaluate(comments, good, bad);
}