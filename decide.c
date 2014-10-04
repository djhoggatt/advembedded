/*
* Team 11  CS 5785
* Team Assignment #1: decide.c
* SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
*/

#include "decide.h"
#include <stdio.h>

// -- Forward Declarations -- //
boolean LIC0();
boolean LIC1();
boolean LIC2();
boolean LIC3();
boolean LIC4();
boolean LIC5();


boolean all_elements_in_row_are_true(BMATRIX, int);
double Calculate_Area_Triangle(double, double, double, double ,double ,double);
double length_point(double ,double ,double ,double );
double circumcenter(double ,double ,double ,double ,double ,double );
double angle_points(double, double, double, double ,double ,double);
int Quadrant_point(double,double);

// -- Globals -- //
boolean LAUNCH = 0; // Default to no launch.

/*
*See requirements specification document for decide() function contract.
*/
void DECIDE(void)
{
	int i = 0;
	int j = 0;

	// -- CMV -- //
	CMV[0] = LIC0();
	CMV[1] = LIC1();
	CMV[2] = LIC2();
	CMV[3] = LIC3();
	CMV[4] = LIC4();
	CMV[5] = LIC5();

	/*
	* Use the logical operator stored in LCM and apply to the booleans
	* stored in the CMV. Store the result in PUM. If "NOTUSED" is found
	* in LCM then PUM defaults to 0 (FALSE).
	*/
	for(i = 0; i < 15; i++ )
	{
		for(j = 0; j < 15; j++ )
		{
			if (LCM[i][j] == ORR) { PUM[i][j] = (CMV[i] || CMV[j]); }
			else if (LCM[i][j] == ANDD) { PUM[i][j] = (CMV[i] && CMV[j]); }
			else PUM[i][j] = 0;
		}
	}

	/*
	* FUV[i] should be set to true if PUM[i,i] is false
	* or if all elements in PUM row i are true. (See page 6
	* of the protocol.)
	*/
	for( i = 0; i < 15; i++ )
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
	for(i = 0; i < 15; i++ )
	{
		if (FUV[i] == 0) { fuv_has_false = 1; }
	}
	if (fuv_has_false == 0) { LAUNCH = 1; }
	else { LAUNCH = 0; }



}


/*
* CMV[0]: There exists at least one set of two consecutive data points
* that are a distance greater than the length, LENGTH1, apart.
*/
boolean LIC0()
{ int ch,i;
	double a;
	for( i = 0; i<NUMPOINTS-1; i++)
	{  //Finds distance between points and compares them
		a = length_point(X[i],Y[i],X[i+1],Y[i+1]);
		ch=  DOUBLECOMPARE(PARAMETERS.LENGTH1,a);
		if(ch == LT)
		return 1;
	}
	return 0;
}

/*
* LIC[1]: There exists at least one set of three consecutive data points that cannot all
* be contained within or on a circle of radius RADIUS1
* 3 points in space can form 2 basic shapes: Line or Triangle;
* If Slope of the line formed by any 2 points equals that of any other combination, then the points lie on a single Line
* If the Slope of a line formed by any two points are different, they form a Triangle
*/

