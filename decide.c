/*
 * Team 11  CS 5785
 * Team Assignment #1: decide.c
 * SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
  */
 
#include "decide.h"
#include <math.h>

// -- Forward Declarations -- //
double Calculate_Area_Triangle(double, double, double, double, double, double);
boolean all_elements_in_row_are_true(BMATRIX, int);

// -- Globals -- //
boolean LAUNCH = 0; // Default to no launch.

/* 
 *See requirements specification document for function contract.
*/
void DECIDE()
{
// -- CMV -- //
/* 
 * CMV[2]: There exists at least one set of three consecutive data points
 * that are the vertices of a triangle with area greater than AREA1.
 */
CMV[2] = 0;
for(i=0; i<(NUMPOINTS-2); ++i)
{
  double triangle_area = Calculate_Area_Triangle(X[i], Y[i], X[i+1], Y[i+1], X[i+2], Y[i+2])
  if(DOUBLECOMPARE(triangle_area, PARAMETERS.AREA1) == GT)
  {
   CMV[2] = 1;
   break; // only need one so can quit checking
  }
}

 
 
/* 
 * Use the logical operator stored in LCM and apply to the booleans 
 * stored in the CMV. Store the result in PUM. If "NOTUSED" is found 
 * in LCM then PUM defaults to 0 (FALSE).
 */
for(int i = 0; i < 15; i++ )
{
  for(int j = 0; j < 15; j++ ) 
  {
    if (LCM[i][j] == 0) { PUM[i][j] = (CMV[i] || CMV[j]); }
    else if (LCM[i][j] == 1) { PUM[i][j] = (CMV[i] && CMV[j]); }
    else PUM[i][j] = 0; 
  }
}

/* 
 * FUV[i] should be set to true if PUM[i,i] is false 
 * or if all elements in PUM row i are true. (See page 6
 * of the protocol.) 
 */
for(int i = 0; i < 15; i++ )
{  
  if ((PUM[i][i] == 0) || ( all_elements_in_row_are_true(PUM,i) )){ FUV[i] = 1; }
  else { FUV[i] = 0; }   
}

/* 
 * Should we Launch?
 * Check all the elements of the Final Unlocking Vector (FUV)
 * for any FALSE entries. If there are any FALSE entries then
 * we should not launch (LAUNCH = 0).
 */
boolean fuv_has_false = 0; 
for(int i = 0; i < 15; i++ )
{ 
  if (FUV[i] == 0) { fuv_has_false = 1; }
}
if (fuv_has_false == 0) { LAUNCH = 1; }
else { LAUNCH = 0; }


// -- Helper Functions -- //

/* 
 * This function calculates the area of a triangle
 * given three points in the same plane.
 * This function was modified from
 * http://www.softwareandfinance.com/Turbo_C/Triangle_Area_Perimeter.html
 */
double Calculate_Area_Triangle(double ax, double ay, double bx, double by, double cx, double cy)
{
    double A = sqrt((double)(bx-ax) * (bx-ax) + (by-ay) * (by-ay));
    double B = sqrt((double)(bx-cx) * (bx-cx) + (by-cy) * (by-cy));
    double C = sqrt((double)(ax-cx) * (ax-cx) + (ay-cy) * (ay-cy));
    double height = 0;
 
    // Heron's formula for area calculation
    // area = sqrt( s * (s-a) * (s-b) * (s-c))
    double s = (A + B + C) / 2;
    double area = sqrt( s * (s-A) * (s-B) * (s-C));
	return area;
}

/*
 * This function takes in a two by two boolean matrix and 
 * the index of a row number.  It returns 1 (TRUE) if all elements
 * in the given row are 1 (TRUE). Otherwise returns FALSE.
 */
boolean all_elements_in_row_are_true(BMATRIX two_by_two_matrix, int row)
{
  boolean all_elements_are_true = 1;
  // Loop through each element in the row
  for(int column = 0; column < 15; column++ )
  {
    if (two_by_two_matrix[row][column] == 0) { all_elements_are_true = 0; }
  }
  return all_elements_are_true;
} // end all_elements_in_row_are_true()


} // end DECIDE