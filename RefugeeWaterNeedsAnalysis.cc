/**
 *
 * Project 1
 * Refugee Water Needs Analysis
 * Leslie Kim
 * NettID: lk584
 * COSC 051
 * Section 02
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance
 * on this project with the exceptions of the lecture notes and those
 * items noted below.
 * Any help items: NA
 * Description: <This program will determine the water needs for a refugee
 * camp based on the number of refugees, daily water needs  and the existing
 * water supplies.>
 *
 **/

#include <iostream>
#include <math.h>
using namespace std;

int main() {

  // Define variables
  int numberOfRefugees = 0;
  double dailyWaterNeeds = 0; // measured in liters/person/day
  int numberOfTaps = 0;
  double waterTapsProvide = 0.0; // unless noted, all water measured in liters
  int numberOfPumps = 0;
  double waterPumpsProvide = 0.0;
  int numberOfWells = 0;
  double waterWellsProvide = 0.0;
  double totalWaterNeeds = 0.0;
  double totalWaterAvailable = 0.0;
  double waterExcess = 0.0;
  double waterShortage = 0.0;
  int additionalRefugees = 0;
  int additionalWaterBuffalo = 0;
  double additionalWaterAvailable = 0.0;
  double consumedWater = 0.0;

  // Define constants
  const double minWater = 7.5; // liters/person/day
  const int maxWater = 15; // liters/person/day

  // Define constant water sources provisions (measured in liters/minute)
  const double tapFlow = 7.5;
  const int  handPumpFlow = 17;
  const double openWellFlow = 12.5;
  const int accessTime = 480; // 8 hours/day = 480 minutes/day
  const double waterBuffalo = 1514.164; // number of liters one provides per day

  // Output program description
  cout << endl
       << "This program will determine the water needs for a refugee camp" << endl
       << "based on the number of refugees, daily water needs and the" << endl
       << "existing water supplies. The information you will need to input" << endl
       << "are the number of refugees, amount of daily water needs per" << endl
       << "person and the amount of each existing water supplier."
       << endl << endl;

  // Ask how many refugees are in the camp
  cout << "Please enter the number of refugees in the camp: ";
  cin >> numberOfRefugees;

  // Check if numberOfRefugees is valid value
  if (numberOfRefugees < 0) {
    cout << endl
	 << "WARNING: There cannot be a negative number of refugees." << endl << endl;
    return 0;
  }
  else if (numberOfRefugees == 0) {
    cout << "WARNING: There are no refugees in the camp to provide water for."
	 << endl << endl;
  }
  else {
    cout << endl;
  }

  // Ask how many liters of water each refugee needs per day
  cout << "Please enter how many liters each refugee needs per day" << endl
       << "(float between 7.5 - 15 liters/day): ";
  cin >> dailyWaterNeeds;

  // Check if dailyWaterNeeds are within range
  if (dailyWaterNeeds < 0) {
    cout << endl
	 << "WARNING: Refugees cannot consume negative liters of water."
	 << endl << endl;
    return 0;
  }
  else if (dailyWaterNeeds == 0) {
    cout << endl
	 << "WARNING: The water needs entered are not within range of the" << endl
	 << "minimum standards in water supply, sanitation and hygiene" << endl
	 << "promotion according to the Sphere Project Minimum Standards" << endl
	 << "in Humanitarian Response. Zero liters per day will lead to death."
	 << endl << endl;
    return 0;
  }
  else if ((dailyWaterNeeds > 0) && (dailyWaterNeeds < minWater)) {
    cout << endl
	 << "WARNING: The water needs entered are not within range of the" << endl
	 << "minimum standards in water supply, sanitation and hygiene" << endl
	 << "promotion according to the Sphere Project Minimum Standards" << endl
	 << "in Humanitarian Response." << endl << endl;
      return 0;
  }
  else if ((dailyWaterNeeds >= minWater) && (dailyWaterNeeds <= maxWater)) {
    cout << endl;
  }
  else if (dailyWaterNeeds > maxWater) {
    cout << endl
	 << "WARNING: The water needs entered exceed minimum standards in" << endl
	 << "water supply, sanitation and hygiene promotion according to" << endl
	 << "the Sphere Project Minimum Standards in Humanitarian Response." << endl
	 << endl;
  }

  // Ask for the number of working taps in camp
  cout << "Please enter the number of working taps in the camp: ";
  cin >> numberOfTaps;

  // Check if numberOfTaps is valid
  if (numberOfTaps < 0) {
    cout << "WARNING: There cannot be a negative number of taps." << endl << endl;
    return 0;
  }
 
  // Ask for the number of working pumps in camp
  cout << "Please enter the number of working hand pumps in the camp: ";
  cin >> numberOfPumps;

  // Check if numberOfPumps is valid
  if (numberOfPumps < 0) {
    cout << "WARNING: There cannot be a negative number of hand pumps." << endl << endl;
    return 0;
  }

  // Ask for the number of working open wells in camp
  cout << "Please enter the number of working open wells in the camp: ";
  cin >> numberOfWells;

  // Check if numberOfWells is valid
  if (numberOfWells < 0) {
    cout << "WARNING: There cannot be a negative number of open wells." << endl << endl;
    return 0;
  }

  // Calculate water provided by the number of sources that were input
  waterTapsProvide = numberOfTaps * tapFlow * accessTime;
  waterPumpsProvide = numberOfPumps * handPumpFlow * accessTime;
  waterWellsProvide = numberOfWells * openWellFlow * accessTime;
  totalWaterAvailable = waterTapsProvide + waterPumpsProvide + waterWellsProvide;

  // Calculate total water provided by sources
  totalWaterNeeds = numberOfRefugees * dailyWaterNeeds;

  // Calculate water excess or shortage
  if (totalWaterAvailable >= totalWaterNeeds) {
    waterExcess = totalWaterAvailable - totalWaterNeeds;
     // Calculate how much excess and additional refugees there is room for
    if (waterExcess == 0) {
      cout << endl
	   << "There is exactly enough water for the camp. There is not enough for" << endl
	   << "additional refugees."
	   << endl << endl;
    }
    else if (waterExcess > 0) {
      // Calculate how many additionalRefugees there is room for
      additionalRefugees = floor(waterExcess/dailyWaterNeeds);
      cout << endl
	   << "There is an excess of water of " << waterExcess << " liters/day." << endl
	   << "There is adequate water for the camp and enough water for "
	   << additionalRefugees << " more refugees." << endl << endl;
      }
    else if (waterExcess < 0) {
      cout << endl 
	   << "WARNING: Error in calculations." << endl << endl;
      return 0;
    }
  }

  else if (totalWaterAvailable < totalWaterNeeds) {
    // Calculate how much shortage and number of Water Buffalos needed
    waterShortage = totalWaterNeeds - totalWaterAvailable;
    cout << endl
	 << "The camp has a water shortage of " << waterShortage << " liters/day." << endl;
    // Calculate how many M-149 Water Buffalo Trailers are needed
    additionalWaterBuffalo = ceil(waterShortage/waterBuffalo);
    cout << "The camp needs an additional " << additionalWaterBuffalo
	 << " M-149 Water Buffalo Trailers each day." << endl;
    // Calculate how many more refugees there is room for with excess from Water Buffalo
    // Trailers
    totalWaterAvailable = totalWaterAvailable + (additionalWaterBuffalo * waterBuffalo);
    consumedWater = numberOfRefugees * dailyWaterNeeds;
    additionalWaterAvailable = totalWaterAvailable - consumedWater;
    additionalRefugees = floor(additionalWaterAvailable/dailyWaterNeeds);
    cout << "With the extra water from the M-149 Water Buffalos, there is also room"
	 << endl << "for " << additionalRefugees << " additional refugees in the camp."
	 << endl << endl;
  }

  else {
    cout << endl
	 <<  "WARNING: Error in calculations." << endl;
    return 0;
  }

  return 0;
}
