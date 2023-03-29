/******************************************************************************
 * Programmer: Kendelle Innis                                                 *
 * Class: CptS 122; Lab Section 11                                            *
 * Programming Assignment: PA1                                                *
 * Date: 01.22.2023                                                           *
 *                                                                            *
 * Description: Reads Fitbit data from a file. Removes duplicates and         *
 *              cleanses data for accuracy. Calculates information fro        *
 *              cleansed/deduped data.                                        *
 *                                                                            *
 * Relevant Formulas: Refer to function definitions in fitbit.h               *
 *                                                                            *
 * Format of record in input file (FitbitData.csv):                           *
 *			Patient,minute,calories,distance,floors,heart,steps,sleep_level   *
 *                                                                            *
 * Format of output file (Results.csv): Same as input file.                   *
 *****************************************************************************/

#include "fitbit.h"

void read_file(FILE* infile, FitbitData* pdata) {

	// variable to store value read from line
	char line[100] = "";

	// variable to store target patient
	char targetPatient[10] = "";

	// read in entire first line up to 100 char
	fgets(line, 100, infile);

	// read from start of line to first ",";
	// store value in remaining
	// we don't care about this descriptor
	char* remaining = strtok(line, ",");

	// read from last point to next ",";
	// overwrite remaining with value
	// value stored at remaining should now be target patient number
	remaining = strtok(NULL, ",");

	// Target Patient should be the value at remaining
	// copy value from remaining into target patient. 
	strcpy(targetPatient, remaining);

	// skip 2nd line of file
	fgets(line, 100, infile);

	// variable to store number of minutes actually read and stored
	int minuteCount = 0;

	// while we are not at the end of the file
	while (fgets(line, 100, infile) != NULL) {

		// store first value read in remaining
		remaining = strtok(line, ",");

		// compare first token to value in target_patient
		// if both strings are identical, add to pdata array. 
		if (strcmp(remaining, targetPatient) == 0) {
			strcpy(pdata[minuteCount].patient, remaining);
		}

		// otherwise, skip line and start next line
		else {
			continue;
		}

		// get minutes from file.
		// copy string into array
		remaining = strtok(NULL, ",");

		// if the minute read is already read into the array,
		// skip the line and start at next line
		if (strcmp(remaining, pdata[minuteCount - 1].minute) == 0) {
			continue;
		}

		// otherwise, copy data into array
		strcpy(pdata[minuteCount].minute, remaining);

		// get calories from line
		// convert string to double and store in array
		remaining = strtok(NULL, ",");
		pdata[minuteCount].calories = atof(remaining);

		// get distace from line
		// convert to double and store in array
		remaining = strtok(NULL, ",");
		pdata[minuteCount].distance = atof(remaining);

		// get floors from line
		// convert to unsigned int and store in array
		remaining = strtok(NULL, ",");
		pdata[minuteCount].floors = (unsigned int)atoi(remaining);

		// get heart rate from line
		// convert to unsigned int and store in array
		remaining = strtok(NULL, ",");
		pdata[minuteCount].heartRate = (unsigned int)atoi(remaining);

		// get steps from line
		// convert to unsigned int and store in array
		remaining = strtok(NULL, ",");
		pdata[minuteCount].steps = (unsigned int)atoi(remaining);

		// get sleepLevel from line
		// convert to unsigned int and store in array
		remaining = strtok(NULL, ",");
		
		// if remaining does not equal NULL
		// assign int value to sleeplevel
		if (remaining != NULL)
		{
			pdata[minuteCount].sleepLevel = atoi(remaining);
		}
		
		// move pdata to next position.
		minuteCount++;
	}
}

