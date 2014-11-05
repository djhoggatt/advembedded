/*
* Team 11  CS 5785
* Team Assignment #1: decide.c
* SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
*/

#include "decide.h"
#include <math.h>

// -- Forward Declarations -- //
//LIC declaration
boolean LIC0();
boolean LIC1();
boolean LIC2();
boolean LIC3();
boolean LIC4();
boolean LIC5();
boolean LIC6();
boolean LIC7();
boolean LIC8();
boolean LIC9();
boolean LIC10();
boolean LIC11();
boolean LIC12();
boolean LIC13();
boolean LIC14();

//Helper method declaration
boolean all_elements_in_row_are_true(BMATRIX, int);
double Calculate_Area_Triangle(double, double, double, double ,double ,double);
double length_point(double ,double ,double ,double );
double circumcenter(double ,double ,double ,double ,double ,double );
double angle_points(double, double, double, double ,double ,double);
int Quadrant_point(double,double);

// -- Globals -- //
boolean LAUNCH = 0; // Default to no launch.

// -- Decide Implementation -- //
//See the requirements specification for details regarding the decide function requirements.
void DECIDE(void)
{
	//Initialization
	int i = 0;
	int j = 0;

	//CMV Initialization
	CMV[0] = LIC0();
	CMV[1] = LIC1();
	CMV[2] = LIC2();
	CMV[3] = LIC3();
	CMV[4] = LIC4();
	CMV[5] = LIC5();
	CMV[6] = LIC6();
	CMV[7] = LIC7();
	CMV[8] = LIC8();
	CMV[9] = LIC9();
	CMV[10] = LIC10();
	CMV[11] = LIC11();
	CMV[12] = LIC12();
	CMV[13] = LIC13();
	CMV[14] = LIC14();


	/*
	* Use the logical operators stored in the LCM and apply them to the booleans stored in the CMV. Store the 
	* results in PUM. If the logical operator is "NOTUSED" then PUM defaults to 0 (FALSE).
	*/
	for(i = 0; i < 15; i++ )
	{
		for(j = 0; j < 15; j++ )
		{
			if (LCM[i][j] == ORR) 
				PUM[i][j] = (CMV[i] || CMV[j]);
			else if (LCM[i][j] == ANDD)
				PUM[i][j] = (CMV[i] && CMV[j]);
			else 
				PUM[i][j] = 0;
		}
	}

	/*
	* Loop through the FUV. FUV[i] should be set to true if PUM[i,i] is false or if all elements in PUM row i 
	* are true.
	*/
	for( i = 0; i < 15; i++ )
	{
		if ((PUM[i][i] == 0) || ( all_elements_in_row_are_true(PUM,i) ))
			FUV[i] = 1;
		else
			FUV[i] = 0;
	}

	/*
	* Check all of the elements in the FUV for any false entries. If there are any false entries, then
	* we should not launch.
	*/
	LAUNCH = 0;
	for(i = 0; i < 15; i++ )
	{
		if (FUV[i] == 0)
			LAUNCH = 1;
	}

}

