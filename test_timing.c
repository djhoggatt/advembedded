/*
* Team 11  CS 5785
* Unit Tests for decide.c
* SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
*/

#include <stdio.h>
#include <stdlib.h>
#include "decide.h"
#include "limits.h"
#include <time.h>

const  int NANO_TO_SEC = 1000000000;

// -- Forward Declarations -- //
int initialize_globals(void);
int clean_globals(void);

struct timespec start_time;
struct timespec end_time;

int main()
{
	double run_time;
	initialize_globals();
	FILE *fp;
	fp = fopen("cdf.txt", "w");

	// -- LIC0 Tests -- //

	// LIC0-Test1

	X[0] = 0;
	Y[0] = 0;
	X[1] = 0;
	Y[1] = 0;
	boolean test_passed = 1;
	int i;

	//timing harness

	X[0] = 2.5238;
	X[1] = -8.32321;
	X[2] = 0;
	X[3] = 123.321;
	X[4] = -38291.133235;
	X[5] = 8381.382015;
	X[6] = 1.0001;

	Y[0] = -9913893.1355;
	Y[1] = 1;
	Y[2] = 123252.235;
	Y[3] = -6346.2;
	Y[4] = -3.3;
	Y[5] = 0;
	Y[6] = 5323821;

	for(i = 0; i < 1000000; i++)
	{
		clock_gettime(CLOCK_MONOTONIC, &start_time);
		DECIDE();
		clock_gettime(CLOCK_MONOTONIC, &end_time);
		
		run_time = (end_time.tv_sec - start_time.tv_sec) + ((double)(end_time.tv_nsec - start_time.tv_nsec)/NANO_TO_SEC);
		
		fprintf(fp, "%lf\n", run_time);
	}
	fclose(fp);
// 	PARAMETERS.LENGTH1 = 1,000,000;  // max according to func. req #3
// 	while ( PARAMETERS.LENGTH1 > 0 )
// 	{
// 		DECIDE();
// 		if (CMV[0] != 0) { test_passed = 0; }
// 		PARAMETERS.LENGTH1 = PARAMETERS.LENGTH1 - 0.001;  // max precision
// 	}
// 
// 	PARAMETERS.LENGTH1 = -1,000,000;  // max according to func. req #3
// 	while ( PARAMETERS.LENGTH1 < 0 )
// 	{
// 		DECIDE();
// 		if (CMV[0] == 0) { test_passed = 0; }
// 		PARAMETERS.LENGTH1 = PARAMETERS.LENGTH1 + 0.001;  // max precision
// 	}
// 
// 	printf( "LIC0-Test1 %s\n", (test_passed == 1) ? "PASSED.": "FAILED." );
// 	clean_globals();
	
	// LIC1 Tests
	/* all should return true except for the last one */
	
	test_passed = 1;
	
	/* makes perfect line, radius would need to be 212.132*/
	X[0] = 0;
	Y[0] = 0;
	X[1] = 10;
	Y[1] = 10;
	X[2] = 300;
	Y[2] = 300;
	
	DECIDE();
	if(CMV[1] == 0) 
	{
		test_passed = 0;
	}
	
	/* makes perfect line radius would need to be 212.132*/
	X[0] = 10;
	Y[0] = 10;
	X[1] = 300;
	Y[1] = 300;
	X[2] = 0;
	Y[2] = 0;
	
	DECIDE();
	if(CMV[1] == 0)
	{
		test_passed = 0;
	}
	
	/* makes perfect line radius would need to be 212.132*/
	X[0] = 300;
	Y[0] = 300;
	X[1] = 0;
	Y[1] = 0;
	X[2] = 10;
	Y[2] = 10;
	
	DECIDE();
	if(CMV[1] == 0)
	{
		test_passed = 0;
	}
	
	/* b greater than a, r greater than b */
	/* makes perfect line radius would need to be 212.132*/
	X[0] = 10;
	Y[0] = 10;
	X[1] = 0;
	Y[1] = 0;
	X[2] = 300;
	Y[2] = 300;
		
	DECIDE();
	if(CMV[1] == 0)
	{
		test_passed = 0;
	}
	
	/* test triangles */
	
	/* makes a right triangle */
	X[0] = 0;
	Y[0] = 0;
	X[1] = 300;
	Y[1] = 300;
	X[2] = 300;
	Y[2] = 0;
	
	DECIDE();
	if(CMV[1] == 0)
	{
		test_passed = 0;
	}	
	
	/* makes a triangle with angle 1 obtuse */
	X[0] = 300;
	Y[0] = 300;
	X[1] = 300;
	Y[1] = 10;
	X[2] = 0;
	Y[2] = 0;
		
	DECIDE();
	if(CMV[1] == 0)
	{
		test_passed = 0;
	}
		
	/* makes a triangle with angle 2 obtuse */
	X[0] = 0;
	Y[0] = 0;
	X[1] = 300;
	Y[1] = 300;
	X[2] = 300;
	Y[2] = 10;
		
	DECIDE();
	if(CMV[1] == 0)
	{
		test_passed = 0;
	}
	
	/* makes a triangle with angle 3 obtuse */
	X[2] = 10;
	Y[2] = -100;
	X[1] = 300;
	Y[1] = 300;
	X[0] = 0;
	Y[0] = 0;
		
	DECIDE();
	if(CMV[1] == 0)
	{
		test_passed = 0;
	}
	
	/* returns false for the first time a line smaller than RADIUS1*2 */
	X[0] = 0;
	Y[0] = 0;
	X[1] = 0;
	Y[1] = 0;
	X[2] = 20;
	Y[2] = 20;
	
	DECIDE();
	if(CMV[1] == 1)
	{
		test_passed = 0;
	}

	
	printf("LIC1-Test1 %s\n", (test_passed ==1) ? "PASSED": "FAILED");

	clean_globals();

	return 0;
}


