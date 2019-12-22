#ifndef __NOTFOUNDEXCEPTION_H__
#define __NOTFOUNDEXCEPTION_H__

#include <exception>

using namespace std;

#define NOT_FOUND_MESSAGE "Not Found"

class NotFoundException: public exception
{
 	virtual const char* what() const throw()
 	{
   		return NOT_FOUND_MESSAGE;
  	}
}not_found;

#endif