// -- LIC Implementation -- //
/*
* Launch Intercept Condition 0
* There exists at least one set of two consecutive data points that are a distance greater than the length,
* LENGTH1, apart.
*/
boolean LIC0()
{ 
	//Initialization
	int i;
	
	//Find the distance between all consecutive points, and compare them.
	for ( i = 0; i < NUMPOINTS - 1; i++)
	{  
		//If the distance between the points is greater than LENGTH1, return true.
		if(DOUBLECOMPARE(PARAMETERS.LENGTH1, length_point(X[i],Y[i],X[i+1],Y[i+1])))
			return 1;
	}
	
	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 1
* There exists at least one set of three consecutive data points that cannot all be contained within or on a 
* circle of radius RADIUS1.
*/
boolean LIC1()
{
	//Initialization
	int i;
	double a, b, r, ang1, ang2, ang3;
	
	/*
	* Three points in space can form either one of two basic shapes: a line or a triangle. If the slope of the
	* line formed by any two points equals that of any other combination, then the points lie on a single line.
	* If the slope of a line formed by any two points are different, then they form a triangle
	*/
	for( i = 0; i < NUMPOINTS - 2; i++)
	{
		//Determine if any of the points are the same. If all three points are the
		//if they are, then we know that the points form a line.
		//Otherwise, find the slop of the line
		if ((X[i] == X[i+1]) || (X[i+1] == X[i+2]) || (X[i] == X[i+2]) || (Y[i] == Y[i+1]) || (Y[i+1] == Y[i+2]) || (Y[i] == Y[i+2]))
		{
			a = 0.0;
			b = 0.0;
		}
		else
		{
			a = ((Y[i+2] - Y[i+1])/(X[i+2] - X[i+1]));
			b = ((Y[i] - Y[i+1])/(X[i] - X[i+1]));
		}
		
		//Decide if the points form a line or a triangle
		if(DOUBLECOMPARE(a,b) == EQ)
		{
			// If the points form a line, then compute the greatest separation between the points 
			//to find total length of the line.
			a = length_point(X[i],Y[i],X[i+1],Y[i+1]);
			b = length_point(X[i],Y[i],X[i+2],Y[i+2]);
			r = length_point(X[i+2],Y[i+2],X[i+1],Y[i+1]);
			
			//Find the longest distance formed by the three points, which should correspond to the total length
			//of the line.
			if (DOUBLECOMPARE(a,b) == GT)
			{ 
				if(DOUBLECOMPARE(a,r) == GT)
				{
					//If the The radius of the circle specified by RADIUS1 is greater than half the length of the
					//line, then return true.
					if (DOUBLECOMPARE((a/2),PARAMETERS.RADIUS1) == GT)
						return 1;
				}
				else
				{
					//If the The radius of the circle specified by RADIUS1 is greater than half the length of the
					//line, then return true.
					if (DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1) == GT)
						return 1;
				}
			}
			else
			{
				if(DOUBLECOMPARE(b,r) == GT)
				{
					//If the The radius of the circle specified by RADIUS1 is greater than half the length of the
					//line, then return true.
					if (DOUBLECOMPARE((b/2),PARAMETERS.RADIUS1) == GT)
					{
						return 1;
					}
				}
				else
				{
					//If the The radius of the circle specified by RADIUS1 is greater than half the length of the
					//line, then return true.
					if (DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1) == GT)
					{
						return 1;
					}
				}
			}
		}
		else
		{ 
			//Determine the three angles of the triangle
			ang1 = angle_points(X[i],Y[i],X[i+1],Y[i+1],X[i+2],Y[i+2]);
			ang2 = angle_points(X[i],Y[i],X[i+2],Y[i+2],X[i+1],Y[i+1]);
			ang3 = angle_points(X[i+1],Y[i+1],X[i],Y[i],X[i+2],Y[i+2]);
			
			//If the triangle is an acute or right triangle, then RADIUS 1 should be greater than or equal to the 
			//circumradius of the triangle. For obtuse triangles, the radius of circle must be greater than half 
			//the length of the longest side.
			if( (DOUBLECOMPARE(ang1,PI/2) < GT) && (DOUBLECOMPARE(ang2,PI/2) < GT) && (DOUBLECOMPARE(ang3,PI/2) < GT))
				r  = circumcenter(X[i],Y[i],X[i+1],Y[i+1],X[i+2],Y[i+2]);
			else
			{ 
				if(DOUBLECOMPARE(ang1,PI/2)==GT)
					r = (length_point(X[i],Y[i],X[i+2],Y[i+2]))/2;
				else if(DOUBLECOMPARE(ang2,PI/2)==GT)
					r = (length_point(X[i],Y[i],X[i+1],Y[i+1]))/2;
				else
					r = (length_point(X[i+1],Y[i+1],X[i+2],Y[i+2]))/2;
			}
			
			//Return true if the computes value is less than RADIUS1.
			if(DOUBLECOMPARE(PARAMETERS.RADIUS1,r) == LT)
				return 1;
		}
	}
	
	//If no points are found that satisfy the condition, return false.
	return 0;
}

