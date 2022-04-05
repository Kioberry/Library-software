#ifndef SIGN_GUARD__H 
#define SIGN_GUARD__H

#include <stdio.h>

//function for the operation of login system
void signCLI();

//display the Login menu
void signMenu();

//create the node of the linked list(used in registration to create a new account)
User* creatuNode(const char* name, const char* username, char password);

//transverse the linked list
User* searchUsername(const char* username);

//add a new user in the user linked list
void add_user(User* head, char name[50], char username[50], char password[50]);


//create a new account and store the 
//new user's information into user linked list.
void registration();

//transverse the userlist to varify the username and password.
//returns 1 if both username and password can be matched, returns 0 if
//username couldn't be matched and returns -1 if username can be matched 
// while password is incorrect.
int searchUser(FILE* fp, char ufname[50], char fusername[50], char fpassword[50]);



//verify the username and password to manage user logins.
void Login();

//search books by one of the three ways in the Login system
void signSearch();


#endif