// -- Helper Functions -- //

/*
* This function initializes all the globals needed to
* call decide()
*/
int initialize_globals(void)
{
	int i, j;
	// Initialize CMV: 1x15 boolean
	CMV = malloc( sizeof(boolean)*15 );
	for( i=0; i<15 ; i++) { CMV[i] = 0; }  // all false
	
	// Initialize LCM: 15x15 ANDD, ORR, NOTUSED
	LCM = (CONNECTORS**) malloc(15*sizeof(CONNECTORS*));
	for(i=0; i<15 ; i++) { LCM[i] = (CONNECTORS*)malloc(15*sizeof(CONNECTORS)); }
	
	for(i=0; i<15; i++)
	{
		for(j=0; j<15; j++) { LCM[i][j] = NOTUSED; }
	}
	
	// Initialize PUM: 15x15 boolean
	PUM = (boolean**) malloc(15*sizeof(boolean*));
	for(i=0; i<15 ; i++) { PUM[i] = (boolean*)malloc(15*sizeof(boolean)); }
	
	for(i=0; i<15; i++)
	{
		for(j=0; j<15; j++)
		{
			if(i==j)
			PUM[i][j]=1;  // diagonals = true
			else
			PUM[i][j] = 0; // rest = false
		}
	}
	// Initialize FUV: 1x15 boolean
	FUV = malloc( sizeof(boolean)*15 );
	for(i=0; i<15; i++) { FUV[i] = 0; }  // all false
	
	// Initialize Parameters Struct with Any Numbers
	PARAMETERS.LENGTH1 = 816064.687;    // Length in LICs 0, 7, 12
	PARAMETERS.RADIUS1 = 210.323;	    // Radius in LICs 1, 8, 13
	PARAMETERS.EPSILON = 1.32225;       // Deviation from PI in LICs 2, 9
	PARAMETERS.AREA1   = 800283.1163;   // Area in LICs 3, 10, 14
	PARAMETERS.Q_PTS   = 5;             // No. of consecutive points in LIC 4
	PARAMETERS.QUADS   = 2;             // No. of quadrants in LIC 4
	PARAMETERS.DIST    = 554724.335;    // Distance in LIC 6
	PARAMETERS.N_PTS   = 2;             // No. of consecutive pts. in LIC 6
	PARAMETERS.K_PTS   = 4;             // No. of int. pts. in LICs 7, 12
	PARAMETERS.A_PTS   = 3;             // No. of int. pts. in LICs 8, 13
	PARAMETERS.B_PTS   = 1;             // No. of int. pts. in LICs 8, 13
	PARAMETERS.C_PTS   = 4;             // No. of int. pts. in LIC 9
	PARAMETERS.D_PTS   = 1;             // No. of int. pts. in LIC 9
	PARAMETERS.E_PTS   = 1;             // No. of int. pts. in LICs 10, 14
	PARAMETERS.F_PTS   = 3;             // No. of int. pts. in LICs 10, 14
	PARAMETERS.G_PTS   = 2;             // No. of int. pts. in LIC 11
	PARAMETERS.LENGTH2 = 507202.792;    // Maximum length in LIC 12
	PARAMETERS.RADIUS2 = 559839.0403;   // Maximum radius in LIC 13
	PARAMETERS.AREA2   = 650689.2825;   // Maximum area in LIC 14
	
	// Number of Points
	NUMPOINTS = 7;
	//NUMPOINTS = 100;
	
	// X and Y initialize to 0
	X = malloc(sizeof(double)*NUMPOINTS);
	Y = malloc(sizeof(double)*NUMPOINTS);
	for(i=0; i<NUMPOINTS; i++)
	{
		X[i] = 0;
		Y[i] = 0;
	}
	
	return 0;
} // end initialize_globals()

/*
* This function frees all the malloc'd memory for initialized arrays
*/
int clean_globals(void)
{
	free(CMV);
	free(LCM);
	free(PUM);
	free(FUV);
	return 0;
} // end clean_globals()