boolean LIC2()
{ 
	int i;
	for(i=0; i<(NUMPOINTS-2); ++i)
	{  
		if (((DOUBLECOMPARE(X[i], X[i+1]) == EQ)&&(DOUBLECOMPARE(Y[i], Y[i+1]) == EQ))||((DOUBLECOMPARE(X[i+2], X[i+1]) == EQ)&&(DOUBLECOMPARE(Y[i+2], Y[i+1]) == EQ)))
		continue;
		else
		{
			double Angle = angle_points(X[i],Y[i],X[i+1],Y[i+1],X[i+2],Y[i+2]);
			if((DOUBLECOMPARE(Angle, PI - PARAMETERS.EPSILON) == LT)||(DOUBLECOMPARE(Angle, PI + PARAMETERS.EPSILON) == GT))
			{
				return 1;
				// only need one so can quit checking
			}
		}
	}
	return 0;
}
/*
* CMV[3]: There exists at least one set of three consecutive data points
* that are the vertices of a triangle with area greater than AREA1.
*/

boolean LIC3()
{ 
	int i;
	for(i=0; i<(NUMPOINTS-2); ++i)
	{
		double triangle_area = Calculate_Area_Triangle(X[i],Y[i],X[i+1],Y[i+1],X[i+2],Y[i+2]);
		if(DOUBLECOMPARE(triangle_area, PARAMETERS.AREA1) == GT)
		{
			return 1;
			// only need one so can quit checking
		}
	}
	return 0;
}

boolean LIC4() // commented out for now until bug is found
{ 
	int i,j,k,count,flag;
	int quad[100];
	for(i=0; i<(NUMPOINTS + 1 - PARAMETERS.Q_PTS); ++i)
	{ 
		count = 0;
		for(j=0;j<PARAMETERS.Q_PTS;++j)
		{ 
			quad[j] = Quadrant_point(X[i+j],Y[i+j]);
		}
		for(j=0;j<PARAMETERS.Q_PTS;++j)
		{ 
			flag = 0;
			for (k=j+1;k<PARAMETERS.Q_PTS;++k)
			{
				if(quad[j] == quad[k])
				{ 
					flag =1;
				}
			}
			if(flag == 0)
			{ count ++;}
			else
			continue;
		}
		if (count > PARAMETERS.QUADS)
		{return 1;}

	}
	return 0;
}

boolean LIC5()
{ int i;
	for(i=0; i<(NUMPOINTS-1); ++i)
	{
		if(DOUBLECOMPARE(X[i], X[i+1]) == GT)
		{
			return 1;
			// only need one so can quit checking
		}

	}
	return 0;
}

boolean LIC6()
{
	int ch,i,A,B,C,j,d;
        for(i=0; i<(NUMPOINTS + 1 - PARAMETERS.N_PTS); ++i)
	{    if((DOUBLECOMPARE(X[i],X[i + PARAMETERS.N_PTS -1]) == EQ)&&(DOUBLECOMPARE(Y[i],Y[i + PARAMETERS.N_PTS -1]) == EQ))
		{ for ( j =i + 1;j< i + PARAMETERS.N_PTS -1; j++)
		  {
                   d = length_point(X[i],Y[i],X[j],Y[j]);
		   ch=  DOUBLECOMPARE(PARAMETERS.DIST,d);
		   if(ch == LT)
			return 1;
		   }
                }
	     else
		{ A = ((Y[i + PARAMETERS.N_PTS -1]) - (Y[i]));
		  B = ((X[i]) - (X[i + PARAMETERS.N_PTS -1]));
		  C = (((-(X[i]))*A) + ((-(Y[i]))*B));
		  for ( j =i + 1;j< i + PARAMETERS.N_PTS -1; j++)
		   { d = (fabs( (A*X[j]) + (B*Y[j]) + C ))/(sqrt((A*A)+(B*B)));
                     ch=  DOUBLECOMPARE(PARAMETERS.DIST,d);
		     if(ch == LT)
			return 1;

                   }
		}
	}
        return 0;
}


