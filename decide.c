/*
 * Team 11  CS 5785
 * Team Assignment #1
 * SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
 *
 */
 
#include "decide.h"
#include <math.h>


void DECIDE()
{
/* 
 * Should we Launch?
 *  Check all the elements of the Final Unlocking Vector (FUV)
 *  for any FALSE entries. If there are any FALSE entries then
 *  we should not launch (LAUNCH = 0).
 */
for( i=0; i<15; i++ )
{ 
   if(FUV[i] == 0) { LAUNCH = 0; }
}

} // end DECIDE