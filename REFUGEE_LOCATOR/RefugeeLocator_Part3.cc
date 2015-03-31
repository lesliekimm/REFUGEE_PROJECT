/**
 *
 * Project 5
 * Refugee Locator
 * Leslie Kim
 * NetID: lk584
 * COSC 051
 * Section 02
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance on
 * this project with the exceptions of lecture notes and those items
 * listed below.
 * Any help items:
 * Description <This program will assist in finding separated refugees
 * by searching through data files that contain the name, gender, age
 * and camp name of refugees. Users will be permitted to load as many
 * files as they want. Each file contains the first and last name (UNK
 * for unknown names), gender, age and camp of each refugee. Users will
 * be able to search for refugees by name or age and gender, list all
 * refugees at a camp, get a count of total refugees and print all
 * information about refugees.>
 *
 **/

#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;

// FUNCTION PROTOTYPES
char selectMenuOption();

// CLASSES
// Refugee class
class Refugee {

  friend istream &operator>>(istream &, Refugee &);
  friend ostream &operator<<(ostream &, Refugee);

public:
  Refugee();
  Refugee(string, string, char, int, string);
  string getFirst();
  void setFirst(string);
  string getLast();
  void setLast(string);
  char getGender();
  void setGender(char);
  int getAge();
  void setAge(int);
  string getCampName();
  void setCampName(string);
  string nameMatch(string, string);
  bool ageMatch(int, char);
  bool goodRefugeeData();
  Refugee * getNextRefugee();
  void setNextRefugee(Refugee *);

private:
  string firstName;
  string lastName;
  char gender;
  int age;
  string campName;
  bool dataGood;
  Refugee * nextRefugee;
};

// Overloading >> operator for reading in new Refugee
istream &operator>>(istream & input, Refugee & newRefugee) {
  input >> newRefugee.firstName >> newRefugee.lastName >> newRefugee.gender
	>> newRefugee.age >> newRefugee.campName;
  return input;
}

// Overloading << operator for output new Refugee with formatting
ostream &operator<<(ostream & output, Refugee newRefugee) {
  output << left << setw(25) << newRefugee.firstName << setw(25) << newRefugee.lastName
	 << setw(10) << newRefugee.gender << setw(5) << newRefugee.age << setw(15)
	 << newRefugee.campName;
  return output;
}

// Create empty refugee object
Refugee::Refugee() {
  firstName = "";
  lastName = "";
  gender = ' ';
  age = 0;
  campName = "";
  dataGood = false;
  nextRefugee = NULL;
}

// Refugee object takes input - error checks in Operation class
Refugee::Refugee(string inputFirstName, string inputLastName, char inputGender,
		 int inputAge, string inputCampName) {
  firstName = inputFirstName;
  lastName = inputLastName;
  gender = inputGender;
  age = inputAge;
  campName = inputCampName;
  dataGood = false;
  nextRefugee = NULL;
}

// Returns Refugee's first name
string Refugee::getFirst() {
  return firstName;
}

// Sets Refugee's first name
void Refugee::setFirst(string inputFirstName) {
  firstName = inputFirstName;
}

// Returns Refugee's last name
string Refugee::getLast() {
  return lastName;
}

// Sets Refugee's last name
void Refugee::setLast(string inputLastName) {
  lastName = inputLastName;
}

// Returns Refugee's gender
char Refugee::getGender() {
  return gender;
}

// Set's Refugee's gender with error check
void Refugee::setGender(char inputGender) {
  gender = inputGender;
  dataGood = false;

  switch(gender) {
  case 'M':
  case 'm':
    gender = 'M';
    dataGood = true;
    break;
  case 'F':
  case 'f':
    gender = 'F';
    dataGood = true;
    break;
  default:
    cout << "ERROR: " << firstName << " " << lastName << "'s gender is not valid."
	 << endl;
    break;
  }
}

// Returns Refugee's age
int Refugee::getAge() {
  return age;
}

// Sets Refugee's age with error check
void Refugee::setAge(int inputAge) {
  age = inputAge;
  dataGood = false;

  const int minAge = 0;
  const int maxAge = 120; // oldest current living person is 116 years old

  if ((age < minAge) || (age > maxAge)) {
    cout << "ERROR: " << firstName << " " << lastName << "'s age of " << age
	 << " is out of range." << endl;
  }
  else {
    dataGood = true;
  }
}

