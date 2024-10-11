#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

int createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
int editContact(AddressBook *addressBook);
int deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveandexit(AddressBook *addressBook);



#endif
