#ifndef LOGIN_GUARD__H 
#define LOGIN_GUARD__H

#include <stdio.h>

//function for the operation of login system
void signCLI();

//display the Login menu
void signMenu();

//create a new account and store the 
//new user's information into user linked list.
void registration();

//verify the username and password to manage user logins.
void Login();

//search books by one of the three ways in the Login system
void signSearch();


#endif
