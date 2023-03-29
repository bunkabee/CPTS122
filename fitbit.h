/*******************************************************************************
 * Programmer: Kendelle Innis                                                  *
 * Class: CptS 122; Lab Section 11                                             *
 * Programming Assignment: PA1                                                 *
 * Date: 01.22.2023                                                            *
 *                                                                             *
 * Description: Reads Fitbit data from a file. Removes duplicates and          *
 *              cleanses data for accuracy. Calculates information from        *
 *              cleansed/deduped data.                                         *   
 *                                                                             *
 * Relevant Formulas: Refer to each function definition.                       *
 *                                                                             *
 * Format of record in input file (FitbitData.csv):                            *
 *			Patient,minute,calories,distance,floors,heart,steps,sleep_level    *	
 *                                                                             *
 * Format of output file (Results.csv): Same as input file.                    *
 ******************************************************************************/

#ifndef FITBIT_H
#define FITBIT_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINUTES_MAX 1440

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

/*************************************************************
 * Function: read_file(FILE*, FitbitData)                    *
 * Date Created:.01.22.23                                    *
 * Date Last Modified:                                       *
 * Description: Reads file and parses data line by line      *
 * Input parameters: input file pointer, FitbitData struct   *
 * Returns: Nothing - void                                   *
 * Preconditions: input file must be open                    *
 * Postconditions: none                                      *
 *************************************************************/
void read_file(FILE* infile, FitbitData* pdata);


/*************************************************************
 * Function: write_file(FILE*, FitbitData)                   *
 * Date Created:.01.22.23                                    *
 * Date Last Modified: 01.26.23                              *
 * Description: outputs data stored in FitbitData array to a *
 *				to a file and the console    				 *
 * Input parameters: output file pointer, FitbitData struct  *
 * Returns: Nothing - void                                   *
 * Preconditions: output file must be open                   *
 * Postconditions: none                                      *
 *************************************************************/
void write_data(FILE* outfile, FitbitData* pdata);

/*************************************************************
 * Function: total_calories(FitbitData)                      *
 * Date Created:.01.22.23                                    *
 * Date Last Modified:                                       *
 * Description: calculates total calories burned in 24-hour  *
 *				period. 									 *
 * Input parameters: pointer to FitbitData                   *
 * Returns: double - sum of all calories in found in array   *
 * Preconditions: data must be read into pdata               *
 * Postconditions: none                                      *
 *************************************************************/
double total_calories(FitbitData* pdata);

/*************************************************************
 * Function: total_distance(FitbitData)                      *
 * Date Created:.01.22.23                                    *
 * Date Last Modified:                                       *
 * Description: calculates total distance walked in 24-hour  *
 *				period. 									 *
 * Input parameters: pointer to FitbitData                   *
 * Returns: double - sum of distances walked found in array  *
 * Preconditions: data must be read into pdata               *
 * Postconditions: none                                      *
 *************************************************************/
double total_distance(FitbitData* pdata);

/*************************************************************
 * Function: total_floors(FitbitData)                        *
 * Date Created:.01.22.23                                    *
 * Date Last Modified:                                       *
 * Description: calculates total floors climbed in 24-hour   *
 *				period. 									 *
 * Input parameters: pointer to FitbitData                   *
 * Returns: unsigned int - sum of floors climbed found in    *
 *						array                                *
 * Preconditions: data must be read into pdata               *
 * Postconditions: none                                      *
 *************************************************************/
unsigned int total_floors(FitbitData* pdata);

/*************************************************************
 * Function: total_steps(FitbitData)                         *
 * Date Created:.01.22.23                                    *
 * Date Last Modified:                                       *
 * Description: calculates total steps taken in 24-hour      *
 *				period. 									 *
 * Input parameters: pointer to FitbitData                   *
 * Returns: unsigned - sum of steps taken found in array     *
 * Preconditions: data must be read into pdata               *
 * Postconditions: none                                      *
 *************************************************************/
unsigned int total_steps(FitbitData* pdata);

/*************************************************************
 * Function: avg_heartRate(FitbitData)                       *
 * Date Created:.01.22.23                                    *
 * Date Last Modified:                                       *
 * Description: calculates average heartrate over 24-hour    *
 *				period. 									 *
 * Input parameters: pointer to FitbitData                   *
 * Returns: unsigned - average of all heartrates in array    *
 * Preconditions: data must be read into pdata               *
 * Postconditions: none                                      *
 *************************************************************/
unsigned int avg_heartRate(FitbitData* pdata);

/*************************************************************
 * Function: total_distance(FitbitData)                      *
 * Date Created:.01.22.23                                    *
 * Date Last Modified: 01.26.23                              *
 * Description: finds when most amount of steps were taken   *
 *				in one minute								 *
 * Input parameters: pointer to FitbitData                   *
 * Returns: unsigned int - index of max steps                *
 * Preconditions: data must be read into pdata               *
 * Postconditions: none                                      *
 *************************************************************/
unsigned int max_steps(FitbitData* pdata);

/*************************************************************
 * Function: sleep_totals(FitbitData)                        *
 * Date Created:.01.23.23                                    *
 * Date Last Modified:                                       *
 * Description: finds range of worst sleep   				 *
 * Input parameters: pointer to FitbitData                   *
 * Returns: char* - range of minutes where worse sleep       * 
 *			occured                                          *
 * Preconditions: data must be read into pdata               *
 * Postconditions: none                                      *
 *************************************************************/
char* sleep_totals(FitbitData* pdata);

#endif

