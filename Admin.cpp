#include "Admin.hpp"

Admin::Admin() :User("admin@gmail.com", "admin", -1, 0) {
	type = ADMIN;

}