/**
 *
 * Project 2
 * Multiple Camp Water Calculations
 * Leslie Kim
 * NettID: lk584
 * COSC 051
 * Section 02
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance
 * on this project with the exceptions of the lecture notes and those
 * items noted below.
 * Any help items: NA
 * Description: <This program will read a file containing information
 * about multiple refugee camps and detemrmine which camps have enough
 * water and which do not. It will then total the number of water
 * buffalos needed to transport water betwen camps.>
 *
 **/

#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {

  // Define variables
  // All liquid measurements have been converted to liters (L)
  int numOfRefugees = 0;
  double dailyWaterNeeds = 0; // measured in L/person/day
  int numOfTaps = 0;
  double waterTapsProvides = 0.0;
  int numOfPumps = 0;
  double waterPumpsProvides = 0.0;
  int numOfWells = 0;
  double waterWellsProvides = 0.0;
  double totalWaterNeeds = 0.0;
  double totalWaterAvailable = 0.0;
  double waterSurplus = 0.0;
  double waterDeficit = 0.0;
  int needBuffalos = 0;

  // Define constants
  const double minWater = 7.5; // L/person/day
  const int maxWater = 15; // L/person/day

  // Define constant water sources provisions (measured in L/min)
  const double tapFlow = 7.5;
  const int  handPumpFlow = 17;
  const double openWellFlow = 12.5;
  const int accessTime = 480; // 8 hours/day = 480 mins/day
  const double waterBuffalos = 1514.164; // L/day

  // Define file
  ifstream inputFile;

  // Define columns
  string campName;
  int surplusBuffalos = 0;
  int totalRefugees = 0;
  double totalWaterSurplus = 0.0;
  int totalSurplusBuffalos = 0;
  double totalWaterDeficit = 0.0;
  int totalNeedBuffalos = 0;

  // Output program description
  cout << endl
       << "Multiple Camp Water Distribution Helper:" << endl
       << "This program will read a file containing information about multiple" << endl
       << "refugee camps and determine which camps have enough water and which" << endl
       << "do not. It will then total the number of water buffalos needed to" << endl
       << "transport water between camps." << endl << endl;

  // Ask for file name
  cout << "Please enter the name of the input file: ";
  cin >> campName;

  // Connect variable to file and check name validity and if it opens
  inputFile.open(campName.c_str());
  if (!inputFile) {
    do {
      cout << "File not found." << endl
	   << "Please re-enter the name of the input file: ";
      cin >> campName;
      inputFile.open(campName.c_str());
    } while (!inputFile);
  }

  // Output header
  cout << endl;
  cout << setw(8) << "Camp" << setw(16) << "Number" << setw(16) << "Water"
       << setw(16) << "Surplus" << setw(16) << "Water" << setw(16) << "Need" << endl;
  cout << setw(8) << "Name" << setw(16) << "Refugee" << setw(16) << "Surplus"
       << setw(16) << "Buffalos" << setw(16) << "Deficit" << setw(16) << "Buffalos" << endl;
  cout << setw(8) << "--------" << setw(16) << "--------" << setw(16) << "--------"
       << setw(16) << "--------" << setw(16) << "--------" << setw(16) << "--------" << endl;

  // Validate input data from file
  while (inputFile >> campName >> numOfRefugees >> dailyWaterNeeds >> numOfTaps
	 >> numOfWells >> numOfPumps) {

	 // Check if numOfRefugees is valid
	 if (numOfRefugees < 0) {
	   cout << endl << "WARNING: There is a negative number of refugees in Camp "
		<< campName << "." << endl
		<< "There cannot be a negative number of refugees in a camp."
		<< endl << endl;
	   return 0;
	 }
	 else if (numOfRefugees > 100000) {
	   cout << endl << "WARNING: There is more than 100,000 refugees in Camp " << campName
		<< "." << endl
		<< "There should not be more than 100,000 refugees in one camp."
		<< endl << endl;
	   return 0;
	 }
	 /*
	   else if (numOfRefugees == 0) {
	   cout << endl << "WARNING: There are no refugees in " << campName
		<< " to provide water for." << endl << endl;
	 }
	 */

	 // Check if dailyWaterNeeds is valid
	 if (dailyWaterNeeds < 0) {
	   cout << endl << "WARNING: The water needs entered for Camp " << campName << " is not"
		<< endl
		<< "within range of the standards in water supply, sanitation and" << endl
		<< "hygiene promotion according to the Sphere Project Minimum" << endl
		<< "Standards in Humanitarian Response. There cannot be a negative" << endl
		<< "amount of daily water needs." << endl << endl;
	   return 0;
	 }
	 else if (dailyWaterNeeds == 0) {
	   cout << endl << "WARNING: The water needs entered for Camp " << campName << " is not"
		<< endl
		<< "within range of the standards in water supply, sanitation and" << endl
		<< "hygiene promotion according to the Sphere Project Minimum" << endl
		<< "Standards in Humanitarian Response. Zero liters of water will" << endl
		<< "lead to death."
		<< endl << endl;
	   return 0;
	 }
	 else if (dailyWaterNeeds < minWater) {
	   cout << endl << "WARNING: The water needs entered for Camp " << campName << " is not"
		<< endl
		<< "within range of the standards in water supply, sanitation and" << endl
		<< "hygiene promotion according to the Sphere Project Minimum" << endl
		<< "Standards in Humanitarian Response. Daily water needs is too low."
		<< endl << endl;
	   return 0;
	 }
	 else if (dailyWaterNeeds > maxWater) {
	   cout << endl << "WARNING: The water needs entered for Camp " << campName << " is not"
		<< endl
		<< "within range of the standards in water supply, sanitation and" << endl
		<< "hygiene promotion according to the Sphere Project Minimum" << endl
		<< "Standards in Humanitarian Response. Daily water needs is too high."
		<< endl << endl;
	   return 0;
	 }

	 // Check if numOfTaps, numOfWells and numOfPumps are valid
	 if (numOfTaps < 0) {
	   cout << endl << "WARNING: There is a negative number of taps in Camp " << campName
		<< "." << endl << "There cannot be a negative number of taps." << endl << endl;
	   return 0;
	 }
	 if (numOfWells < 0) {
	   cout << endl << "WARNING: There is a negative number of wells in Camp " << campName
		<< "." << endl << "There cannot be a negative number of wells." << endl << endl;
	   return 0;
	 }
	 if (numOfPumps < 0) {
	   cout << endl << "WARNING: There is a negative number of pumps in Camp " << campName
		<< "." << endl << "There cannot be a negative number of pumps." << endl << endl;
	   return 0;
	 }

	 // Make output calculations now that validation is complete for the line that was read
	 waterTapsProvides = numOfTaps * tapFlow * accessTime;
	 waterPumpsProvides = numOfPumps * handPumpFlow * accessTime;
	 waterWellsProvides = numOfWells * openWellFlow * accessTime;
	 totalWaterNeeds = numOfRefugees * dailyWaterNeeds;
	 totalWaterAvailable = waterTapsProvides + waterPumpsProvides + waterWellsProvides;

	 // Is there water surplus or deficit?
	 if (totalWaterAvailable >= totalWaterNeeds) {
	   waterSurplus = totalWaterAvailable - totalWaterNeeds;
	   surplusBuffalos = floor(waterSurplus / waterBuffalos);
	   waterDeficit = 0;
	   needBuffalos = 0;

	   // Output line for surplus
	   cout << setw(8) << campName << setw(16) << numOfRefugees << setw(16)
		<< waterSurplus << setw(16) << surplusBuffalos << setw(16) << waterDeficit
		<< setw(16) << needBuffalos << endl;

	   // Calculate overall totals
	   totalRefugees += numOfRefugees;
	   totalWaterSurplus += waterSurplus;
	   totalSurplusBuffalos += surplusBuffalos;
	   totalWaterDeficit += waterDeficit;
	   totalNeedBuffalos += needBuffalos;
	 }
	 else if (totalWaterAvailable <= totalWaterNeeds) {
	   waterSurplus = 0;
	   surplusBuffalos = 0;
	   waterDeficit = totalWaterNeeds - totalWaterAvailable;
	   needBuffalos = ceil(waterDeficit / waterBuffalos);
	
	   // Output line for deficit
	   cout << setw(8) << campName << setw(16) << numOfRefugees << setw(16)
		<< waterSurplus << setw(16) << surplusBuffalos << setw(16) << waterDeficit
		<< setw(16) << needBuffalos << endl;

	   // Calculate overall totals
	   totalRefugees += numOfRefugees;
	   totalWaterSurplus += waterSurplus;
	   totalSurplusBuffalos += surplusBuffalos;
	   totalWaterDeficit += waterDeficit;
	   totalNeedBuffalos += needBuffalos;
	 }
  }

  // Close inputFile after reading data
  inputFile.close();

  // Output footer divider and totals
  cout << setw(8) << "--------" << setw(16) << "--------" << setw(16) << "--------"
       << setw(16) << "--------" << setw(16) << "--------" << setw(16) << "--------" << endl;
  cout << setw(8) << "Totals: " << setw(16) << totalRefugees << setw(16)
       << totalWaterSurplus << setw(16) << totalSurplusBuffalos << setw(16)
       << totalWaterDeficit << setw(16) << totalNeedBuffalos << endl;

  // Output error message for no data in file
  if (totalRefugees == 0 && totalWaterSurplus == 0 && totalSurplusBuffalos == 0 &&
      totalWaterDeficit == 0 && totalNeedBuffalos ==0) {
    cout << endl << "WARNING: There was no data in the file." << endl << endl;
    return 0;
  }

  // Output error message for no refugee in ALL camps
  if (totalRefugees == 0) {
    cout << endl << "WARNING: There were no refugees in all camps." << endl << endl;
    return 0;
  }
    return 0;
}
