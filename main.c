#include <stdio.h>
#include<stdlib.h>
#include "contact.h"

/*main function*/
int main() 
{
    /*declaring the choice variable*/
    int choice;
    /*declaring addressBook variable*/
    AddressBook addressBook;
    /*Initializing the address book*/
    initialize(&addressBook); 

    /*loop to accept the choice from the user until user exits*/
    do {
        /*prompt main menu*/
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");	
        printf("6. Save contacts\n");	
        printf("7. Exit\n");
        /*prompt message to enter the choice*/
        printf("Enter your choice: ");
        /*read choice from the user*/
        scanf("%d",&choice);
        getchar();
        /*depending on the choice calling function*/
        switch (choice) 
        {
            case 1:
                /*createContact function call*/
                createContact(&addressBook);
                break;
            case 2:
                /*searchContact function call*/
                searchContact(&addressBook);
                break;
            case 3:
                /*editContact function call*/
                editContact(&addressBook);
                break;
            case 4:
                /*deleteContact function call*/
                deleteContact(&addressBook);
                break;
            case 5:        
                /*listContacts function call*/  
                listContacts(&addressBook);
                break;
            case 6:
                /*saveandexit function call*/ 
                saveandexit(&addressBook);
                printf("Saving and exiting..");
                break;
            case 7:
                /*exiting addressbook*/
                printf("\nExiting addressbook");
                exit(0);
                /*default error message when invalid choice is entered*/
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);
    
       return 0;
}