/*
 * LIC[7]: There exists at least one set of points K, consecutive data points apart
 * that are a distance greater than the length, LENGTH1, apart.
 */

boolean LIC7()
{ int ch,i;
  double a;
  for( i = 0; i<NUMPOINTS-1; i++)
    {  //Finds distance between points and compares them
    if(((i+PARAMETERS.K_PTS + 1)>=NUMPOINTS)||(NUMPOINTS < 3))
     { return 0;
      }
 else {
       a = length_point(X[i],Y[i],X[i+PARAMETERS.K_PTS + 1],Y[i+PARAMETERS.K_PTS + 1]);
       ch=  DOUBLECOMPARE(PARAMETERS.LENGTH1,a);
       if(ch == LT)
         return 1;

      }
    }
   return 0;
}


/*
 * LIC[8]: There exists at least one set of three points, A and B consecutive data points apart that cannot all
 * be contained within or on a circle of radius RADIUS1
 * 3 points in space can form 2 basic shapes: Line or Triangle;
 * If Slope of the line formed by any 2 points eqauls that of any other combination, then the points lie on a single Line
 * If the Slope of a line formed by any two points are different, they form a Triangle
 */

boolean LIC8()
{ int ch,ch1,ch2,ch3,i;
  double a,b,r;

  for( i = 0; i<NUMPOINTS-2; i++)
    { if(((i+PARAMETERS.A_PTS + 1)>=NUMPOINTS)||((i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2)>=NUMPOINTS)||(NUMPOINTS < 5))
     { return 0;
      }
  else
    {
      //Finding slope of a line by standard formulae( Learnt in Highschool)

     a = ((Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1] - Y[i+PARAMETERS.A_PTS + 1])/(X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1] - X[i + PARAMETERS.A_PTS + 1]));
     b = ((Y[i] - Y[i+PARAMETERS.A_PTS + 1])/(X[i] - X[i+PARAMETERS.A_PTS + 1]));
     //Compares Slopes to decide if line or Triangle
     ch=  DOUBLECOMPARE(a,b);
       if(ch == EQ)
          {
            // Decidesthat it is a Line So copmute the greatest seperation between the points to find length of the line
            a = length_point(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1]);
            b = length_point(X[i],Y[i],X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1]);
            r = length_point(X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS+1],Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1]);
            
            //Compares 2 Lengths
            ch1 = DOUBLECOMPARE(a,b);
             if (ch1 == GT)
               { //Compares the greater of the 2 with the third
                 ch2 = DOUBLECOMPARE(a,r);
                  if(ch2 == GT)
                    {
                       //For a Circle to be Able to encompass the 3 points,
                       // Radius of circle must be greater than or equal to half the length of the Line
                       ch3 = DOUBLECOMPARE((a/2),PARAMETERS.RADIUS1);
                        if (ch3 == GT)
                          {return 1;}
                    }
                  else
                      {
                       //For a Circle to be Able to encompass the 3 points,
                       // Radius of circle must be greater than or equal to half the length of the Line
                       ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1);
                        if (ch3 == GT)
                          {return 1;}
                      }
                }
             else
              {  //Compares the greater of the 2 with the third
                 ch2 = DOUBLECOMPARE(b,r);
                  if(ch2 == GT)
                    {
                      //For a Circle to be Able to encompass the 3 points,
                      // Radius of circle must be greater than or equal to half the length of the Line
                       ch3 = DOUBLECOMPARE((b/2),PARAMETERS.RADIUS1);
                        if (ch3 == GT)
                          {return 1;}
                    }
                  else
                      {
                       //For a Circle to be Able to encompass the 3 points,
                       // Radius of circle must be greater than or equal to half the length of the Line
                       ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1);
                        if (ch3 == GT)
                          {return 1;}
                      }
               }
            }
       else
          { //The Points form a Triangle. All Triangles are Circumscribable
            // For the 3 points to be contained,
            // the Radius of the Cicle should be greater than or equal to the Circumradius if triangle is acute or right.
            // For abtuse, Radius of circle must be greater than halff the length of the longest side
             double ang1,ang2,ang3;
             ang1 = angle_points(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1]);
             ang2 = angle_points(X[i],Y[i],X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1]);
             ang3 = angle_points(X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i],Y[i],X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1]);
             
             //If the triangle is 
             if((DOUBLECOMPARE(ang1,PI/2)<GT)&&(DOUBLECOMPARE(ang2,PI/2)<GT)&&(DOUBLECOMPARE(ang3,PI/2)<GT))
             {r  = circumcenter(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i+PARAMETERS.B_PTS + 1],Y[i+PARAMETERS.B_PTS + 1]);
              }
             else
               { if(DOUBLECOMPARE(ang1,PI/2)==GT)
                     { r = (length_point(X[i],Y[i],X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1]))/2;
                     }
                  else if(DOUBLECOMPARE(ang2,PI/2)==GT)
                     { r = (length_point(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1]))/2;
                     }
                  else
                     { r = (length_point(X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1],Y[i+ PARAMETERS.A_PTS + 1 + PARAMETERS.B_PTS + 1]))/2;

                      }

               }
              ch1 = DOUBLECOMPARE(PARAMETERS.RADIUS1,r);
              if(ch1 == LT)
                  { return 1;}

    }
   }
  }
   return 0;
}

