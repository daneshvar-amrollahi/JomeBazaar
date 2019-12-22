#include "Car.hpp"

Car::Car(string _name, int _weight, int _num_of_seats, int _num_of_cylinders, int _engine_capacity, int _reverse_parking_sensors, int _product_id)
	:Product(_product_id){
	name = _name;
	weight = _weight;
	num_of_seats = _num_of_seats;
	num_of_cylinders = _num_of_cylinders;
	engine_capacity = _engine_capacity;
	reverse_parking_sensors = _reverse_parking_sensors;
}