// Returns Refugee's camp name
string Refugee::getCampName() {
  return campName;
}

// Sets Refugee's camp name
void Refugee::setCampName(string inputCampName) {
  campName = inputCampName;
}

// Performs search for Refugee by name
string Refugee::nameMatch(string inputFirstName, string inputLastName) {
  if ((inputFirstName == firstName) && (inputLastName == lastName)) {
    return "Exact";
  }
  else if ((inputFirstName == firstName) && (inputLastName != lastName)) {
    return "First";
  }
  else if ((inputFirstName != firstName) && (inputLastName == lastName)) {
    return "Last";
  }
  else {
    return "None";
  }
}

// Performs search for refugees by age and gender
bool Refugee::ageMatch(int inputAge, char inputGender) {
  int inputMinAge = inputAge - 1;
  int inputMaxAge = inputAge + 1;
  dataGood = false;

  const int minAge = 0;
  const int maxAge = 120; // oldest current living person is 116 years old

  if ((inputAge < minAge) || (inputAge > maxAge)) {
    cout << "ERROR: The age " << inputAge << " is out of range." << endl;
  }

  switch(inputGender) {
  case 'M':
  case 'm':
    inputGender = 'M';
    dataGood = true;
    break;
  case 'F':
  case 'f':
    inputGender = 'F';
    dataGood = true;
    break;
  default:
    break;
  }

  // Checks for refugees of inputAge within +/- 1 year and inputGender
  if ((age >= inputMinAge) && (age <= inputMaxAge) && (gender == inputGender)) {
    dataGood = true;
  }
  else {
    dataGood = false;
  }

  return dataGood;
}

// Gets address of next Refugee
Refugee * Refugee::getNextRefugee() {
  return nextRefugee;
}

// Sets address of nextRefugee
void Refugee::setNextRefugee(Refugee * newNextRefugee) {
  nextRefugee = newNextRefugee;
}

// Checks if Refugee data is good
bool Refugee::goodRefugeeData() {
  return dataGood;
}

// Operation class
class Operation {

public:
  Operation();
  void loadFile(string);
  void nameSearch(string, string);
  void childSearch(int, char);
  void showCamp(string);
  int totalRefugees();
  void showRefugees();

private:
  Refugee * refugeeList;
  void addRefugee(Refugee *);
  int refugeeCount;
};

// Create empty  list of Refugee objects
Operation::Operation() {
  refugeeList = NULL;
}

// Checks data in file and loads data
void Operation::loadFile(string inputFileName) {
  ifstream userFile;
  string header;
  string fileFirstName;
  string fileLastName;
  char fileGender = ' ';
  int fileAge = 0;
  string fileCampName;
  refugeeCount = 0;
  char fileGood = ' ';
  Refugee newRefugee;
  Operation list;

  const int minAge = 0;
  const int maxAge = 120; // oldest current livign person is 116 years old

  // Check if file exists and opens
  userFile.open(inputFileName.c_str());
  if(!userFile) {
    do {
      cout << "ERROR: Unable to open file " << inputFileName << "." << endl
	   << "Please re-enter the name of the input file: ";
      cin >> inputFileName;
      userFile.open(inputFileName.c_str());
    } while (!userFile);
  }

  // Take out header line
  getline(userFile, header);

  while (userFile >> newRefugee) {
    refugeeCount++;
 
    // Verify gender and age are within range
    if (newRefugee.getGender() == 'm') {
      newRefugee.setGender('M');
    }
    if (newRefugee.getGender() == 'f') {
      newRefugee.setGender('F');
    }

    if((newRefugee.getGender() != 'M') && (newRefugee.getGender() != 'F')) {
      cout << "ERROR: " << newRefugee.getFirst() << " " << newRefugee.getLast()
	   << "'s gender is not valid." << endl;
      fileGood = 'n';
    }

    if ((newRefugee.getAge() < minAge) || (newRefugee.getAge() > maxAge)) {
      cout << "ERROR: " << newRefugee.getFirst() << " " << newRefugee.getLast()
	   << "'s age of " << newRefugee.getAge() << " is out of range." << endl;
      fileGood = 'n';
      }

    Refugee * temp = new Refugee(newRefugee.getFirst(), newRefugee.getLast(),
				 newRefugee.getGender(), newRefugee.getAge(),
				 newRefugee.getCampName());
    list.addRefugee(temp);
    temp->setNextRefugee(refugeeList);
    refugeeList = temp;
    }

  if (refugeeCount == 0) {
    fileGood = 'e';
  }

  switch (fileGood) {
  case 'e':
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    break;
  case 'n':
    cout << "Load was successful, but there is data that is out of range." << endl;    
    break;
  default:
    cout << "Load was successful and data is good." << endl;
    break;
  }

  userFile.close();

  cout << "Loaded " << refugeeCount << " refugees." << endl;
}

