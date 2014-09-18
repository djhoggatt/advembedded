/*
 * Team 11  CS 5785
 * Team Assignment #1
 * SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
 *
 */
 
#include "decide.h"
#include <math.h>

// -- Forward Declarations -- //
boolean all_elements_in_row_are_true(BMATRIX, int);

// -- Globals -- //
boolean LAUNCH = 0; // Default to no launch.

void DECIDE()
{
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