/*
 * There exists at least one set of three data points separated by exactly C PTS and D PTS consecutive intervening
 * points, respectively, that form an angle such that:
 * angle < (PI-EPSILON)
 * or
 * angle > (PI+EPSILON)
 */
boolean LIC9()
{
	//Initialization
	int i;

	//The condition is not met when NUMPOINTS < 5
	if(NUMPOINTS < 5)
		return 0;

	//For each point (X[i], Y[i]), determine the next point as seperated by the number of points
	//designated by C_PTS. Take that point, and determine the next point as seperated by the
	//number of points designated by D_PTS.
	for(i = 0; i < (NUMPOINTS-(PARAMETERS.C_PTS+PARAMETERS.D_PTS + 2)); i++)
	{
		//Note: the "+1" is necessary to seperate out the number of points designated by C_PTS.
		//I.e. if C_PTS is 2, the we need to check X[0] and X[3], since there are two points
		//in between 0 and 3.
		int pt_one = i+PARAMETERS.C_PTS+1;
		int pt_two = pt_one+PARAMETERS.D_PTS+1;

		//Determine if the first or last poiint coincides with the vertex. If not, then compute the angle and compare
		//it to EPSILON. Return true if the angle is outside of PI within the boundary as designated by EPSILON.
		if (((DOUBLECOMPARE(X[i], X[pt_one]) == EQ)&&(DOUBLECOMPARE(Y[i], Y[pt_one]) == EQ))||((DOUBLECOMPARE(X[pt_one], X[pt_two]) == EQ)&&(DOUBLECOMPARE(Y[pt_one], Y[pt_two]) == EQ)))
			continue;
		else
		{
			double Angle = angle_points(X[i],Y[i],X[pt_one],Y[pt_one],X[pt_two],Y[pt_two]);
			if((DOUBLECOMPARE(Angle, PI - PARAMETERS.EPSILON) == LT)||(DOUBLECOMPARE(Angle, PI + PARAMETERS.EPSILON) == GT))
				return 1;
		}
	}

	return 0;
}

/*
 * There exists at least one set of three data points separated by exactly E PTS and F PTS consecutive intervening
 * points, respectively, that are the vertices of a triangle with area greater than AREA1. The condition is not met
 * when NUMPOINTS < 5.
 */
