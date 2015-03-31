/**
 *
 * Project 3
 * Refugee Locator
 * Leslie Kim
 * NetID: lk584
 * COSC 051
 * Section 02
 * In accordance with the class policies and Goergetown's Honor Code,
 * I certify that I have neither given nor receieved any assitance
 * on this project with the exceptions of lecture notes and those items
 * noted below.
 * Any help items: Fall 2013 Project 3 Solution
 * Description <This program will assist in finding separated refugees
 * by searching through data files that contain the name, gender, age
 * and camp name of refugees. Users will be permitted to load as many
 * files as they want. Each file contains the first and last name (UNK
 * for unknown names), gender, age and camp of each refugee. Users will
 * be able to search for refugees by name or age and gender, list all
 * refugees at a camp, get a count of total refugees and print all
 * information abotu refugees.>
 *
 **/

#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// FUNCTION PROTOTYPES
char selectMenuOption();
bool checkFile(string &);
void loadFile(string, vector<string> &, vector<string> &, vector<char> &,
	      vector<int> &, vector<string> &);
void searchName(const string, const string, const vector<string>,
		const vector<string>, const vector<char>, const vector<int>,
		const vector<string>);
void searchAgeGender(const int, const char, const vector<string>,
		     const vector<string>, const vector<char>, const vector<int>,
		     const vector<string>);
void printCampRefugees(const string, const vector<string>, const vector<string>,
		       const vector<char>, const vector<int>, const vector<string>);
int countRefugees(const vector<string>);
void printHeader();
void printRefugee(const string, const string, const char, const int, const string);
void printRefugees(const vector<string>, const vector<string>, const vector<char>,
		   const vector<int>, const vector<string>);

