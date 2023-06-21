// AddressBook.cpp

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>


using namespace std;

struct Contact {
    string firstName;
    string lastName;
    string home;
    string number;
};

Contact firstContact();
Contact nextContacts();
void prompt_and_execute(vector<Contact> &vect, bool *continue_updating);
void p_e_handler(vector<Contact> &vect, char command);
void makeNewContact(vector<Contact> &vect);
void placeNewContact(vector<Contact> &vect, Contact newContact);
void editContact(vector<Contact> &vect);
void Edit(vector<Contact> &vect, int index);
void deleteContact(vector<Contact> &vect);
void searchContacts(vector<Contact> &vect);
void alphabetizer(string fName, string nameHolder, bool *Seen, int *sameCheck);
Contact *find_contact(vector<Contact> &vect, string name, string lname, int *n);
void print_contacts(vector<Contact> &vect);
void print_one_Cont(vector<Contact> &vect, int index);
bool isValidChange(string changer);
void makeChange(vector<Contact> &vect, string changer, int index);
void fNameChanger(vector<Contact> &vect, int index);
void runSearch(vector<Contact> &vect, string changer);
void phoneSearch(vector<Contact> &vect, string changer);
void spaceDeterminer(string word);

int main()
{
    vector<Contact> vect;
    vect.push_back(firstContact());
    print_contacts(vect);

    //Ask the user for updates until they no longer have any
    bool continue_updating = true;

    while (continue_updating == true) {
        prompt_and_execute(vect, &continue_updating);
    }

    cout << "Thank you. Goodbye!" << endl;
    return 0;
}

Contact firstContact(){
    string fName, lName, home, number;
    cout << "Enter Your first and last Name: ";
    cin >> fName >> lName;
    cout << "Enter Your home location: ";
    cin >> home;
    cout << "Enter Your Phone Number: ";
    cin >> number;
    Contact Holder;
    Holder.firstName = fName;
    Holder.lastName = lName;
    Holder.home = home;
    Holder.number = number;
    return Holder;
}

Contact nextContacts(){
    string fName, lName, home, number;
    cout << "Enter first and last Name: ";
    cin >> fName >> lName;
    cout << "Enter home location: ";
    cin >> home;
    cout << "Enter Phone Number: ";
    cin >> number;
    Contact Holder;
    Holder.firstName = fName;
    Holder.lastName = lName;
    Holder.home = home;
    Holder.number = number;
    return Holder;
}

/*
 * Description: Ask the user for a name and number and query if it exists in the
 *              blackbook. If not, add the contact.
 * Input: The Contact array (aka a pointer to its first element), and
 *        the total size of that array
 * Output: Nothing returned, but potentially adds another contact to the
 *         blackbook.
 */
void prompt_and_execute(vector<Contact> &vect, bool *continue_updating)
{
    char command;
    cout << "What would you like to do?" << endl
         << "1. Add Contact" << endl
         << "2. Edit Contact" << endl
         << "3. Delete Contact" << endl
         << "4. View All Contacts" << endl
         << "5. Search Address Book" << endl
         << "6. Quit" << endl
         << "Please put your input here: ";
    cin >> command;
    if(command != '1' && command != '2' && command != '3' && command != '4'
       && command != '5' && command != '6'){
            cout << "Invalid input. Inputs are '1', '2', '3', '4', '5',or '6'.";
            cin.clear();  // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            // Ignore the remaining input
            prompt_and_execute(vect, continue_updating);
    }
    else if(command == '6'){
        *continue_updating = false;
        return;
    }
    else{
        p_e_handler(vect, command);
    }
}

void p_e_handler(vector<Contact> &vect, char command){
    if(command == '1'){
        makeNewContact(vect);
    }
    else if(command == '2'){
        editContact(vect);
    }else if(command == '3'){
        deleteContact(vect);
    }else if(command == '4'){
        print_contacts(vect);
    }else if(command == '5'){
        searchContacts(vect);
    }
}