boolean LIC10()
{
	//Initialization
	int i;

	//The condition is not met when NUMPOINTS < 5
	if(NUMPOINTS < 5)
		return 0;

	//For each  point (X[i], Y[i]), determine the next point as seperated by the number of points
	//designated by E_PTS. Take that point, and determine the next point as seperated by the
	//number of points designated by F_PTS. Compute the area of the triangle using these three
	//points, and if it is greater than AREA1, then return true. Do this for all points.
	for(i = 0; i < (NUMPOINTS-(PARAMETERS.E_PTS+PARAMETERS.F_PTS+2)); i++)
	{
		//Note: the "+1" is necessary to seperate out the number of points designated by E_PTS.
		//I.e. if E_PTS is 2, the we need to check X[0] and X[3], since there are two points
		//in between 0 and 3.
		int pt_one = i+PARAMETERS.E_PTS+1;
		int pt_two = pt_one+PARAMETERS.F_PTS+1;
		double triangle_area = Calculate_Area_Triangle(X[i],Y[i],X[pt_one],Y[pt_one],X[pt_two],Y[pt_two]);
		if(DOUBLECOMPARE(triangle_area, PARAMETERS.AREA1) == GT)
			return 1;
	}

	return 0;
}

/* There exists at least one set of two data points, (X[i],Y[i]) and (X[j],Y[j]), separated by exactly G_PTS consecutive
 * intervening points, such that X[j] - X[i] < 0. (where i < j ) The condition is not met when NUMPOINTS < 3.
 * 1 <= G PTS <= NUMPOINTS-2
 */
boolean LIC11()
{
	int i;
	
	if(NUMPOINTS < 3)
	{
		return 0;
	}
	
	for(i=0; i < (NUMPOINTS - (PARAMETERS.G_PTS + 1)); i++)
	{
		if(DOUBLECOMPARE(X[i], X[i+PARAMETERS.G_PTS + 1]) == GT)
		{
			return 1;
		}
	}
	
	return 0; 
}

/* There exists at least one set of two data points, separated by exactly K_PTS consecutive intervening points,
 * which are a distance greater than the length, LENGTH1, apart. In addition, there exists at least one set of two
 * data points (which can be the same or different from the two data points just mentioned), separated by exactly
 * K PTS consecutive intervening points, that are a distance less than the length, LENGTH2, apart. Both parts
 * must be true for the LIC to be true. The condition is not met when NUMPOINTS < 3, 0 <= LENGTH2
 */
boolean LIC12()
{
	boolean cond_1;
	boolean cond_2;
	double dist;
	int i;
	
	if(NUMPOINTS < 3)
	{
		return 0;
	}
	
	for(i = 0; i < (NUMPOINTS - (PARAMETERS.K_PTS + 1)); i++)
	{
		dist = length_point(X[i],Y[i],X[i+PARAMETERS.K_PTS + 1],Y[i+PARAMETERS.K_PTS + 1]);
		if(DOUBLECOMPARE(dist, PARAMETERS.LENGTH1) == GT)
		{
			cond_1 = 1;
		}
		if(DOUBLECOMPARE(dist, PARAMETERS.LENGTH2) == LT)
		{
			cond_2 = 1;
		}
	}
	
	return (cond_1 & cond_2);
}

