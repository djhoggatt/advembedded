/*
 * Team 11  CS 5785
 * Unit Tests for decide.c
 * SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
  */

#include <stdio.h>
#include <stdlib.h>
#include "decide.h"
#include "limits.h"

// -- Forward Declarations -- //
int initialize_globals(void);
int clean_globals(void);


int main()
{
initialize_globals();


// -- LIC0 Tests -- //

// LIC0-Test1 

X[0] = 0;
Y[0] = 0;
X[1] = 0;
Y[1] = 0;
boolean test_passed = 1;

PARAMETERS.LENGTH1 = 1,000,000;  // max according to func. req #3 
while ( PARAMETERS.LENGTH1 > 0 )
{
  DECIDE();
  if (CMV[0] != 0) { test_passed = 0; }
  PARAMETERS.LENGTH1 = PARAMETERS.LENGTH1 - 0.001;  // max precision
}

PARAMETERS.LENGTH1 = -1,000,000;  // max according to func. req #3 
while ( PARAMETERS.LENGTH1 < 0 )
{
  DECIDE();
  if (CMV[0] == 0) { test_passed = 0; }
  PARAMETERS.LENGTH1 = PARAMETERS.LENGTH1 + 0.001;  // max precision
}

printf( "LIC0-Test1 %s\n", (test_passed == 1) ? "PASSED.": "FAILED." );
clean_globals();


return 0;
}


// -- Helper Functions -- //

/*
 * This function initializes all the globals needed to
 * needed to call decide()
 */
int initialize_globals(void)
{ 
  // Initialize CMV: 1x15 boolean
  CMV = malloc( sizeof(boolean)*15 );
  for(int i=0; i<15 ; i++) { CMV[i] = 0; }  // all false
 
  // Initialize LCM: 15x15 ANDD, ORR, NOTUSED
  LCM = (CONNECTORS**) malloc(15*sizeof(CONNECTORS*));
  for(int i=0; i<15 ; i++) { LCM[i] = (CONNECTORS*)malloc(15*sizeof(CONNECTORS)); }
    
  for(int i=0; i<15; i++)
  {
  for(int j=0; j<15; j++) { LCM[i][j] = NOTUSED; }
  }
 
  // Initialize PUM: 15x15 boolean
  PUM = (boolean**) malloc(15*sizeof(boolean*));
  for(int i=0; i<15 ; i++) { PUM[i] = (boolean*)malloc(15*sizeof(boolean)); }
	
  for(int i=0; i<15; i++)
  {
    for(int j=0; j<15; j++)
    {
     if(i==j)
      PUM[i][j]=1;  // diagonals = true
     else
       PUM[i][j] = 0; // rest = false
    }
  }
  // Initialize FUV: 1x15 boolean
  FUV = malloc( sizeof(boolean)*15 );
  for(int i=0; i<15; i++) { FUV[i] = 0; }  // all false
  
  // Initialize Parameters Struct with Any Numbers
  PARAMETERS.LENGTH1 = 816064.687;    // Length in LICs 0, 7, 12
  PARAMETERS.RADIUS1 = 513054.8828;   // Radius in LICs 1, 8, 13
  PARAMETERS.EPSILON = 1.32225;       // Deviation from PI in LICs 2, 9
  PARAMETERS.AREA1   = 800283.1163;   // Area in LICs 3, 10, 14
  PARAMETERS.Q_PTS   = 5;             // No. of consecutive points in LIC 4
  PARAMETERS.QUADS   = 2;             // No. of quadrants in LIC 4
  PARAMETERS.DIST    = 554724.335;    // Distance in LIC 6
  PARAMETERS.N_PTS   = 4;             // No. of consecutive pts. in LIC 6
  PARAMETERS.K_PTS   = 4;             // No. of int. pts. in LICs 7, 12
  PARAMETERS.A_PTS   = 4;             // No. of int. pts. in LICs 8, 13
  PARAMETERS.B_PTS   = 4;             // No. of int. pts. in LICs 8, 13
  PARAMETERS.C_PTS   = 4;             // No. of int. pts. in LIC 9
  PARAMETERS.D_PTS   = 4;             // No. of int. pts. in LIC 9
  PARAMETERS.E_PTS   = 4;             // No. of int. pts. in LICs 10, 14
  PARAMETERS.F_PTS   = 4;             // No. of int. pts. in LICs 10, 14
  PARAMETERS.G_PTS   = 4;             // No. of int. pts. in LIC 11
  PARAMETERS.LENGTH2 = 507202.792;    // Maximum length in LIC 12
  PARAMETERS.RADIUS2 = 559839.0403;   // Maximum radius in LIC 13
  PARAMETERS.AREA2   = 650689.2825;   // Maximum area in LIC 14
  
  // Number of Points
  NUMPOINTS = 100;
  
  // X and Y initialize to 0
  X = malloc(sizeof(double)*NUMPOINTS);
  Y = malloc(sizeof(double)*NUMPOINTS);
  for(int i=0; i<NUMPOINTS; i++)
  { 
    X[i] = 0;
    Y[i] = 0;
  }
    
  return 0;
} // end nitialize_globals()

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