void write_data(FILE* outfile, FitbitData* pdata) {
	
	// Print first header line to outfile
	fprintf(outfile, "Total Calories,Total Distance,Total Floors,Total Steps,");
	fprintf(outfile, "AVG Heartrate, Max Steps, Sleep\n");

	// Print first header line to console
	printf("Total Calories,Total Distance,Total Floors,Total Steps,");
	printf("AVG Heartrate, Max Steps, Sleep\n");

	// Print second header line to outfile
	fprintf(outfile, "%.9lf,%.9lf,%d,%d,%d,%d at %s,%s\n", total_calories(pdata), 
			total_distance(pdata), total_floors(pdata), total_steps(pdata),
			avg_heartRate(pdata), pdata[max_steps(pdata)].steps, 
			pdata[max_steps(pdata)].minute, sleep_totals(pdata));

	// Print second header line to console
	printf("%.9lf,%.9lf,%d,%d,%d,%d at %s,%s\n", total_calories(pdata),
		total_distance(pdata), total_floors(pdata), total_steps(pdata),
		avg_heartRate(pdata), pdata[max_steps(pdata)].steps,
		pdata[max_steps(pdata)].minute, sleep_totals(pdata));

	// Print each record to outfile
	for (int i = 0; i < MINUTES_MAX; i++) {
		fprintf(outfile, "%s,%s,%.9lf,%.9lf,%d,%d,%d,%d\n", 
				pdata[i].patient, pdata[i].minute, pdata[i].calories, 
				pdata[i].distance, pdata[i].floors, pdata[i].heartRate, 
				pdata[i].steps, pdata[i].sleepLevel);
	}
}

double total_calories(FitbitData* pdata) {

	// variable to store total
	double total = 0;

	// add each pdata calorie item to total
	for (int i = 0; i < MINUTES_MAX; i++) {
		total += pdata[i].calories;
	}

	// return sum of all calorie items
	return total;
}

double total_distance(FitbitData* pdata) {

	// variable to store total
	double total = 0;

	// add each pdata distance to total
	for (int i = 0; i < MINUTES_MAX; i++) {
		total += pdata[i].distance;
	}

	// return sum of all distance items
	return total;
}

unsigned int total_floors(FitbitData* pdata) {
	
	// variable to store total
	unsigned int total = 0;

	// add each pdata floor to total
	for (int i = 0; i < MINUTES_MAX; i++) {
		total += pdata[i].floors;
	}

	// return sum of all floor items
	return total;
}

unsigned int total_steps(FitbitData* pdata) {

	// variable to store total
	unsigned int total = 0;

	// add each pdata steps to total
	for (int i = 0; i < MINUTES_MAX; i++) {
		total += pdata[i].steps;
	}

	// return sum of all steps
	return total;
}

unsigned int avg_heartRate(FitbitData* pdata) {

	// variable to store total
	unsigned int total = 0;

	// add each pdata heartrate to total
	for (int i = 0; i < MINUTES_MAX; i++) {
		total += pdata[i].heartRate;
	}

	// return the total divided by total number of minutes
	// avg = sum / count
	return total / MINUTES_MAX;
}

unsigned int max_steps(FitbitData* pdata) {

	// variable to store max steps
	unsigned int max = 0;

	// variable to store index; 
	unsigned int minute = 0;

	// starting from end of data, compare each step total to max
	// if step total is greater than max, set max to step total
	for (int i = (MINUTES_MAX - 1); i >= 0; i--) {
		if (pdata[i].steps > max) {
			max = pdata[i].steps;
			minute = i;
		}
	}

	// return max steps
	return minute;
}

char* sleep_totals(FitbitData* pdata) {

	int sum = 0;
	int countRange = 0;
	int maxSum = 0;
	char* startMinute[9] = { NULL };
	char* endMinute[9] = { NULL };
	char* range = calloc(strlen(startMinute) + strlen(endMinute), sizeof(char));

	// start at index 0
	for (int i = 0; i < MINUTES_MAX; i++) {

		// if sleepLevel at i is greater than 1 (awake or really awake)
		if (pdata[i].sleepLevel > 1) {

			// start range at i
			countRange = i;

			// check sleepLevel until sleepLevel is 1 or less
			// while sleepLevel is less than 1, add sleepLevel value to sum
			// and increase to countRange to get next index
			while (pdata[countRange].sleepLevel > 1) {

				sum += pdata[countRange].sleepLevel;
				countRange++;
			}

			// if sum is bigger than current maxsum
			// set maxsum to new sum
			// store first value of range in startMinute
			// store last value of range in endMinute
			if (sum > maxSum) {
				maxSum = sum;
				
				strcpy(startMinute, pdata[i].minute);
				strcpy(endMinute, pdata[countRange].minute);

			}
		}

		// reset sum to 0 
		sum = 0;
	}

	// copy value of startMinute into range
	strcpy(range, startMinute);

	// concatenate a : to end of range
	strcat(range, ":");

	// concatenate endMinute to end of range
	strcat(range, endMinute);

	// return range
	return range;
}