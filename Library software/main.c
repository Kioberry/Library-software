#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "library.h"
#include "book_management.h"
#include "global.h"
#include "user.h"

int main(int argc, char** argv) {
    char bfname[40];
    char ufname[40];
    // check that correct number of command line arguments are entered    
    if (argc != 3) {
        // use the error message 
        printf("Error\nExpected use: ./library books.txt users.txt\n");
        // exit the application if there is an error
        exit(1);
    }
    else {
        // assign command line value to filename string
        strcpy(bfname, argv[1]);
        strcpy(ufname, argv[2]);
    }
	libraryCLI();
	return 0;
}