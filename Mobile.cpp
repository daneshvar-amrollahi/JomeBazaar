#include "Mobile.hpp"

Mobile::Mobile(string _name, int _weight, double _cpu_frequency, int _built_in_memory, int _ram, double _display_size,
		int _camera_resolution, string _operating_system_, int _product_id) 
		:Product(_product_id){

	name = _name;
	weight = _weight;
	cpu_frequency = _cpu_frequency;
	built_in_memory = _built_in_memory;
	ram = _ram;
	display_size = _display_size;
	camera_resolution = _camera_resolution;
	operating_system = _operating_system_;
}