/* There exists at least one set of three data points, separated by exactly A_PTS and B_PTS consecutive intervening
 * points, respectively, that cannot be contained within or on a circle of radius RADIUS1. In addition, there exists
 * at least one set of three data points (which can be the same or different from the three data points just mentioned)
 * separated by exactly A PTS and B PTS consecutive intervening points, respectively, that can be contained in or
 * on a circle of radius RADIUS2. Both parts must be true for the LIC to be true. The condition is not met when
 * NUMPOINTS < 5, 0 <= RADIUS2
*/
boolean LIC13()
{
	boolean cond_1;
	boolean cond_2;
	int ch,ch1,ch2,ch3,i;
	double a,b,r;
	
	if(NUMPOINTS < 5)
	{
		return 0;
	}
		
	for(i = 0; i < (NUMPOINTS - (PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2)); i++)
	{
		//Finding slope of a line by standard formula (Learned in High School)

		a = ((Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2] - Y[i+PARAMETERS.A_PTS + 1])/(X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2] - X[i+PARAMETERS.A_PTS]));
		b = ((Y[i] - Y[i+PARAMETERS.A_PTS + 1 ])/(X[i] - X[i+PARAMETERS.A_PTS + 1]));
		//Compares Slopes to decide if line or Triangle
		ch=  DOUBLECOMPARE(a,b);
		if(ch == EQ)
		{
			// Decides that it is a Line So compute the greatest separation between the points to find length of the line
			a = length_point(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1]);
			b = length_point(X[i],Y[i],X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2]);
			r = length_point(X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],X[i+PARAMETERS.A_PTS + 2],Y[i+PARAMETERS.A_PTS + 2]);
			//Compares 2 Lengths
			ch1 = DOUBLECOMPARE(a,b);
			if (ch1 == GT)
			{
				ch2 = DOUBLECOMPARE(a,r);
				if(ch2 == GT)
				{
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					ch3 = DOUBLECOMPARE((a/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						cond_1 = 1;
					}
					ch3 = DOUBLECOMPARE((a/2),PARAMETERS.RADIUS2);
					if(ch3 < GT)
					{
						cond_2 = 1;
					}
				}
				else
				{
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						cond_1 = 1;
					}
					ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS2);
					if(ch3 < GT)
					{
						cond_2 = 1;
					}
				}
			}
			else
			{
				//Compares the greater of the 2 with the third
				ch2 = DOUBLECOMPARE(b,r);
				if(ch2 == GT)
				{
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					ch3 = DOUBLECOMPARE((b/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						cond_1 = 1;
					}
					ch3 = DOUBLECOMPARE((b/2),PARAMETERS.RADIUS2);
					if (ch3 < GT)
					{
						cond_2 = 1;
					}
				}
				else
				{
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						cond_1 = 1;
					}
					ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS2);
					if (ch3 < GT)
					{
						cond_2 = 1;
					}
				}
			}
		}
		else
		{
			//The Points form a Triangle. All Triangles are Circumscribable
			// For the 3 points to be contained,
			// the Radius of the Circle should be greater than or equal to the Circumradius if triangle is acute or right.
			// For obtuse, Radius of circle must be greater than halff the length of the longest side
			double ang1,ang2,ang3;
			ang1 = angle_points(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2]);
			ang2 = angle_points(X[i],Y[i],X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1]);
			ang3 = angle_points(X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i],Y[i],X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2]);
			if((DOUBLECOMPARE(ang1,PI/2)<GT)&&(DOUBLECOMPARE(ang2,PI/2)<GT)&&(DOUBLECOMPARE(ang3,PI/2)<GT))
			{
				r  = circumcenter(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2]);
			}
			else
			{
				if(DOUBLECOMPARE(ang1,PI/2)==GT)
				{
					r = (length_point(X[i],Y[i],X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2 ],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2]))/2;
				}
				else if(DOUBLECOMPARE(ang2,PI/2)==GT)
				{
					r = (length_point(X[i],Y[i],X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1]))/2;
				}
				else
				{
					r = (length_point(X[i+PARAMETERS.A_PTS + 1],Y[i+PARAMETERS.A_PTS + 1],X[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2],Y[i+PARAMETERS.A_PTS+PARAMETERS.B_PTS + 2]))/2;
				}

			}
			ch1 = DOUBLECOMPARE(PARAMETERS.RADIUS1,r);
			if(ch1 == LT)
			{
				cond_1 = 1;
			}
			ch1 = DOUBLECOMPARE(PARAMETERS.RADIUS2,r);
			if(ch1 > LT)
			{
				cond_2 = 1;
			}

		}
	}
		
	return (cond_1 & cond_2);
}