// Searches for Refugee by name
void Operation::nameSearch(string inputFirstName, string inputLastName) {
  string nameMatch;
  int firstCount = 0;
  int lastCount = 0;
  int fullCount = 0;
  Refugee * temp = refugeeList;

  // Checks to see if there is a loaded file
  if (temp == NULL) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  while (temp != NULL) {
    nameMatch = temp->nameMatch(inputFirstName, inputLastName);
    if (nameMatch == "First") {
      firstCount++;
    }
    if (nameMatch == "Last") {
      lastCount++;
    }
    if (nameMatch == "Exact") {
      fullCount++;
    }
    temp = temp->getNextRefugee();
  }

  // Output results
  if (fullCount > 0) {
    cout << "Exact match(es):" << endl;
    cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	 << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
    temp = refugeeList;
    while (temp != NULL) {
      if ((inputFirstName == temp->getFirst()) &&
          (inputLastName == temp->getLast())) {
        cout << *temp << endl;
      }
      temp = temp->getNextRefugee();
    }
  }

  if ((fullCount == 0) && (firstCount > 0)) {
    cout << "First name match(es):" << endl;
    cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	 << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
    temp = refugeeList;
    while (temp != NULL) {
      if ((inputFirstName == temp->getFirst()) &&
          (inputLastName != temp->getLast())) {
        cout << *temp << endl;
      }
      temp = temp->getNextRefugee();
    }
  }

  if ((fullCount == 0) && (lastCount > 0)) {
    cout << "Last name match(es):" << endl;
    cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	 << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
    temp = refugeeList;
    while (temp != NULL) {
      if ((inputFirstName != temp->getFirst()) &&
          (inputLastName == temp->getLast())) {
        cout << *temp << endl;
      }
      temp = temp->getNextRefugee();
    }
  }

  if (fullCount == 0) {
    cout << "Sorry, there were no exact matches for the name " << inputFirstName << " "
	 << inputLastName << "." << endl;
  }
}

// Searched for Refugee by age and gender
void Operation::childSearch(int inputAge, char inputGender) {
  int inputMinAge = inputAge - 1;
  int inputMaxAge = inputAge + 1;
  int ageCount = 0;
  int ageGenderCount = 0;
  Refugee * temp = refugeeList;
  bool ageGenderMatch;

  const int minAge = 0;
  const int maxAge = 120; // oldest current living person is 116 years old

  // Checks to see if there is a loaded file
  if (temp == NULL) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Checks to see if age and gender being searched for are valid
  if((inputAge < minAge) || (inputAge > maxAge)) {
    cout << "ERROR: The age that is being searched for of " << inputAge
	 << " is out of range." << endl;
    return;
  }

  switch (inputGender) {
  case 'M':
  case 'm':
    inputGender = 'M';
    break;
  case 'F':
  case 'f':
    inputGender = 'F';
    break;
  default:
    cout << "ERROR: The gender that is being searched for of " << inputGender
	 << " is not a valid gender." << endl;
    break;
  }

  while (temp != NULL) {
    ageGenderMatch = temp->ageMatch(inputAge, inputGender);
    if(ageGenderMatch) {
      ageGenderCount++;
    }
    temp = temp->getNextRefugee();
  }

  if (ageGenderCount == 0) {
    cout << endl << "Sorry, there were no matches for a refugee of approximately age "
	 << inputAge << " and is a " << inputGender << "." << endl;
  }

  if (ageGenderCount > 0) {
    cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	 << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
    temp = refugeeList;
    while (temp != NULL) {
      ageGenderMatch = temp->ageMatch(inputAge, inputGender);
      if (ageGenderMatch) {
	cout << *temp << endl;
      }
      temp = temp->getNextRefugee();
    }
  }
}

