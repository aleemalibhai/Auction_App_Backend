#ifndef DRIVER_HEADER
#define DRIVER_HEADER

#include <string.h>
#include "data.h"
#include "user.h"
#include "item.h"

using namespace std;


class Driver{
	protected: 
		User* currentUser;
		bool isLoggedIn = false;

	public:
		void logout(Data &data); // allows logout
		void login(Data &data); // allows login
		User getCurrentUser(Data &data); // returns the current User
		void setCurrentUser(string userName, Data &data); // sets the current user
		void input(Data &data); // function in main's for loop that asks for input and directs for output
};

#endif
