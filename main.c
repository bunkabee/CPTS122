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
 * Format of output file (Results.csv): See PA1 Assignment Description        *
 *****************************************************************************/

#include "fitbit.h"

int main() {

	// Open input and output files
	FILE* infile = fopen("FitbitData.csv", "r");
	FILE* outfile = fopen("Results.csv", "w");

	// allocate space for patientData array
	// used calloc to allocate memory on heap
	FitbitData* patientData = calloc(MINUTES_MAX, sizeof(FitbitData));
	
	// if file cannot be opened print error
	if (!infile || !outfile) {
		perror("The following error has occured. Unable to run.");
	}
	else {

		// read data into patientData
		read_file(infile, patientData);

		// write data to output file and console
		write_data(outfile, patientData);

		// close input and output files
		fclose(outfile);
		fclose(infile);
	}

	// free memory allocated for patientData
	free(patientData);

	return 0;
}