void makeNewContact(vector<Contact> &vect){
    Contact newContact = nextContacts();
    placeNewContact(vect, newContact);
}

void placeNewContact(vector<Contact> &vect, Contact newContact){
    string nameHolder = newContact.firstName;
    int count = 0;
    int sameCheck = 0;
    bool Seen = false;
    for(std::vector<Contact>::size_type i = 0; i < vect.size(); i++){
        if(!Seen){
            string fName = vect[i].firstName;
            alphabetizer(fName, nameHolder, &Seen, &sameCheck);
            if(!Seen){
                count++;
            }
        }
    }
    if(sameCheck == 1){
        Seen = false;
        string lName = vect[count].lastName;
        nameHolder = newContact.lastName;
        alphabetizer(lName, nameHolder, &Seen, &sameCheck);
        if(!Seen){
            count++;
        }
    }
    vect.insert(vect.begin() + count, newContact);
}

void editContact(vector<Contact> &vect){
    string pName, givName;
    cout << "Which Contact would you like to edit?" <<
    " Please enter a first and last name: ";
    cin >> pName >> givName;
    int index;
    Contact *holder = find_contact(vect, pName, givName, &index);
    while(holder == nullptr){
        cout << "Not a valid contact. Enter a first and last name: ";
        cin >> pName >> givName;
        holder = find_contact(vect, pName, givName, &index);
    }
    Edit(vect, index);
}

void Edit(vector<Contact> &vect, int index){
    print_one_Cont(vect, index);
    string changer;
    cout << "Which index would you like to change? " << endl;
    cout << "1. Primary Name" << endl << "2. Last Name(s)" << endl
    << "3. Resident of" << endl << "4. Phone Number" << endl << "Index: ";
    cin >> changer;
    if(isValidChange(changer)){
        cout << "Enter a valid index('1', '2', '3', or '4': ";
        cin >> changer;
    }
    makeChange(vect, changer, index);
}

void deleteContact(vector<Contact> &vect){
    string pName, givName;
    cout << "Which Contact would you like to delete? " <<
    "Please enter a first and last name: ";
    cin >> pName >> givName;
    int index;
    Contact *holder = find_contact(vect, pName, givName, &index);
    while(holder == nullptr){
        cout << "Not a valid contact. Enter a first and last name: ";
        cin >> pName >> givName;
        holder = find_contact(vect, pName, givName, &index);
    }
    vect.erase(vect.begin() + index);
}

void searchContacts(vector<Contact> &vect){
    string changer;
    cout << "Which index would you like to search for? You can enter part of" 
    << " a contact as well." << endl;
    cout << "1. Primary Name" << endl << "2. Last Name(s)" << endl
    << "3. Resident of" << endl << "4. Phone Number" << endl << "Index: ";
    cin >> changer;
    if(isValidChange(changer)){
        cout << "Enter a valid index('1', '2', '3', or '4': ";
        cin >> changer;
    }
    runSearch(vect, changer);
}

void alphabetizer(string fName, string nameHolder, bool *Seen, int *sameCheck){
    if(fName.compare(nameHolder) < 0){
        return;
    }else if(fName.compare(nameHolder) == 0){
        *sameCheck = 1;
        *Seen = true;
    }else{
        *Seen = true;
    }
}

/*
 * Description: This function finds the contact that needs to be updated.
 *              If the provided name is already in the black book, it will
 *              return an existing contact. Otherwise it will return the
 *              first available blank entry in the black book.
 * Input: The Contact array (aka a pointer to its first element), the total
 *        size of that array, and the name that will be updated/added
 * Output: A pointer to the Contact that needs to be updated/added or
 *         nullptr if the black book is full
 */
Contact *find_contact(vector<Contact> &vect, string name, string lname, int *n)
{
    for(std::vector<Contact>::size_type i = 0; i < vect.size(); i++){
        if (vect[i].firstName == name && vect[i].lastName == lname){
            *n = i;
            return &vect[i];
        }
    }
    return nullptr;
}

