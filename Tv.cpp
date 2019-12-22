#include "Tv.hpp"

Tv::Tv(string _name, int _screen_size, string _screen_type, string _resolution, int _three_d, int _hdr, int _product_id)
	:Product(_product_id) {

	name = _name;
	screen_size = _screen_size;
	screen_type = _screen_type;
	resolution = _resolution;
	three_d = _three_d;
	hdr = _hdr;
	product_id = _product_id;
}