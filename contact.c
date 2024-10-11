#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "contact.h"
//#include "file.h"
#include "populate.h"

/*List contact function*/
void listContacts(AddressBook *addressBook) 
{
    /*Printing heading of the list of contacts i.e name,phone number,email*/
    printf("S.no\tName\t\tPhone number\tEmail\n");
    printf("\033[1;32m");
    /*for loop to print the all the name,phone number and email*/
    for(int i=0;i<addressBook->contactCount;i++)
    {
        
        printf("%d.\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("\033[0m");
}

/*intialization function */
void initialize(AddressBook *addressBook) 
{
    /*intializing contactcount with zero value*/
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
    /*creating the structure containing array of name,phone and email*/
    struct dummy 
    {
        char name[50];
        char phone[20];
        char email[50];
    };
    struct dummy arr;
    /*opening the text file containing contacts in read mode*/
    FILE *fptr=fopen("contact.txt","r");
    /*if there is no file print error message*/
    if(fptr==NULL)
    {
        printf("No file found\n");
        return ;
    }
    /*read the name, phone number and email from the file*/
    while((fscanf(fptr,"%[^,],%[^,],%[^\n]\n",arr.name,arr.phone,arr.email))==3)
    {
        /*copying the contact deatil from the file to array Contacts */
        if(addressBook->contactCount<MAX_CONTACTS)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,arr.name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone,arr.phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email,arr.email);
            addressBook->contactCount++;
        }
    }
    /*close the file*/
    fclose(fptr);

}

/*saveandexit function*/
void saveandexit(AddressBook *addressBook)
{
    /*opening contact.txt file*/
    FILE *fptr=fopen("contact.txt","w");
    /*print the contact details in file from contacts array using loop*/
    for (int i = 0; i <  addressBook->contactCount && addressBook->contactCount < MAX_CONTACTS; ++i)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    /*close the file*/
    fclose(fptr);
}

/*createContact function */
int createContact(AddressBook *addressBook)
{
    /*declaring seperate array for name,phone number and email for validating*/
    char name1[50];
    char phone1[20];
    char email1[50];
    /*declaring the flag variables*/
    int flag_1=0,flag_2=0,flag_3=0;
    /*prompt message to enter the name*/
	printf("Enter the name:\n");
    /*reading name input from the user*/
    scanf("%[^\n]",name1);
    getchar();
    /*prompt message to enter the phone number*/
    printf("Enter the phone number:\n");
    /*reading phone number input from the user*/
    scanf("%[^\n]",phone1);
    getchar();
    /*prompt message to enter the email*/
    printf("Enter the email:\n");
    /*reading email input from the user*/
    scanf("%[^\n]",email1);
    getchar();
    printf("\033[1;31m");
    /*for loop to compare the name input obtained from the user with all the name present in the addressBook array*/
    for(int i=0;i<addressBook->contactCount;i++)
    {
        /*condtion to check whether input name is present in array or not*/
        if(strcmp(addressBook->contacts[i].name,name1)==0)
        {
            /*Error prompt message if name already exists*/
            printf("Name already exist");
            /*return back to main function*/
            return 1;
        }
    }
    /*updating the flag_1 if name is created successfully*/
    flag_1=1;
    /*checking whether the entered number from user has length 10 or not*/
    if(strlen(phone1)!=10)
    {
        /*error message when length is not equal to 10*/
        printf("Invalid number");
        return 1;
    }
    else
    {
        /*for loop to compare the phone number input with all the name present in the addressBook array*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            /*condition to check whether all the digits in the phone number lie between 0-9*/
            if(phone1[i] >= '0' || phone1[i] <= '9')
            {
                /*condtion to check whether input phone number is present in array or not*/
                if(strcmp(addressBook->contacts[i].phone,phone1)==0)
                {
                    /*printing error message if phone number alredy present*/
                    printf("phone number already exists");
                    return 1;
                }
            }
            else
            {
                /*error message if individual digit doesn't lie between 0-9*/
                printf("Invalid number enter only digits");
                return 1;
            }
        }
    }
    /*updating the flag_1 if phone number is created successfully*/
    flag_2=1;
    /*declaring variables ch with @ present in it*/
    char ch='@';
    /*declaring string str with .com present in it*/
    char str[]=".com";
    /*declaring and initializing the cond variable with zero*/
    int cond=0;
    /*loop to check whether @ and .com are together or not*/
    for(int j=0;email1[j]!=0;j++)
    {
        if(email1[j]=='@')
        {
            if(email1[j+1]=='.' || email1[j-1]=='m')
            {
                /*updating cond flag to indicate @ and .com are together*/
                cond=1;
            }
        }
    }
    /*condition to check whether flag cond is not equal to 1*/
    if(cond!=1)
    {
        /*loop to compare input email is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            /*condition to check whether character @ is present in input or not*/
            if(strchr(email1,ch)!=NULL)
            {
                /*condtion to check whether string .com is present in the input or not*/
                if(strstr(email1,str)!=NULL)
                {
                    /*condition to check whether @ is present at zeroth index or not*/
                    if(email1[0]!='@')
                    {
                        /*condition to check whether input email is already present in addressbook or not */
                        if(strcmp(addressBook->contacts[i].email,email1)==0)
                        {
                            /*printing error if email alredy present*/
                            printf("Email already exists.Try again!");
                            return 1;
                        }
                    }
                    else
                    {
                        /*printing error if @ is present at zeroth index and returning to main menu*/
                        printf("Invalid email.Any character other than @ should be used at first index");
                        return 1;
                    }
                }
                else
                {
                    /*printing error if string '.com' is not present in the input and returning to main menu*/
                    printf("Email is invalid! .com should be present");
                    return 1;
                }
            }
            else
            {
                /*printing error if character '@' is not present in the input and returning to main menu*/
                printf("Email is invalid! @ should be present");
                return 1;
            }
        }
    }
    else
    {
         /*printing error message if @ and .com are together and returning to main menu*/
        printf("Invalid email! after or before @ any character should be mentioned");
        return 1;
    }
    printf("\033[0m");
    /*updating the flag_1 if name is created successfully*/
    flag_3=1;
    /*if condition to check whether all the flags equal to 1*/
    if(flag_1==1 && flag_2==1 && flag_3==1)
    {
        /*copying the name,phone number and email to the adddressbook array*/
        strcpy(addressBook->contacts[addressBook->contactCount].name,name1);
        strcpy(addressBook->contacts[addressBook->contactCount].phone,phone1);
        strcpy(addressBook->contacts[addressBook->contactCount].email,email1);
        /*incrementing contactCount*/
        addressBook->contactCount++;
        printf("\033[1;33m");
        printf("Contact saved successfully");
        printf("\033[0m");
    }

}