//Print out the list of active contacts
void print_contacts(vector<Contact> &vect)
{
    cout << "Entry Number"
         << "                "
         << "Primary Name"
         << "                "
         << "Last Name(s)"
         << "                "
         << "Resident of"
         << "                "
         << "Phone Number" << endl;
 
    // Traversing vector
    for (std::vector<Contact>::size_type i = 0; i < vect.size(); i++) {
        cout << "     " << (i + 1) << "                      "
             << vect[i].firstName;
        spaceDeterminer(vect[i].firstName);
        cout << vect[i].lastName;
        spaceDeterminer(vect[i].lastName);
        cout << vect[i].home; 
        spaceDeterminer(vect[i].home);
        cout << vect[i].number << endl;
    }
}

void print_one_Cont(vector<Contact> &vect, int index){
    cout << "Entry Number" << "                " << "Primary Name"
         << "                " << "Last Name(s)" << "                "
         << "Resident of" << "                " << "Phone Number" << endl;
        cout << "     " << (index + 1) << "                      "
             << vect[index].firstName;
        spaceDeterminer(vect[index].firstName);
        cout << vect[index].lastName;
        spaceDeterminer(vect[index].lastName);
        cout << vect[index].home; 
        spaceDeterminer(vect[index].home);
        cout << vect[index].number << endl;
}

bool isValidChange(string changer){
    //true/false checks for column input correctness
    if(changer == "1" || changer == "2" || changer == "3" || changer == "4"){
        return false;
    }
    return true;
}

void makeChange(vector<Contact> &vect, string changer, int index){
    if(changer == "1"){
        fNameChanger(vect, index);
    }else if(changer == "2"){
        string lName;
        cout << "Please enter a new last name: ";
        cin >> lName;
        vect[index].lastName = lName;
    }else if(changer == "3"){
        string location;
        cout << "Please enter a new residence location: ";
        cin >> location;
        vect[index].home = location;
    }else{
        string phone;
        cout << "Please enter a new phone number: ";
        cin >> phone;
        vect[index].number = phone;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string Continue;
    cout << "Would you like to keep editing this contact(yes/no)?: ";
    cin >> Continue;
    if(Continue == "yes"){
        Edit(vect, index);
    }else{
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void fNameChanger(vector<Contact> &vect, int index){
    string fName;
    cout << "Please enter a new first name: ";
    cin >> fName;
    vect[index].firstName = fName;
    Contact holder = vect[index];
    vect.erase(vect.begin() + index);
    placeNewContact(vect, holder);
}

void runSearch(vector<Contact> &vect, string changer){
    if(changer == "1"){
        string fName;
        cout << "Please enter a first name: ";
        cin >> fName;
        for(std::vector<Contact>::size_type i = 0; i < vect.size(); i++){
            if(!vect[i].firstName.find(fName)){
                print_one_Cont(vect, i);
            }
        }
    }else if(changer == "2"){
        string lName;
        cout << "Please enter a last name: ";
        cin >> lName;
        for(std::vector<Contact>::size_type i = 0; i < vect.size(); i++){
            if(!vect[i].lastName.find(lName)){
                print_one_Cont(vect, i);
            }
        }
    }else if(changer == "3"){
        string location;
        cout << "Please enter a residence location: ";
        cin >> location;
        for(std::vector<Contact>::size_type i = 0; i < vect.size(); i++){
            if(!vect[i].home.find(location)){
                print_one_Cont(vect, i);
            }
        }
    }
    phoneSearch(vect, changer);
}

void phoneSearch(vector<Contact> &vect, string changer){
    if(changer == "4"){
        string phone;
        cout << "Please enter a new phone number: ";
        cin >> phone;
        for(std::vector<Contact>::size_type i = 0; i < vect.size(); i++){
            if(!vect[i].number.find(phone)){
                print_one_Cont(vect, i);
            }
        }
    }
}


void spaceDeterminer(string word){
    int length = 28 - word.length();
    for(int i = 0; i < length; i++){
        cout << " ";
    }
}
