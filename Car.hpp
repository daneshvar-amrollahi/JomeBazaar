#ifndef __CAR_H__
#define __CAR_H__

#include "Product.hpp"

#include <string>

using namespace std;

class Car: public Product
{
private:
	string name;
	int weight;
	int num_of_seats;
	int num_of_cylinders;
	int engine_capacity;
	int reverse_parking_sensors;

public:
	Car(string _name, int _weight, int _num_of_seats, int _num_of_cylinders, int _engine_capacity, int _reverse_parking_sensors, int _product_id);
	int getProductId() {return product_id;}
	string getName() {return name;}
	int getWeight() {return weight;}
	int getNumOfSeats() {return num_of_seats;}
	int getNumOfCylinders() {return num_of_cylinders;}
	int getEngineCapacity() {return engine_capacity;}
	int getReverseParkingSensors() {return reverse_parking_sensors;}

};

#endif