int main() {
  bool finished = false;
  char userSelection = ' ';
  string userFilename;
  string userFirstName;
  string userLastName;
  int userAge = 0;
  char userGender = ' ';
  string userCamp;

  vector<string> firstNames;
  vector<string> lastNames;
  vector<char> genders;
  vector<int> ages;
  vector<string> campNames;

  while (!finished) {
    // Output menu option and allow user selection
    userSelection = selectMenuOption();

    switch (userSelection) {
    case 'L':
    case 'l':
      cout << endl << "Enter name of file to load: ";
      getline (cin, userFilename);
      // Load file
      loadFile(userFilename, firstNames, lastNames, genders, ages, campNames);
      break;
    case 'N':
    case 'n':
      cout << "Please enter first name to search for: ";
      cin >> userFirstName;
      cout << "Please enter last name to search for: ";
      cin >> userLastName;
      // Search for refugee by name
      searchName(userFirstName, userLastName, firstNames, lastNames, genders, ages,
		 campNames);
      break;
    case'A':
    case'a':
      cout << "Please enter the age of refugee to search for: ";
      cin >> userAge;
      cout << "Please enter the gender of refugee to search for (M/F): ";
      cin >> userGender;
      // Search for refugee by age and gender
      searchAgeGender(userAge, userGender, firstNames, lastNames, genders, ages,
		      campNames);
      break;
    case'C':
    case'c':
      cout << "Please enter the name of a camp: ";
      cin >> userCamp;
      // List all refugees in camp
      printCampRefugees(userCamp, firstNames, lastNames, genders, ages, campNames);
      break;
    case'T':
    case't':
      // Count all refugees loaded
      countRefugees(firstNames);
      break;
    case 'P':
    case 'p':
      // Print all refugees loaded
      printRefugees(firstNames, lastNames, genders, ages, campNames);
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

// Checks if file opens and verifies data
bool checkFile(string & inputFileName) {
  ifstream userFile;
  string firstName;
  string lastName;
  char gender = ' ';
  int age = 0;
  string campName;
  string header;
  int count = 0;
  bool fileGood = true;

  const int minAge = 0;
  const int maxAge = 120; // oldest current living person is 120 years old

  // Check if file opens
  userFile.open(inputFileName.c_str());
  if (!userFile) {
    do {    
      cout << "ERROR: Unable to open " << inputFileName << "." << endl
	   << "Please re-enter the name of the input file: ";
      cin >> inputFileName;
      userFile.open(inputFileName.c_str());
    } while (!userFile);
  }

  // Take out header line
  getline(userFile, header);

  // Verify gender and age are within range
  while (userFile >> firstName >> lastName >> gender >> age >> campName) {
    count ++;
    if ((gender != 'M') && (gender != 'F')) {
      cout << "ERROR: " << firstName << " " << lastName << "'s gender is not valid."
	   << endl;
      fileGood = false;
    }
    if ((age < minAge) || (age > maxAge)) {
      cout << "ERROR: " << firstName << " " << lastName << "'s age of " << age
	   << " is out of range." << endl;
      fileGood = false;
    }
  }
  if (count == 0) {
    cout << "ERROR: There was no data in this file. No data loaded." << endl;
    fileGood = false;
  }

  userFile.close();
  return fileGood;
}

// Loads file data
void loadFile(string inputFileName, vector<string> & firstName,
	      vector<string> & lastName, vector<char> & gender, vector<int> & age,
	      vector<string> & campName) {
  ifstream userFile;
  string header;
  string firstNames;
  string lastNames;
  char genders = ' ';
  int ages = 0;
  string campNames;
  int count = 0;

  // Open file
  userFile.open(inputFileName.c_str());
  if(!userFile) {
    do {
      cout << "ERROR: Unable to open file " << inputFileName << "." << endl
	   << "Please re-enter the name of the input file: ";
      cin >> inputFileName;
      userFile.open(inputFileName.c_str());
    } while (!userFile);
  }

  // Check if file opens and verifies data
  if(!checkFile(inputFileName)) {
    cout << "ERROR: Errors found in " << inputFileName << ". No information loaded."
	 << endl;
    return;
  }

  // Take out header line
  getline(userFile, header);

  // Read lines into vectors
  while (userFile >> firstNames >> lastNames >> genders >> ages >> campNames) {
    count ++;

    firstName.push_back(firstNames);
    lastName.push_back(lastNames);
    gender.push_back(genders);
    age.push_back(ages);
    campName.push_back(campNames);
  }

  userFile.close();
  cout << "Loaded " << count << " refugees from " << inputFileName << "." << endl;
}

// Search for refugee by name
void searchName(const string inputFirstName, const string inputLastName,
		const vector<string> firstName, const vector<string> lastName,
		const vector<char> gender, const vector<int> age,
		const vector<string> campName) {
  bool nameFound = false;
  int firstCount = 0;
  vector<string> firstFirstNameFound;
  vector<string> firstLastNameFound;
  vector<char> firstGenderFound;
  vector<int> firstAgeFound;
  vector<string> firstCampNameFound;
  int lastCount = 0;
  vector<string> lastFirstNameFound;
  vector<string> lastLastNameFound;
  vector<char> lastGenderFound;
  vector<int> lastAgeFound;
  vector<string> lastCampNameFound;
  int fullCount = 0;
  vector<string> fullFirstNameFound;
  vector<string> fullLastNameFound;
  vector<char> fullGenderFound;
  vector<int> fullAgeFound;
  vector<string> fullCampNameFound;

  // Checks to see if there is a loaded file
  if (firstName.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Creates vectors for matching first names and/or last names
  for (int i = 0; i < firstName.size(); i++) {
    if (firstName[i] == inputFirstName) {
      firstCount++;
      firstFirstNameFound.push_back(firstName[i]);
      firstLastNameFound.push_back(lastName[i]);
      firstGenderFound.push_back(gender[i]);
      firstAgeFound.push_back(age[i]);
      firstCampNameFound.push_back(campName[i]);
    }
    if (lastName[i] == inputLastName) {
      lastCount++;
      lastFirstNameFound.push_back(firstName[i]);
      lastLastNameFound.push_back(lastName[i]);
      lastGenderFound.push_back(gender[i]);
      lastAgeFound.push_back(age[i]);
      lastCampNameFound.push_back(campName[i]);
    }
    if ((firstName[i] == inputFirstName) && (lastName[i] == inputLastName)) {
      fullCount++;
      fullFirstNameFound.push_back(firstName[i]);
      fullLastNameFound.push_back(lastName[i]);
      fullGenderFound.push_back(gender[i]);
      fullAgeFound.push_back(age[i]);
      fullCampNameFound.push_back(campName[i]);
    }
  }

  // Outputs results
  cout << endl <<  "Exact matches: " << endl;
  if (fullCount == 0) {
    cout << "None" << endl;
  }
  else if(fullCount > 0) {
    printRefugees(fullFirstNameFound, fullLastNameFound, fullGenderFound,
		  fullAgeFound, fullCampNameFound);
  }
  cout << endl << "First name matches: " << endl;
  if (firstCount == 0) {
    cout << "None" << endl;
  }
  else if (firstCount > 0) {
    printRefugees(firstFirstNameFound, firstLastNameFound, firstGenderFound,
		firstAgeFound, firstCampNameFound);
  }
  cout << endl << "Last name matches: " << endl;
  if (lastCount == 0) {
    cout << "None" << endl;
  }
  else if (lastCount > 0) {  
    printRefugees(lastFirstNameFound, lastLastNameFound, lastGenderFound,
		  lastAgeFound,	lastCampNameFound);
  }

  // Checks for exact match(es)
  for (int m = 0; m < firstName.size(); m++) {
    if ((firstName[m] == inputFirstName) && (lastName[m] == inputLastName)) {
      nameFound = true;
      return;
    }
  }

  // Output for no exact match
  if (!nameFound) {
    cout << endl << "Sorry, there was no exact match for a refugee named "
	 << inputFirstName << " " << inputLastName << " found." << endl;
  }
}

// Search for refugee by age and gender
void searchAgeGender(const int inputAge, const char inputGender,
		     const vector<string> firstName, const vector<string> lastName,
		     const vector<char> gender, const vector<int> age,
		     const vector<string> campName) {
  const int minAge = 0;
  const int maxAge = 120; // oldest current living person is 120 years old
  int inputMinAge = inputAge - 1;
  int inputMaxAge = inputAge + 1;
  int ageCount = 0;
  vector<string> ageFirstNameFound;
  vector<string> ageLastNameFound;
  vector<char> ageGenderFound;
  vector<int> ageAgeFound;
  vector<string> ageCampNameFound;
  int genderCount = 0;
  vector<string> genderFirstNameFound;
  vector<string> genderLastNameFound;
  vector<char> genderGenderFound;
  vector<int> genderAgeFound;
  vector<string> genderCampNameFound;
  int ageGenderCount = 0;
  vector<string> agFirstNameFound;
  vector<string> agLastNameFound;
  vector<char> agGenderFound;
  vector<int> agAgeFound;
  vector<string> agCampNameFound;
  bool refugeeFound = false;

  // Checks to see if there is a loaded file
  if (firstName.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Check to see if age and gender being searched for is valid
  if ((inputAge < minAge) || (inputAge > maxAge)) {
    cout << "ERROR: The age " << inputAge << " is out of range." << endl;
    return;
  }
  if ((inputGender != 'M') && (inputGender != 'F')) {
    cout << "ERROR: The gender " << inputGender << " is not a valid gender." << endl;
    return;
  }

  // Creates vectors of matches for ages and/or genders
  for (int i = 0; i < firstName.size(); i++) {
    if ((age[i] >= inputMinAge) && (age[i] <= inputMaxAge)) {
	ageCount++;
	ageFirstNameFound.push_back(firstName[i]);
	ageLastNameFound.push_back(lastName[i]);
	ageGenderFound.push_back(gender[i]);
	ageAgeFound.push_back(age[i]);
	ageCampNameFound.push_back(campName[i]);
    }
    if (gender[i] == inputGender) {
      genderCount++;
      genderFirstNameFound.push_back(firstName[i]);
      genderLastNameFound.push_back(lastName[i]);
      genderGenderFound.push_back(gender[i]);
      genderAgeFound.push_back(age[i]);
      genderCampNameFound.push_back(campName[i]);
    }
    if ((age[i] >=inputMinAge) && (age[i] <= inputMaxAge)
	&& (gender[i] == inputGender)) {
      ageGenderCount++;
      agFirstNameFound.push_back(firstName[i]);
      agLastNameFound.push_back(lastName[i]);
      agGenderFound.push_back(gender[i]);
      agAgeFound.push_back(age[i]);
      agCampNameFound.push_back(campName[i]);
    }
  }

  // Outputs results
  cout << endl << "Age (within +/- 1 year) and gender matches: " << endl;
  if (ageGenderCount == 0) {
    cout << "None" << endl;
  }
  else if (ageGenderCount > 0) {
    printRefugees(agFirstNameFound, agLastNameFound, agGenderFound, agAgeFound,
		  agCampNameFound);
  }
  cout << endl << "Age (within +/- 1 year) matches: " << endl;
  if (ageCount == 0) {
    cout << "None" << endl;
  }
  else if (ageCount > 0) {
    printRefugees(ageFirstNameFound, ageLastNameFound, ageGenderFound, ageAgeFound,
		  ageCampNameFound);
  }
  cout << endl << "Gender matches: " << endl;
  if (genderCount == 0) {
    cout << "None" << endl;
  }
  else if (genderCount > 0) {
    printRefugees(genderFirstNameFound, genderLastNameFound, genderGenderFound,
		  genderAgeFound, genderCampNameFound);
  }

  // Checks to see if these is exact match(es)
  for (int m = 0; m < firstName.size(); m++) {
    if ((age[m] >= inputMinAge) && (age[m] <= inputMaxAge)
	&& (gender[m] == inputGender)) {
      refugeeFound = true;
      return;
    }
  }

  // Output for no exact match
  if (!refugeeFound) {
    cout << endl
	 << "Sorry, there was no exact match for a refugee of approximately age "
	 << inputAge << " and is a " << inputGender << "." << endl;
  }
}

// Print all refugees from specified camp
void printCampRefugees(const string inputCamp, const vector<string> firstName,
		       const vector<string> lastName, const vector<char> gender,
		       const vector<int> age, const vector<string> campName) {
  int campCount = 0;
  vector<string> campFirstNameFound;
  vector<string> campLastNameFound;
  vector<char> campGenderFound;
  vector<int> campAgeFound;
  vector<string> campCampFound;
  bool campFound = false;

  // Checks to see if there is a loaded file
  if (firstName.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  for (int i = 0; i < firstName.size(); i++) {
    if (campName[i] == inputCamp) {
      campCount++;
      campFirstNameFound.push_back(firstName[i]);
      campLastNameFound.push_back(lastName[i]);
      campGenderFound.push_back(gender[i]);
      campAgeFound.push_back(age[i]);
      campCampFound.push_back(campName[i]);
    }
  }

  cout << endl << "Matches for refugees in camp " << inputCamp << ": " << endl;
  if (campCount == 0) {
    cout << "None" << endl;
  }
  else if (campCount > 0){
    printRefugees(campFirstNameFound, campLastNameFound, campGenderFound,
		  campAgeFound, campCampFound);
  }

  for (int m = 0; m < firstName.size(); m++) {
    if (campName[m] == inputCamp) {
      campFound = true;
      return;
    }
  }

  if (!campFound) {
    cout << endl
	 << "Sorry, there were no refugees found in camp " << inputCamp << "."
	 << endl;
  }
}

// Counts all refugees
int countRefugees(const vector<string> firstName) {
  int total = 0;

  // Checks to see if there is a loaded file
  if (firstName.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return -1;
  }
  else {
    total = firstName.size();
    cout << "There are a total of " << total << " refugees in all camps." << endl;
    return 0;
  }
}

// Prints header
void printHeader() {
  cout << left << setw(25) << "First Name" << setw(25) << "Last Name" << setw(10)
       << "Gender" << setw(5) << "Age" << setw(15) << "Camp Name" << endl;
}

// Prints one refugee's information - formatted
void printRefugee(const string firstName, const string lastName, const char gender,
		  const int age, const string campName) {
  cout << left << setw(25) << firstName << setw(25) << lastName << setw(10) << gender
       << setw(5) << age << setw(15) << campName << endl;
}

// Prints out all refugees' information - formatted
void printRefugees(const vector<string> firstName, const vector<string> lastName,
		   const vector<char> gender, const vector<int> age,
		   const vector<string> campName) {
  const int minAge = 0;
  const int maxAge = 120; // oldest current living person is 120 years old

  // Checks to see if there is a loaded file
  if (firstName.empty()) {
    cout << "ERROR: No file was loaded. There is no data to display." << endl;
    return;
  }

  // Prints from youngest to oldest
  printHeader();
  for (int ageForSorting = minAge; ageForSorting <= maxAge; ageForSorting++) {
    for (int i = 0; i < firstName.size(); i++) {
      if (age[i] == ageForSorting) {
	printRefugee(firstName[i], lastName[i], gender[i], age[i], campName[i]);
      }
    }
  } // end of ageForSorting for loop
}
