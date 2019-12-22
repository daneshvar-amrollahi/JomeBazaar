#ifndef __PERMISSIONDENIDEXCEPTION_H__
#define __PERMISSIONDENIEDEXCEPTION_H__

#include <exception>

using namespace std;

#define PERMISSION_DENIED_MESSAGE "Permission Denied"

class PermissionDeniedException: public exception
{
 	virtual const char* what() const throw()
 	{
   		return PERMISSION_DENIED_MESSAGE;
  	}
}permission_denied;

#endif