/*searchContact function*/
int searchContact(AddressBook *addressBook) 
{
    /*declaring the variable*/
    int c;
    /*prompting the search menu*/
    printf("Search menu:\n");
    printf("1.search by name\n");
    printf("2.search by phone number\n");
    printf("3.search by email id\n");
    printf("Enter your choice: ");
    /*read choice from the user*/
    scanf("%d",&c);
    getchar();
    /*declaring flag and array*/
    int flag=0;
    char arr[50];
    /*if condtion when choice is 1*/
    if(c==1)
    {
        /*prompt message to enter the name*/
        printf("Enter the name:");
        /*read input from the user*/
        scanf("%[^\n]",arr);
        getchar();
        printf("\033[1;32m");
        /*loop to compare input name is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            /*condtion to check whether input name is present in array or not*/
            if(strcasestr(addressBook->contacts[i].name,arr)!=NULL)
                {
                    /*printing name, phonr number and email of searched name*/
                    printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag=1;
                }
        }
        printf("\033[0m");
        if(flag==0)
        {
            printf("\033[1;31m");
            /*error message if name not found and return to main menu*/
            printf("Contact not found!");
            printf("\033[0m");
            return 1;
        }
        else
        {
            /*return to main menu*/
            return 1;
        }
    }
    /*if condtion when choice is 2*/
    else if(c==2)
    {
        /*prompt message to enter the phone number*/
        printf("Enter the phone number:");
        /*read input from the user*/
        scanf("%[^\n]",arr);
        /*loop to compare input phone number is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("\033[1;32m");
            /*condtion to check whether input phone number is present in array or not*/
            if(strcasestr(addressBook->contacts[i].phone,arr)!=NULL)
            {
                /*printing name, phone number and email of searched phone number*/
                printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag=1;
            }
        }
        printf("\033[0m");
        if(flag==0)
        {
            /*error message if phone number not found and return to main menu*/
            printf("Contact not found!");
            return 1;
        }
        else
        {
            /*return to main menu*/
            return 1;
        }
    }
    /*if condtion when choice is 3*/
    else if(c==3)
    {
        /*prompt message to enter the email*/
        printf("Enter the email:");
        /*read input from the user*/
        scanf("%[^\n]",arr);
        /*loop to compare input email is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("\033[1;32m");
            /*condtion to check whether input email is present in array or not*/
            if(strcasestr(addressBook->contacts[i].email,arr)!=NULL)
                {
                    /*printing name, phonr number and email of searched email*/
                    printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag=1;
                }
        }
        printf("\033[0m");
        printf("\033[1;31m");
        if(flag==0)
        {
            /*error message if email not found and return to main menu*/
            printf("Contact not found!");
            return 1;
        }
        else
        {
            /*return to main menu*/
            return 1;
        }
    }
    else
    {
        /*printing error message if choice is invalid and return to main menu*/
        printf("Invalid choice\n");
        return 1;
    }
    printf("\033[0m");
}

