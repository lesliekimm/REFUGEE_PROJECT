/**
 *
 * Project 4
 * Refugee Locator
 * Leslie Kim
 * NetID: lk584
 * COSC 051
 * Section 02
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance on
 * this project with the exceptions of lecture notes and those items
 * listed below.
 * Any help items: Fall 2013 Project 4 Solution
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
#include <vector>
using namespace std;

// FUNCTION PROTOTYPES
char selectMenuOption();

// CLASSES
// Refugee class
class Refugee {

  friend ostream &operator<<(ostream &, Refugee);

public:
  // Constructors
  Refugee();
  Refugee(string, string, char, int, string);
  // Accessors & setters
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
  // Methods
  string nameMatch(string, string);
  bool ageMatch(int, char);
  bool goodRefugeeData();

private:
  string firstName;
  string lastName;
  char gender;
  int age;
  string campName;
  bool dataGood;
};

// Creates an empty refugee object
Refugee::Refugee() {
  firstName = "";
  lastName = "";
  gender = ' ';
  age = 0;
  campName = "";
  dataGood = false;
}

// Refugee object takes input - error checks performed in Operation class
Refugee::Refugee(string inputFirstName, string inputLastName, char inputGender,
		 int inputAge, string inputCampName) {
  firstName = inputFirstName;
  lastName = inputLastName;
  gender = inputGender;
  age = inputAge;
  campName = inputCampName;
}

// Output formatting
ostream &operator<<(ostream & output, Refugee x) {

  output << left << setw(25) << x.firstName << setw(25) << x.lastName << setw(10)
	 << x.gender << setw(5) << x.age << setw(15) << x.campName;
  return output;
}

// Accesses refugee's first name
string Refugee::getFirst() {
  return firstName;
}

// Sets refugee's first name
void Refugee::setFirst(string inputFirstName) {
  firstName = inputFirstName;
}

// Accesses refugee's last name
string Refugee::getLast() {
  return lastName;
}

// Sets refugee's last name
void Refugee::setLast(string inputLastName) {
  lastName = inputLastName;
}

// Accesses refugee's gender
char Refugee::getGender() {
  return gender;
}

// Sets refugee's gender & performs error check
void Refugee::setGender(char inputGender) {
  gender = inputGender;

  switch (gender) {
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
    dataGood = false;
    break;
  }
}

// Accesses refugee's age
int Refugee::getAge() {
  return age;
}

// Sets refugee's age & performs error check
void Refugee::setAge(int inputAge) {
  const int minAge = 0;
  const int maxAge = 120; // oldest current living person is 116 years old

  age = inputAge;

  if ((age < minAge) || (age > maxAge)) {
    cout << "ERROR: " << firstName << " " << lastName << "'s age of " << age
	 << " is out of range." << endl;
    dataGood = false;
  }
}

// Accesses refugee's camp name
string Refugee::getCampName() {
  return campName;
}

// Sets refugee's camp name
void Refugee::setCampName(string inputCampName) {
  campName = inputCampName;
}

// Performs search for refugee by name
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
  const int minAge = 0;
  const int maxAge = 120; // oldest current living person in 116 years old
  int inputMinAge = inputAge - 1;
  int inputMaxAge = inputAge + 1;

  if ((inputAge < minAge) || (inputAge > maxAge)) {
    cout << "ERROR: The age " << inputAge << " is out of range." << endl;
    dataGood = false;
  }

  switch (inputGender) {
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
    dataGood = false;
    break;
  }

  // Checks for refugees of inputAge within +/- 1 year and inputGender
  if((age >= inputMinAge) && (age <= inputMaxAge) &&
     (gender == inputGender)) {
    dataGood = true;
  }
  else {
    dataGood = false;
  }

  return dataGood;
}

bool Refugee::goodRefugeeData() {
  return dataGood;
}

// Operation Class
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
  vector<Refugee> refugees;
};

// Create empty vector of Refugee objects
Operation::Operation() {
  refugees.clear();
}

// Checks data in file and loads file
void Operation::loadFile(string inputFileName) {
  ifstream userFile;
  string header;
  string fileFirstName;
  string fileLastName;
  char fileGender = ' ';
  int fileAge = 0;
  string fileCampName;
  int count = 0;
  char fileGood = ' ';;

  const int minAge = 0;
  const int maxAge = 120; // oldest curret living person is 116 years old

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

  while (userFile >> fileFirstName >> fileLastName >> fileGender >> fileAge >>
	 fileCampName) {
    count++;
    // Verify gender and age are within range
    if (fileGender == 'm') {
      fileGender = 'M';
    }
    if (fileGender == 'f') {
      fileGender = 'F';
    }

    if((fileGender != 'M') && (fileGender != 'F')) {
      cout << "ERROR: " << fileFirstName << " " << fileLastName
	   << "'s gender is not valid." << endl;
      fileGood = 'n';
    }

    if ((fileAge < minAge) || (fileAge > maxAge)) {
      cout << "ERROR: " << fileFirstName << " " << fileLastName << "'s age of "
	   << fileAge << " is out of range." << endl;
      fileGood = 'n';
    }

    Refugee refugee(fileFirstName, fileLastName, fileGender, fileAge, fileCampName);
    refugees.push_back(refugee);
  }

  if (count == 0) {
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

  cout << "Loaded " << count << " refugees." << endl;
}

void Operation::nameSearch(string inputFirstName, string inputLastName) {
  string nameMatch;
  int firstCount = 0;
  vector<Refugee> firstNameFound;
  int lastCount = 0;
  vector<Refugee> lastNameFound;
  int nameCount = 0;
  vector<Refugee> fullNameFound;

  // Checks to see if there is a loaded file
  if (refugees.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Creates vectors for matching first names and/or last names
  for (int i = 0; i < refugees.size(); i++) {
    nameMatch = refugees[i].nameMatch(inputFirstName, inputLastName);
    if (nameMatch == "First") {
      firstCount++;
      firstNameFound.push_back(refugees[i]);
    }
    if (nameMatch == "Last") {
      lastCount++;
      lastNameFound.push_back(refugees[i]);
    }
    if (nameMatch == "Exact") {
      nameCount++;
      fullNameFound.push_back(refugees[i]);
    }
  }

  // Outputs results
  if (nameCount > 0) {
      cout << "Exact match(es): " << endl;
      cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	   << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
      for (int j = 0; j < fullNameFound.size(); j++) {
	cout << fullNameFound[j] << endl;
      }
  }
  if ((nameCount == 0) && (firstCount > 0)) {
      cout << "First name match(es): " << endl;
      cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	   << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
      for (int k = 0; k < firstNameFound.size(); k++) {
	cout << firstNameFound[k] << endl;
      }
  }
  if ((nameCount == 0) && (lastCount > 0)) {
      cout << "Last name match(es): " << endl;
      cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	   << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
      for (int l = 0; l < lastNameFound.size(); l++) {
	cout << lastNameFound[l] << endl;
      }
  }
  if (nameCount == 0) {
    cout << "Sorry, there were no exact matches for the name " << inputFirstName
	 << " " << inputLastName << "." << endl;
  }
}

void Operation::childSearch(int inputAge, char inputGender) {
  const int minAge = 0;
  const int maxAge = 120; // oldest living person is 116 years old
  int inputMinAge = inputAge - 1;
  int inputMaxAge = inputAge + 1;
  int ageCount = 0;
  int ageGenderCount = 0;
  vector<Refugee> ageGenderFound;
  bool ageGenderMatch;

  // Checks to see if there is a loaded file
  if (refugees.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Checks to see if age and gender being searched for are valid
  if((inputAge < minAge) || (inputAge > maxAge)) {
    cout << "ERROR: The age " << inputAge << " is out of range." << endl;
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
    cout << "ERROR: The gender " << inputGender << " is not a valid gender." << endl;
    break;
  }

  for (int i = 0; i < refugees.size(); i++) {
    ageGenderMatch = refugees[i].ageMatch(inputAge, inputGender);
    if (ageGenderMatch) {
      ageGenderCount++;
      ageGenderFound.push_back(refugees[i]);
    }
  }

  if (ageGenderCount == 0) {
    cout << endl << "Sorry, there were no matches for a refugee of approximately age "
	 << inputAge << " and is a " << inputGender << "." << endl;
  }
  if (ageGenderCount > 0) {
    // Prints header
    cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
	 << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
    for (int j = 0; j < ageGenderFound.size(); j++) {
      cout << ageGenderFound[j] << endl;
    }
  }
}

void Operation::showCamp(string inputCampName) {
  int campCount = 0;
  bool campFound = false;

  // Checks to see if there is a loaded file
  if (refugees.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Prints header
  cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
       << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;

  for (int i = 0; i < refugees.size(); i++) {
    if (refugees[i].getCampName() == inputCampName) {
      campCount++;
      campFound = true;
      cout << refugees[i] << endl;
    }
  }
  
 if (!campFound) {
   cout << endl << "Sorry, there were no refugees found in camp " << inputCampName
	<< "." << endl;
 }
}

int Operation::totalRefugees() {
  int total = 0;

  // Checks to see if there is a loaded file
  if (refugees.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return 0;
  }
  else {
    total = refugees.size();
    return total;
  }
}

void Operation::showRefugees() {
  int campCount = 0;
  bool campFound = false;

  const int minAge = 0;
  const int maxAge = 120; // oldest living person is 116 years old

  // Checks to see if there is a loaded file
  if (refugees.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Prints header
  cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
       << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;

  // Prints from youngest to oldest
  for (int ageForSorting = minAge; ageForSorting <= maxAge; ageForSorting++) {
    for (int i = 0; i < refugees.size(); i++) {
      if (refugees[i].getAge() == ageForSorting) {
	cout << refugees[i] << endl;
      }
    }
  } // end of ageForSorting loop
}

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
}

// FUNCTION DEFINITIONS
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