boolean LIC1()
{ int ch,ch1,ch2,ch3,i;
	double a,b,r;

	for( i = 0; i<NUMPOINTS-2; i++)
	{
		//Finding slope of a line by standard formulae(Learned in High School)

		a = ((Y[i+2] - Y[i+1])/(X[i+2] - X[i+1]));
		b = ((Y[i] - Y[i+1])/(X[i] - X[i+1]));
		//Compares Slopes to decide if line or Triangle
		ch=  DOUBLECOMPARE(a,b);
		if(ch == EQ)
		{
			//makes a line
			//got here
			printf("makes a line\n");
			// Decidesthat it is a Line So compute the greatest separation between the points to find length of the line
			a = length_point(X[i],Y[i],X[i+1],Y[i+1]);
			b = length_point(X[i],Y[i],X[i+2],Y[i+2]);
			r = length_point(X[i+2],Y[i+2],X[i+1],Y[i+1]);
			//Compares 2 Lengths
			ch1 = DOUBLECOMPARE(a,b);
			if (ch1 == GT)
			{ 
				//Compares the greater of the 2 with the third
				//got here
				printf("a is greater than b\n");
				ch2 = DOUBLECOMPARE(a,r);
				if(ch2 == GT)
				{
					//got here
					printf("a is greater than r\n");
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					ch3 = DOUBLECOMPARE((a/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						//got here
						printf("a/2 is greater than RADIUS1\n");
						return 1;
					}
				}
				else
				{
					//got here
					printf("r is greater than or equal to a\n");
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						//got here
						printf("r/2 is greater than RADIUS1\n");
						return 1;
					}
				}
			}
			else
			{
				//got here b is greater than a
				printf("b is greater than or equal to a\n");
				//Compares the greater of the 2 with the third
				ch2 = DOUBLECOMPARE(b,r);
				if(ch2 == GT)
				{
					//got here
					printf("b is greater than r\n");
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					ch3 = DOUBLECOMPARE((b/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						//got here
						printf("b/2 is greater than RADIUS1\n");
						return 1;
					}
				}
				else
				{
					//got here
					//r is greater than b
					//For a Circle to be Able to encompass the 3 points,
					// Radius of circle must be greater than or equal to half the length of the Line
					printf("r is greater than or equal to b\n");
					ch3 = DOUBLECOMPARE((r/2),PARAMETERS.RADIUS1);
					if (ch3 == GT)
					{
						//got here
						printf("r/2 is greater than RADIUS1\n");
						return 1;
					}
				}
			}
		}
		else
		{ 
			printf("forms a triangle\n");
			//The Points form a Triangle. All Triangles are Circumscribable
			// For the 3 points to be contained,
			// the Radius of the Circle should be greater than or equal to the Circumradius if triangle is acute or right.
			// For obtuse, Radius of circle must be greater than halff the length of the longest side
			double ang1,ang2,ang3;
			ang1 = angle_points(X[i],Y[i],X[i+1],Y[i+1],X[i+2],Y[i+2]);
			printf("angle1 = %f\n", ang1);
			ang2 = angle_points(X[i],Y[i],X[i+2],Y[i+2],X[i+1],Y[i+1]);
			printf("angle2 = %f\n", ang2);
			ang3 = angle_points(X[i+1],Y[i+1],X[i],Y[i],X[i+2],Y[i+2]);
			printf("angle3 = %f\n", ang3);
			if((DOUBLECOMPARE(ang1,PI/2)<GT)&&(DOUBLECOMPARE(ang2,PI/2)<GT)&&(DOUBLECOMPARE(ang3,PI/2)<GT))
			{
				//got here
				printf("all angles are less than or equal to 90 degrees\n");
				r  = circumcenter(X[i],Y[i],X[i+1],Y[i+1],X[i+2],Y[i+2]);
			}
			else
			{ 
				if(DOUBLECOMPARE(ang1,PI/2)==GT)
				{
					printf("ang1 is obtuse\n"); 
					r = (length_point(X[i],Y[i],X[i+2],Y[i+2]))/2;
				}
				else if(DOUBLECOMPARE(ang2,PI/2)==GT)
				{
					//got here
					printf("ang2 is obtuse\n"); 
					r = (length_point(X[i],Y[i],X[i+1],Y[i+1]))/2;
				}
				else
				{
					printf("ang3 is obtuse\n"); 
					r = (length_point(X[i+1],Y[i+1],X[i+2],Y[i+2]))/2;
				}

			}
			ch1 = DOUBLECOMPARE(PARAMETERS.RADIUS1,r);
			if(ch1 == LT)
			{
				printf("RADIUS1 is less than r\n"); 
				return 1;
			}

		}
	}
	printf("all sets of three consecutive data points can be contained within or on a circle of radius RADIUS1\n");
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


// -- Helper Functions -- //

/*
* This function calculates the area of a triangle
* given three points in the same plane.
* This function was implemented using basic mathematical formulae (by ourselves).
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
double length_point(double x1,double y1,double x2,double y2)
{ double a = 0;
	a = sqrt((double)((x2 - x1)*(x2 - x1) +(y2 - y1)*(y2 - y1)));
	return a;
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
