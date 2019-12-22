#ifndef __TV_H__
#define __TV_H__

#include "Product.hpp"
#include <string>

using namespace std;

class Tv: public Product
{
private:
	string name;
	int screen_size;
	string screen_type;
	string resolution;
	int three_d;
	int hdr;


public:
	Tv(string _name, int _screen_size, string _screen_type, string _resolution, int _three_d, int _hdr, int _product_id);

	int getProductId() {return product_id;}
	string getName() {return name;}
	int getScreenSize() {return screen_size;}
	string getScreenType() {return screen_type;}
	string getResolution() {return resolution;}
	int getThreeD() {return three_d;}
	int getHdr() {return hdr;}
};

#endif