/* There exists at least one set of three data points, separated by exactly E_PTS and F_PTS consecutive intervening
 * points, respectively, that are the vertices of a triangle with area greater than AREA1. In addition, there exist three
 * data points (which can be the same or different from the three data points just mentioned) separated by exactly
 * E PTS and F PTS consecutive intervening points, respectively, that are the vertices of a triangle with area less
 * than AREA2. Both parts must be true for the LIC to be true. The condition is not met when NUMPOINTS < 5.
 * 0 <= AREA2
 */
boolean LIC14()
{
	boolean cond_1;
	boolean cond_2;
	double area;
	if(NUMPOINTS < 5)
	{
		return 0;
	}
	
	int i;
	for(i = 0; i < (NUMPOINTS - (PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2)); i++)
	{
		area = Calculate_Area_Triangle(X[i], Y[i], X[i+PARAMETERS.E_PTS + 1], Y[i+PARAMETERS.E_PTS + 1], X[i+PARAMETERS.E_PTS+PARAMETERS.F_PTS + 2], Y[i+PARAMETERS.E_PTS+PARAMETERS.F_PTS + 2]);
		if(DOUBLECOMPARE(area, PARAMETERS.AREA1) == GT)
		{
			cond_1 = 1;
		}
		if(DOUBLECOMPARE(area, PARAMETERS.AREA2) == LT)
		{
			cond_2 = 1;
		}
	}
	
	return (cond_1 & cond_2);
}


// -- Helper Functions -- //

/*
* This function calculates the area of a triangle
* given three points in the same plane.
* This function was implemented using basic mathematical formula (by ourselves).
*/
double Calculate_Area_Triangle(double ax, double ay, double bx, double by, double cx, double cy)
{
	double A = length_point(ax,ay,bx,by);
	double B = length_point(bx,by,cx,cy);
	double C = length_point(ax,ay,cx,cy);


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
{ int column;
	boolean all_elements_are_true = 1;
	// Loop through each element in the row
	for( column = 0; column < 15; column++ )
	{
		if (two_by_two_matrix[row][column] == 0) { all_elements_are_true = 0; }
	}
	return all_elements_are_true;
} // end all_elements_in_row_are_true()


/*
* This function takes the points in space and returns the distance of seperation of the points
* formula is that of standard coordinate distance between poinrs.
*/
double length_point(double x1, double y1, double x2, double y2)
{ 
	return sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
}

/*
* This function takes the vertices of a triangle and returns thier circum radius
* formula is that of standard Circum radius of a triangle (Learnt in High School).
*/
double circumcenter(double x1,double y1,double x2,double y2,double x3,double y3)
{ double CRadius,Area,a,b,c;
	a = length_point(x1,y1,x2,y2);
	b = length_point(x1,y1,x3,y3);
	c = length_point(x3,y3,x2,y2);
	Area = Calculate_Area_Triangle(x1,y1,x2,y2,x3,y3);
	CRadius = (a*b*c)/(4*Area);
	return CRadius;
}

double angle_points(double x1, double y1, double x2,double y2,double x3,double y3)
{ double cos_Angle,Angle,a,b,c;
	a = length_point(x1,y1,x2,y2);
	b = length_point(x3,y3,x2,y2);
	c = length_point(x1,y1,x3,y3);

	/* By law of cosines c^2 = a^2 + b^2 - 2abcos(angle theta)  */

	cos_Angle = (((a*a)+(b*b)-(c*c))/(2*a*b));
	Angle = acos(cos_Angle);
	return Angle;
}

int Quadrant_point(double x,double y)
{ if((x>=0)&&(y>=0))
	{return 1;}
	else if((x<0)&&(y>=0))
	{return 2;}
	else if((x<=0)&&(y<0))
	{return 3;}
	return 4;
}