/*editcontact function*/
int editContact(AddressBook *addressBook)
{
    /*declaring variable x*/
	int x;
    /*prompt menu to search the menu*/
    printf("Menu:\n");
    printf("1.search by name\n");
    printf("2.search by email id\n");
    printf("Enter your choice: ");
    /*read choice*/
    scanf("%d",&x);
    getchar();
    /*declaring character array*/
    char arr[50];

    /*if entered choice is 1*/
    if(x==1)
    {
        /*declaring flag variables flag */
        int flag=0;
        int sub[100];
        /*prompt message to enter the name to be searched*/
        printf("Enter the name:");
        /*read name*/
        scanf("%[^\n]",arr);
        getchar();
        /*declaring flag*/
        int f=0,flag2=0;
        int k=0;
        printf("\033[1;32m");
        /*loop to compare input name is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            /*condtion to check whether input name is present in array or not*/
            if(strcasestr(addressBook->contacts[i].name,arr)!=NULL)
            {
                /*printing name, phonr number and email of searched name*/
                printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sub[k++]=i+1;
                f=1;
            }
            
        }
        printf("\033[0m");
        if(f==0)
        {
            printf("\033[1;31m");
            /*error message if name not found and return to main menu*/
            printf("Contact not found!");
            printf("\033[0m");
            return 1;
        }
        /*declaring index and i variable*/
        int index,i;
        /*prompt message to enter the index*/
        printf("Select the index of the name: ");
        /*read the index*/
        scanf("%d",&index);
        getchar();
        /*assigning index value to i*/
        i=index-1;

        /*loop to check the index is valid or not*/
        for(int i=0;i<k;i++)
        {
            if(sub[i]==index)
            {
                /*if index is valid update the flag*/
                flag2=1;
                break;
            }
        }

        if(flag2==1)
        {   
            /*do while loop to edit the contact searched using name*/
            do
            {
                /*declaing variable y*/
                int y;
                /*prompt menu to edit the contact*/
                printf("Edit Menu:\n");
                printf("1.Edit name\n");
                printf("2.Edit Phone number\n");
                printf("3.Edit email id\n");
                /*prompt message to enter the choice*/
                printf("Enter your choice: ");
                /*read choice from user*/
                scanf("%d",&y);
                getchar();

                /*if entered choice is 1*/
                if(y==1)
                {
                    /*declaring array name1*/
                    char name1[50];
                    /*prompt message to enter the edited name*/
	                printf("Enter the edit name:\n");
                    /*read the name*/
                    scanf("%[^\n]",name1);
                    getchar();
                    /*loop to validate the eneterd name*/
                    for(int j=0;j<addressBook->contactCount;j++)
                    {
                        /*condition to check whether the name is present in contacts array or not*/
                        if(strcmp(addressBook->contacts[j].name,name1)==0)
                        {
                            printf("\033[1;31m");
                            /*if yes print error message*/
                            printf("Name already exist!!");
                            printf("\033[0m");
                            /*update the flag*/
                            flag=1;
                            break;
                        }
                    }   

                    /*if flag is zero name is not found in the array*/ 
                    if (flag == 0)
                    {
                        /*replace the name with edited name*/
                        strcpy(addressBook->contacts[i].name, name1);
                        /*print message that name updated succcessfully*/
                        printf("\033[1;33m");
                        printf("Name updated successfully.\n");
                        printf("\033[0m");
                    }
                }

                /*if entered choice is 2*/
                else if(y==2)
                {
                    /*declaring array phone1*/
                    char phone1[20];
                    /*prompt message to enter the edited phone number*/
                    printf("Enter the phone number:\n");
                    /*read the phone number*/
                    scanf("%[^\n]",phone1);
                    getchar();
                    /*check whether the number conatains 10 digit or not*/
                    if(strlen(phone1)!=10)
                    {
                        printf("\033[1;31m");
                        /*error message when length is not equal to 10*/
                        printf("Invalid number");
                        printf("\033[0m");
                        /*update the flag*/
                        flag=1;
                        break;
                    }
                    else
                    {
                        /*for loop to compare the phone number input with all the name present in the addressBook array*/
                        for(int j=0;j<addressBook->contactCount;j++)
                        {
                            /*condition to check whether all the digits in the phone number lie between 0-9*/
                            if(phone1[j]>=0 || phone1[j]<=9)
                            {
                                /*condtion to check whether input phone number is present in array or not*/
                                if(strcmp(addressBook->contacts[j].phone,phone1)==0)
                                {
                                    printf("\033[1;31m");
                                    /*printing error message if phone number alredy present*/
                                    printf("phone number already exists");
                                    /*update the flag*/
                                    flag=1;
                                    break;
                                }
                            }
                            else
                            {
                                /*error message if individual digit doesn't lie between 0-9*/
                                printf("Invalid number enter only digits");
                                printf("\033[0m");
                                flag=1;
                                break;
                            }
                        }
                    }
                    /*if flag is not updated copy the edited phone number to the array*/
                    if (flag==0)
                    {    
                        printf("\033[1;33m");
                        strcpy(addressBook->contacts[i].phone, phone1);
                        printf("Phone number updated successfully.\n");
                        printf("\033[0m");
                    }
                }

                /*if choice eneterd is 3*/
                else if(y==3)
                {
                    /*declaring email1 array*/
                    char email1[50];
                    /*prompt message to  enter the edited email*/
                    printf("Enter the email:\n");
                    /*read email*/
                    scanf("%[^\n]",email1);
                    getchar();
                    /*declaring variables*/
                    char ch='@';
                    char str[]=".com";
                    /*declaring count variable*/
                    int cond=0;
                    /*loop to check whether @ and .com are together or not*/
                    for(int j=0;email1[j]!=0;j++)
                    {
                        /*check the presence of @*/
                        if(email1[j]=='@')
                        {
                            if(email1[j+1]=='.')
                            {
                                /*updating cond flag to indicate @ and .com are together*/
                                cond=1;
                            }
                        }
                    }
                    /*condition to check whether flag cond is not equal to 1*/
                    if(cond!=1)
                    {
                        /*loop to compare input email is already present in addressbook or not*/
                        for(int j=0;j<addressBook->contactCount;j++)
                        {
                            /*condition to check whether character @ is present in input or not*/
                            if(strchr(addressBook->contacts[j].email,ch)!=NULL)
                            {
                                /*condtion to check whether string .com is present in the input or not*/
                                if(strstr(email1,str)!=NULL)
                                {
                                    /*condition to check whether input email is already present in addressbook or not */
                                    if(strcmp(addressBook->contacts[j].email,email1)==0)
                                    {
                                        printf("\033[1;33m");
                                        /*printing error if email alredy present*/
                                        printf("Email already exists.Try again!");
                                        flag=1;
                                        break;
                                    }
                                }
                                else
                                {
                                    /*printing error if @ is present at zeroth index*/
                                    printf("Email is invalid");
                                    flag=1;
                                    break;
                                }
                            }
                            else
                            {
                                /*printing error if character '@' is not present in the input*/
                                printf("Email is invalid. @ should be present");
                                flag=1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        /*printing error message if @ and .com are together*/
                        printf("Invalid email. after @ any character should be mentioned");
                        printf("\033[0m");
                        flag=1;
                        break;
                    }
                    if(flag==0)
                    {
                        /*copying email if it satisfies all validation*/
                        strcpy(addressBook->contacts[i].email, email1);
                        printf("\033[1;33m");
                        printf("Email updated successfully.\n");
                        printf("\033[0m");
                    }
                }
            }while(flag==1);
        }
        if(flag2==0)
        {
            printf("\033[1;33m");
            printf("Invalid index");
            printf("\033[0m");
            return 1;
        }   
    }

    /*if entered choice is 2*/
    else if(x==2)
    {
       /*declaring flag variables flag and found*/
        int flag=0;
        /*prompt message to enter the name to be searched*/
        printf("Enter the email:");
        /*read name*/
        scanf("%[^\n]",arr);
        getchar();
        int sub[100];
        int f=0,k=0;
        /*loop to compare input name is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("\033[1;32m");
            /*condtion to check whether input name is present in array or not*/
            if(strcasestr(addressBook->contacts[i].email,arr)!=NULL)
            {
                /*printing name, phonr number and email of searched name*/
                printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sub[k++]=i+1;
                f=1;
            }    
        }
        printf("\033[0m");
        if(f==0)
        {
            printf("\033[1;31m");
            /*error message if name not found and return to main menu*/
            printf("Contact not found!");
            printf("\033[0m");
            return 1;
        }
        /*declaring index and i variable*/
        int index,i,flag2=0;
        /*prompt message to enter the index*/
        printf("Select the index of the name: ");
        /*read the index*/
        scanf("%d",&index);
        /*assigning index value to i*/
        i=index-1;

        /*loop to check the index is valid or not*/
        for(int i=0;i<k;i++)
        {
            if(sub[i]==index)
            {
                /*if index is valid update the flag*/
                flag2=1;
                break;
            }
        }
        
        /*if flag2 is 1 edit the contact*/
        if(flag2==1)
        {   
            do
            {
                /*declaing variable y*/
                int y;
                /*prompt menu to edit the contact*/
                printf("Edit Menu:\n");
                printf("1.Edit name\n");
                printf("2.Edit Phone number\n");
                printf("3.Edit email id\n");
                /*prompt message to enter the choice*/
                printf("Enter your choice: ");
                /*read choice from user*/
                scanf("%d",&y);
                getchar();

                /*if entered choice is 1*/
                if(y==1)
                {
                    /*declaring array name1*/
                    char name1[50];
                    /*prompt message to enter the edited name*/
	                printf("Enter the edit name:\n");
                    /*read the name*/
                    scanf("%[^\n]",name1);
                    getchar();
                    /*loop to validate the eneterd name*/
                    for(int j=0;j<addressBook->contactCount;j++)
                    {
                        /*condition to check whether the name is present in contacts array or not*/
                        if(strcmp(addressBook->contacts[j].name,name1)==0)
                        {
                            printf("\033[1;31m");
                            /*if yes print error message*/
                            printf("Name already exist");
                            printf("\033[0m");
                            /*update the flag*/
                            flag=1;
                            break;
                        }
                    }

                    /*if flag is zero name is not found in the array*/
                    if (flag == 0)
                    {
                        /*replace the name with edited name*/
                        strcpy(addressBook->contacts[i].name, name1);
                        /*print message that name updated succcessfully*/
                        printf("\033[1;33m");
                        printf("Name updated successfully.\n");
                        printf("\033[0m");
                    }
                }

                /*if entered choice is 2*/
                else if(y==2)
                {
                    /*declaring array phone1*/
                    char phone1[20];
                    /*prompt message to enter the edited phone number*/
                    printf("Enter the phone number:\n");
                    /*read the phone number*/
                    scanf("%[^\n]",phone1);
                    getchar();
                    /*check whether the number conatains 10 digit or not*/
                    if(strlen(phone1)!=10)
                    {
                        /*error message when length is not equal to 10*/
                        printf("\033[1;31m");
                        printf("Invalid number");
                        /*update the flag*/
                        flag=1;
                        break;
                    }
                    else
                    {
                        /*for loop to compare the phone number input with all the name present in the addressBook array*/
                        for(int j=0;j<addressBook->contactCount;j++)
                        {
                            /*condition to check whether all the digits in the phone number lie between 0-9*/
                            if(phone1[j]>=0 || phone1[j]<=9)
                            {
                                /*condtion to check whether input phone number is present in array or not*/
                                if(strcmp(addressBook->contacts[j].phone,phone1)==0)
                                {
                                    /*printing error message if phone number alredy present*/
                                    printf("phone number already exists");
                                    /*update the flag*/
                                    flag=1;
                                    break;
                                }
                            }
                            else
                            {
                                /*error message if individual digit doesn't lie between 0-9*/
                                printf("Invalid number enter only digits");
                                printf("\033[0m");
                                flag=1;
                                break;
                            }
                        }
                    }
                    /*if flag is not updated copy the edited phone number to the array*/
                    if (flag==0)
                    {
                        /*copying*/
                        strcpy(addressBook->contacts[i].phone, phone1);
                        printf("\033[1;33m");
                        printf("Phone number updated successfully.\n");
                        printf("\033[0m");
                    }
                }

                /*if choice eneterd is 3*/
                else if(y==3)
                {
                    /*declaring email1 array*/
                    char email1[50];
                    /*prompt message to  enter the edited email*/
                    printf("Enter the email:\n");
                    /*read email*/
                    scanf("%[^\n]",email1);
                    getchar();
                   /*declaring variables*/
                   char ch='@';
                   char str[]=".com";
                   /*declaring count variable*/
                   int cond=0;
                   /*loop to check whether @ and .com are together or not*/
                   for(int j=0;email1[j]!=0;j++)
                    {
                        /*check the presence of @*/
                        if(email1[j]=='@')
                        {
                            if(email1[j+1]=='.')
                            {
                                /*updating cond flag to indicate @ and .com are together*/
                                cond=1;
                            }
                        }
                    }
                    /*condition to check whether flag cond is not equal to 1*/
                    if(cond!=1)
                    {
                        /*loop to compare input email is already present in addressbook or not*/
                        for(int j=0;j<addressBook->contactCount;j++)
                        {
                            /*condition to check whether character @ is present in input or not*/
                            if(strchr(addressBook->contacts[j].email,ch)!=NULL)
                            {
                                /*condtion to check whether string .com is present in the input or not*/
                                if(strstr(email1,str)!=NULL)
                                {
                                    printf("\033[1;31m");
                                    /*condition to check whether input email is already present in addressbook or not */
                                    if(strcmp(addressBook->contacts[j].email,email1)==0)
                                    {
                                        /*printing error if email alredy present*/
                                        printf("Email already exists.Try again!");
                                        flag=1;
                                        break;
                                    }
                                }
                                else
                                {
                                    /*printing error if @ is present at zeroth index*/
                                    printf("Email is invalid");
                                    flag=1;
                                    break;
                                }
                            }
                            else
                            {
                                /*printing error if character '@' is not present in the input*/
                                printf("Email is invalid. @ should be present");
                                flag=1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        /*printing error message if @ and .com are together*/
                        printf("Invalid email. after @ any character should be mentioned");
                        printf("\033[0m");
                        flag=1;
                        break;
                    }
                    if(flag==0)
                    {
                        /*copying email if it satisfies all validation*/
                        strcpy(addressBook->contacts[i].email, email1);
                        printf("\033[1;33m");
                        printf("Email updated successfully.\n");
                        printf("\033[0m");
                    }
                }
            }while(flag==1);
        }
        if(flag2==0)
        {
            printf("\033[1;31m");
            printf("Invalid index");
            printf("\033[0m");
            return 1;
        }                  
    }
}           


/*deletecount function*/
int deleteContact(AddressBook *addressBook)
{
    /*declaring the variable*/
    int d;
    /*prompting delete menu*/
    printf("Delete menu:\n");
    printf("1. Delete by searching name\n");
    printf("2. Delete by searching phone number\n");
    printf("3. Delete by searching email id\n");
    /*prompt message to enter the choice*/
    printf("Enter your choice: ");
    /*read choice from the user*/
    scanf("%d", &d);
    getchar(); 
    /*declaring flag and string variable*/
    int flag = 0;
    char arr[50];
    /*condition to check whether choice is 1*/
    if (d == 1) 
    {
        /*prompt message to enter the name to be deleted*/
        printf("Enter the name: ");
        /*read the name*/
        scanf("%[^\n]",arr);
        getchar();
        int sub[100];
        int f=0,k=0;
        /*loop to compare input name is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("\033[1;32m");
            /*condtion to check whether input name is present in array or not*/
            if(strcasestr(addressBook->contacts[i].name,arr)!=NULL)
            {
                /*printing name, phonr number and email of searched name*/
                printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sub[k++]=i+1;
                f=1;
            }
        }
        printf("\033[0m");
        if(f==0)
        {
            /*error message if name not found and return to main menu*/
            printf("\033[1;31m");
            printf("Contact not found!");
            printf("\033[0m");
            return 1;
        }
       /*declaring index and i variable*/
        int index,i,flag2=0;
        /*prompt message to enter the index*/
        printf("Select the index of the name: ");
        /*read the index*/
        scanf("%d",&index);
        /*assigning index value to i*/
        i=index-1;
        
        /*loop to check the index is valid or not*/
        for(int i=0;i<k;i++)
        {
            if(sub[i]==index)
            {
                /*if index is valid update the flag*/
                flag2=1;
                break;
            }
        }

        /*if flag2 is 1 delete the contact*/
        if(flag2==1)
        { 
            /*if the name is found in the array delete the whole contact and copy next contact in place of that contact*/
            for (int j = i; j < addressBook->contactCount - 1; j++) 
            {
                strcpy(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                strcpy(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
                strcpy(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            }
            /*decrement the count*/
            addressBook->contactCount--;
            printf("\033[1;33m");
            printf("Contact deleted successfully!!");
            printf("\033[0m");
        }
        if(flag2==0)
        {
            printf("\033[1;31m");
            printf("Invalid index");
            printf("\033[0m");
            return 1;
        } 
    }

    /*condition to check whether choice is 2*/ 
    else if (d == 2) 
    {
        /*prompt message to enter the phone number to be deleted*/
        printf("Enter the phone number: ");
        /*read the phone number*/
        scanf("%[^\n]", arr);
        int f=0,k=0;
        int sub[100];
        /*loop to compare input name is already present in addressbook or not*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("\033[1;32m");
            /*condtion to check whether input name is present in array or not*/
            if(strcasestr(addressBook->contacts[i].phone,arr)!=NULL)
            {
                /*printing name, phonr number and email of searched name*/
                printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sub[k++]=i+1;
                f=1;
            }
        }
        printf("\033[0m");
        if(f==0)
        {
            /*error message if name not found and return to main menu*/
            printf("\033[1;33m");
            printf("Contact not found!");
            printf("\033[0m");
            return 1;
        }
        /*declaring index and i variable*/
        int index,i,flag2=0;
        /*prompt message to enter the index*/
        printf("Select the index of the name: ");
        /*read the index*/
        scanf("%d",&index);
        /*assigning index value to i*/
        i=index-1;
        
        /*loop to check the index is valid or not*/
        for(int i=0;i<k;i++)
        {
            if(sub[i]==index)
            {
                /*if index is valid update the flag*/
                flag2=1;
                break;
            }
        }

        if(flag2==1)
        {  
            /*if the phone number is found in the array delete the whole contact and copy next contact in place of that contact*/
            for (int j = i; j < addressBook->contactCount - 1; j++) 
            {
                strcpy(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                strcpy(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
                strcpy(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            }
            /*decrement the count*/
            addressBook->contactCount--;
            printf("\033[1;33m");
            printf("Contact deleted successfully!!");
            printf("\033[0m");
        }
        if(flag2==0)
        {
            printf("\033[1;31m");
            printf("Invalid index");
            printf("\033[0m");
            return 1;
        }        
    }

    /*condition to check whether choice is 2*/
    else if (d == 3) 
    {
        /*prompt message to enter the email to be deleted*/
        printf("Enter the email: ");
        /*read the email*/
        scanf("%[^\n]", arr);
        int f=0,k=0;
        int sub[100];
        /*loop to compare input name is already present in addressbook or not*/
        printf("\033[1;32m");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            /*condtion to check whether input name is present in array or not*/
            if(strcasestr(addressBook->contacts[i].email,arr)!=NULL)
            {
                /*printing name, phonr number and email of searched name*/
                printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sub[k++]=i+1;
                f=1;
            }
        }
        printf("\033[0m");
        if(f==0)
        {
            /*error message if name not found and return to main menu*/
            printf("Contact not found!");
            return 1;
        }
        /*declaring index and i variable*/
        int index,i,flag2=0;
        /*prompt message to enter the index*/
        printf("Select the index of the name: ");
        /*read the index*/
        scanf("%d",&index);
        /*assigning index value to i*/
        i=index-1;
        
        /*loop to check the index is valid or not*/
        for(int i=0;i<k;i++)
        {
            if(sub[i]==index)
            {
                /*if index is valid update the flag*/
                flag2=1;
                break;
            }
        }

        if(flag2==1)
        {   
            /*if the phone number is found in the array delete the whole contact and copy next contact in place of that contact*/
            for (int j = i; j < addressBook->contactCount - 1; j++) 
            {
                strcpy(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                strcpy(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
                strcpy(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            }
            /*decrement the count*/
            addressBook->contactCount--;
            printf("\033[1;33m");
            printf("Contact deleted successfully!!");
            printf("\033[0m");
        }
        if(flag2==0)
        {
            printf("\033[1;31m");
            printf("Invalid index");
            printf("\033[0m");
            return 1;
        } 
                
    }
}