#ifndef __BADREQUESTEXCEPTION_H__
#define __BADREQUESTEXCEPTION_H__

#include <exception>

using namespace std;

#define BAD_REQUEST_MESSAGE "Bad Request"

class BadRequestException: public exception
{
 	virtual const char* what() const throw()
 	{
   		return BAD_REQUEST_MESSAGE;
  	}
}bad_request;

#endif