// Prints all refugees from a camp
void Operation::showCamp(string inputCampName) {
  Refugee * temp = refugeeList;
  bool campNameFound = false;

  // Checks to see if there is a loaded file
  if (temp == NULL) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
       << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
  while (temp != NULL) {
    if (inputCampName == temp->getCampName()) {
      cout << *temp << endl;
      campNameFound = true;
    }
    temp = temp->getNextRefugee();
  }

  if (campNameFound == false) {
    cout << "Sorry, no refugees were found in Camp " << inputCampName << "." << endl;
  }
}

// Prints out total number of refugees
int Operation::totalRefugees() {
  Refugee * temp = refugeeList;
  refugeeCount = 0;
  // Checks to see if there is a loaded file
  if (temp == NULL) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return 0;
  }
  else {
    while (temp != NULL) {
      refugeeCount++;
      temp = temp->getNextRefugee();
    }
    return refugeeCount;
  }
}

// Prints all refugees
void Operation::showRefugees() {
  Refugee * temp = refugeeList;

  // Checks to see if there is a loaded file
  if (temp == NULL) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
       << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
  while (temp != NULL) {
    cout << *temp << endl;
    temp = temp->getNextRefugee();
  }
}

// Adds a refugee to the list
void Operation::addRefugee(Refugee * newRefugee) {
  Refugee * temp = refugeeList;

  if (refugeeList == NULL) {
    refugeeList = new Refugee(newRefugee->getFirst(), newRefugee->getLast(),
		       newRefugee->getGender(), newRefugee->getAge(),
		       newRefugee->getCampName());
  }
  else {
    Refugee * temp = new Refugee(newRefugee->getFirst(), newRefugee->getLast(),
				 newRefugee->getGender(), newRefugee->getAge(),
				 newRefugee->getCampName());
    temp->setNextRefugee(refugeeList);
    refugeeList = temp;
  }
}

// MAIN FUNCTION
int main() {
  bool finished = false;
  Operation refugees;
  char userSelection = ' ';
  string userFileName;
  string userFirstName;
  string userLastName;
  int userAge;
  char userGender = ' ';
  string userCampName;

  while (!finished) {
    // Output menu option and allow user selection
    userSelection = selectMenuOption();

    switch(userSelection) {
    case 'L':
    case 'l':
      cout << endl << "Enter name of file to load: ";
      getline(cin, userFileName);
    // Load file
      refugees.loadFile(userFileName);
      break;
    case 'N':
    case 'n':
      cout << "Please enter first name to search for: ";
     cin >> userFirstName;
      cout << "Please enter last name to search for: ";
      cin >> userLastName;
      // Search for refugee by name
      refugees.nameSearch(userFirstName, userLastName);
      break;
    case 'A':
    case 'a':
      cout << "Please enter the age of refugee to search for: ";
      cin >> userAge;
      cout << "Please enter the gender of refugee to search for (M/F): ";
      cin >> userGender;
      // Search for refugee by age and gender
      refugees.childSearch(userAge, userGender);
      break;
    case 'C':
    case 'c':
      cout << "Please enter the name of a camp: ";
      cin >> userCampName;
      // List all refugees in camp
      refugees.showCamp(userCampName);
      break;
    case 'T':
    case 't':
      // Count all refugees loaded
      cout << "There are a total of " << refugees.totalRefugees()
	   << " refugees in all camps." << endl;
      break;
    case 'P':
    case 'p':
      // Print all refugees loaded
      refugees.showRefugees();
      break;
    case 'Q':
    case 'q':
      finished = true;
      break;
    default:
      cout << "ERROR: Please select a valid menu option." << endl;
      break;
    } // end of switch statement
  } // end of while loop

return 0;
}


// FUNCTION DEFINITION
// Prints out menu options and returns user selection
char selectMenuOption() {
  char selection = ' ';
  string trash;

  cout << endl;
  cout << right << setw(45) << "Add a camp list" << setw(10) << "L" << endl;
  cout << setw(45) << "Search for a refugee by name" << setw(10) << "N" << endl;
  cout << setw(45) << "Search for refugee by age and gender" << setw(10) << "A"
       << endl;
  cout << setw(45) << "Show all refugees at a camp" << setw(10) << "C" << endl;
  cout << setw(45) << "Count of refugees" << setw(10) << "T" << endl;
  cout << setw(45) << "Print all refugees" << setw(10) << "P" << endl;
  cout << setw(45) << "Exit the program" << setw(10) << "Q" << endl << endl;

  cout << "Please enter your choice: ";
  cin >> selection;
  getline(cin, trash);
  cin.clear();

  return selection;
}
