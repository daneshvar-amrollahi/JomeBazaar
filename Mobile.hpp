#ifndef __MOBILE_H__
#define __MOBILE_H__

#include "Product.hpp"

#include <string>

using namespace std;

class Mobile: public Product
{
private:

	string name;
	int weight;
	double cpu_frequency;
	int built_in_memory;
	int ram;
	double display_size;
	int camera_resolution;
	string operating_system;

public:
	Mobile(string _name, int _weight, double _cpu_frequency, int _built_in_memory, int _ram, double _display_size,
		int _camera_resolution, string _operating_system_, int _product_id);

	int getProductId() {return product_id;}
	string getName() {return name;}
	int getWeight() {return weight;}
	double getCpuFrequency() {return cpu_frequency;}
	int getBuiltInMemory() {return built_in_memory;}
	int getRam() {return ram;}
	double getDisplaySize() {return display_size;}
	int getCameraResolution() {return camera_resolution;}
	string getOperatingSystem() {return operating_system;}

};

#endif