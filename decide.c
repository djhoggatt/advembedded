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

//Helper function declaration
boolean all_elements_in_row_are_true(BMATRIX, int);
boolean contained_in_circle(int, int, int, double);
double Calculate_Area_Triangle(double, double, double, double, double, double);
double length_point(double, double, double, double);
double circumcenter(double, double, double, double, double, double);
double angle_points(double, double, double, double, double, double);
int Quadrant_point(double, double);

// -- Globals -- //
boolean LAUNCH = 0; // Default to no launch.

// -- Decide Implementation -- //
//See the requirements specification for details regarding the decide function
// requirements.
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
	* Use the logical operators stored in the LCM and apply them to the booleans
	* stored in the CMV. Store the results in PUM. If the logical operator is
	* "NOTUSED" then PUM defaults to 1 (TRUE).
	*/
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (LCM[i][j] == ORR)
				PUM[i][j] = (CMV[i] || CMV[j]);
			else if (LCM[i][j] == ANDD)
				PUM[i][j] = (CMV[i] && CMV[j]);
			else if (LCM[i][j] == NOTUSED)
				PUM[i][j] = 1;
			else
				PUM[i][j] = 0;
		}
	}

	/*
	* Loop through the FUV. FUV[i] should be set to true if PUM[i,i] is false or
	* if all elements in PUM row i are true.
	*/
	for (i = 0; i < 15; i++)
	{
		if ((PUM[i][i] == 0) || (all_elements_in_row_are_true(PUM, i)))
		{
			FUV[i] = 1;
		}
			
		else
		{
			FUV[i] = 0;
		}
			
	}

	/*
	* Check all of the elements in the FUV for any false entries. If there are 
	* any false entries, then we should not launch.
	*/
	LAUNCH = 1;
	for (i = 0; i < 15; i++)
	{
		if (FUV[i] == 0) 
		{
			LAUNCH = 0;
		}			
	}
}

// -- LIC Implementation -- //
/*
* Launch Intercept Condition 0
* There exists at least one set of two consecutive data points that are a 
* distance
* greater than the length, LENGTH1, apart.
*/
boolean LIC0()
{
	//Initialization
	int i;

	//Find the distance between all consecutive points, and compare them.
	for (i = 0; i < NUMPOINTS - 1; i++)
	{
		//If the distance between the points is greater than LENGTH1, return 
		// true.
		if (DOUBLECOMPARE(PARAMETERS.LENGTH1, length_point(X[i], Y[i], X[i + 1], 
			Y[i + 1])) == LT)
			return 1;
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 1
* There exists at least one set of three consecutive data points that cannot all 
* be contained within or on a circle of radius RADIUS1.
*/
boolean LIC1()
{
	//Initialization
	int i;
	double a, b, r, ang1, ang2, ang3;

	/*
	* Three points in space can form either one of two basic shapes: a line or a 
	* triangle. If the slope of the line formed by any two points equals that of 
	* any other combination, then the points lie on a single line. If the slope 
	* of a line formed by any two points are different, then they form a triangle
	*/
	for (i = 0; i < NUMPOINTS - 2; i++)
	{
		if ((X[i + 2] != X[i + 1]) && (X[i + 1] != X[i]))
		{	//Determine the slopes
			a = ((Y[i + 2] - Y[i + 1]) / (X[i + 2] - X[i + 1]));
			b = ((Y[i] - Y[i + 1]) / (X[i] - X[i + 1]));
		}
		else if ((X[i + 2] == X[i + 1]) && (X[i + 1] == X[i]))
		{
			a = 1;
			b = 1;
		}
		else
		{
			a = 1;
			b = 5;
		}
		//Decide if the points form a line or a triangle
		if (DOUBLECOMPARE(a, b) == EQ)
		{
			// If the points form a line, then compute the greatest separation
			// between the points to find total length of the line.
			a = length_point(X[i], Y[i], X[i + 1], Y[i + 1]);
			b = length_point(X[i], Y[i], X[i + 2], Y[i + 2]);
			r = length_point(X[i + 2], Y[i + 2], X[i + 1], Y[i + 1]);

			// Find the longest distance formed by the three points, which should
			// correspond to the total length of the line.
			if (DOUBLECOMPARE(a, b) == GT)
			{
				if (DOUBLECOMPARE(a, r) == GT)
				{
					// If the The radius of the circle specified by RADIUS1 is 
					// greater than half the length of the
					// line, then return true.
					if (DOUBLECOMPARE((a / 2), PARAMETERS.RADIUS1) == GT)
						return 1;
				}
				else
				{
					//If the The radius of the circle specified by RADIUS1 is 
					// greater than half the length of the line, then return 
					// true.
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS1) == GT)
						return 1;
				}
			}
			else
			{
				if (DOUBLECOMPARE(b, r) == GT)
				{
					// If the The radius of the circle specified by RADIUS1 is 
					// greater than half the length of the line, then return
					// true.
					if (DOUBLECOMPARE((b / 2), PARAMETERS.RADIUS1) == GT)
					{
						return 1;
					}
				}
				else
				{
					// If the The radius of the circle specified by RADIUS1 is 
					// greater than half the length of the
					// line, then return true.
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS1) == GT)
					{
						return 1;
					}
				}
			}
		}
		else
		{
			//Determine the three angles of the triangle
			ang1 = angle_points(X[i], Y[i], X[i + 1], Y[i + 1], 
				X[i + 2], Y[i + 2]);
			ang2 = angle_points(X[i], Y[i], X[i + 2], Y[i + 2], 
				X[i + 1], Y[i + 1]);
			ang3 = angle_points(X[i + 1], Y[i + 1], X[i], Y[i], 
				X[i + 2], Y[i + 2]);

			// If the triangle is an acute or right triangle, then RADIUS 1
			// should be greater than or equal to the circumradius of the 
			// triangle. For obtuse triangles, the radius of circle must be 
			// greater than half the length of the longest side.
			if ((DOUBLECOMPARE(ang1, PI / 2) < GT) && 
				(DOUBLECOMPARE(ang2, PI / 2) < GT) && 
				(DOUBLECOMPARE(ang3, PI / 2) < GT))
				r = circumcenter(X[i], Y[i], X[i + 1], Y[i + 1],
				X[i + 2], Y[i + 2]);
			else
			{
				if (DOUBLECOMPARE(ang1, PI / 2) == GT)
					r = (length_point(X[i], Y[i], X[i + 2], Y[i + 2])) / 2;
				else if (DOUBLECOMPARE(ang2, PI / 2) == GT)
					r = (length_point(X[i], Y[i], X[i + 1], Y[i + 1])) / 2;
				else
					r = (length_point(X[i + 1], Y[i + 1], X[i + 2], Y[i + 2])) 
					/ 2;
			}

			//Return true if the computes value is less than RADIUS1.
			if (DOUBLECOMPARE(PARAMETERS.RADIUS1, r) == LT)
				return 1;
		}
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 2
* There exists at least one set of three consecutive data points which form an 
* angle such that: * angle < (PI - EPSILON) or angle > (PI + EPSILON) The second
* of the three consecutive points is always the vertex of the angle. If either
* the first point or the last point (or both) coincides with the vertex, 
* the angle is undefined and the LIC is not satisfied by those three points.
*/
boolean LIC2()
{
	//Initialization
	int i;

	//Loop through all of the points.
	for (i = 0; i < (NUMPOINTS - 2); i++)
	{
		// Determine if the first or last poiint coincides with the vertex. If
		// not, then compute the angle and compare it to EPSILON. Return true if
		// the angle is outside of PI within the boundary as designated by
		// EPSILON.
		if (((DOUBLECOMPARE(X[i], X[i + 1]) == EQ) && 
			(DOUBLECOMPARE(Y[i], Y[i + 1]) == EQ)) || 
			((DOUBLECOMPARE(X[i + 2], X[i + 1]) == EQ) && 
			(DOUBLECOMPARE(Y[i + 2], Y[i + 1]) == EQ)))
			continue;
		else
		{
			double Angle = angle_points(X[i], Y[i], X[i + 1], Y[i + 1], 
				X[i + 2], Y[i + 2]);
			if ((DOUBLECOMPARE(Angle, PI - PARAMETERS.EPSILON) == LT) ||
				(DOUBLECOMPARE(Angle, PI + PARAMETERS.EPSILON) == GT))
				return 1;
		}
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}


/*
* Launch Intercept Condition 3
* There exists at least one set of three consecutive data points that are the 
* vertices of a triangle with area greater than AREA1.
*/
boolean LIC3()
{
	//Initialization
	int i;

	//Loop through all of the points.
	for (i = 0; i < (NUMPOINTS - 2); i++)
	{
		double triangle_area = Calculate_Area_Triangle(X[i], Y[i], 
			X[i + 1], Y[i + 1], X[i + 2], Y[i + 2]);
		if (DOUBLECOMPARE(triangle_area, PARAMETERS.AREA1) == GT)
			return 1;
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 4
* There exists at least one set of Q PTS consecutive data points that lie in more
* than QUADS quadrants. Where there is ambiguity as to which quadrant contains a
* given point, priority of decision will be by quadrant number, i.e., I, II, III,
* IV. For example, the data point (0,0) is in quadrant I, the point (-l,0) is in
* quadrant II, the point (0,-l) is in quadrant III, the point (0,1) is in 
* quadrant I and the point (1,0) is in quadrant I.
*/
boolean LIC4() // commented out for now until bug is found
{
	//Initialization
	int i, j, k, count, flag;
	int quad[PARAMETERS.Q_PTS];

	//Loop through all of the points.
	for (i = 0; i < (NUMPOINTS + 1 - PARAMETERS.Q_PTS); i++)
	{
		//For all consecutive Q_PTS, determine which quadrant they are in.
		for (j = 0; j < PARAMETERS.Q_PTS; j++)
			quad[j] = Quadrant_point(X[i + j], Y[i + j]);

		// Determine how many qudrants are different, and increment the count if
		// they are.
		count = 0;
		for (j = 0; j < PARAMETERS.Q_PTS; j++)
		{
			flag = 0;
			for (k = (j + 1); k < PARAMETERS.Q_PTS; k++)
			{
				if (quad[j] == quad[k])
					flag = 1;
			}
			if (flag == 0)
				count++;
		}

		// If the total number of points that lie in different qudrants is 
		// greater than QUADS, then return true.
		if (count > PARAMETERS.QUADS)
			return 1;
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 5
* There exists at least one set of two consecutive data points, (X[i],Y[i]) and 
* (X[j],Y[j]), such that X[j] - X[i] < 0.
*/
boolean LIC5()
{
	//Initialization
	int i;

	//Loop through all of the points.
	for (i = 0; i < (NUMPOINTS - 1); i++)
	{
		// If the difference between the next point and the current point is less
		// than zero, return true.
		if (DOUBLECOMPARE(X[i], X[i + 1]) == GT)
			return 1;

	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 6
* There exists at least one set of N PTS consecutive data points such that at
* least one of the points lies a distance greater than DIST from the line 
* joining the first and last of these N PTS points. If the first and last points
* of these N PTS are identical, then the calculated distance to compare with DIST
* will be the distance from the coincident point to all other points of the N PTS
* consecutive points. The condition is not met when NUMPOINTS < 3.
*/
boolean LIC6()
{
	//Initialization
	int i, A, B, C, j, d;

	if (NUMPOINTS < 3) { return 0; }
	else
	{
		//Loop through all of the points.
		for (i = 0; i < (NUMPOINTS + 1 - PARAMETERS.N_PTS); i++)
		{
			if ((DOUBLECOMPARE(X[i], X[i + PARAMETERS.N_PTS - 1]) == EQ) && 
				(DOUBLECOMPARE(Y[i], Y[i + PARAMETERS.N_PTS - 1]) == EQ))
			{
				for (j = i + 1; j < i + PARAMETERS.N_PTS - 1; j++)
				{
					d = length_point(X[i], Y[i], X[j], Y[j]);
					if (DOUBLECOMPARE(PARAMETERS.DIST, d) == LT)
						return 1;
				}
			}
			else
			{
				A = ((Y[i + PARAMETERS.N_PTS - 1]) - (Y[i]));
				B = ((X[i]) - (X[i + PARAMETERS.N_PTS - 1]));
				C = (((-(X[i]))*A) + ((-(Y[i]))*B));
				for (j = i + 1; j < i + PARAMETERS.N_PTS - 1; j++)
				{
					d = (fabs((A*X[j]) + (B*Y[j]) + C)) / (sqrt((A*A) + (B*B)));
					if (DOUBLECOMPARE(PARAMETERS.DIST, d) == LT)
						return 1;
				}
			}
		}
	}
	//If no points are found that satisfy the condition, return false.
	return 0;
}


/*
* Launch Intercept Condition 7
* There exists at least one set of two data points separated by exactly K PTS 
* consecutive intervening points that are a distance greater than the length, 
* LENGTH1, apart. The condition is not met when NUMPOINTS < 3.
*/
boolean LIC7()
{
	//Initialization
	int i;
	double a;

	//The condition is not met when NUMPOINTS < 3
	if (NUMPOINTS < 3)
		return 0;

	//For each point (X[i], Y[i]), determine the next point as seperated by the
	// number of points designated by K_PTS.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.K_PTS + 1)); i++)
	{
		// Note: the "+1" is necessary to seperate out the number of points 
		// designated by K_PTS. I.e. if K_PTS is 2, the we need to check X[0]
		// and X[3], since there are two points
		//in between 0 and 3.
		int pt_one = i + PARAMETERS.K_PTS + 1;

		//Find the distance between the points and compare them
		a = length_point(X[i], Y[i], X[pt_one], Y[pt_one]);

		//Return 1 if the distance is greater than LENGTH1
		if (DOUBLECOMPARE(PARAMETERS.LENGTH1, a) == LT)
			return 1;
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}


/*
* Launch Intercept Condition 8
* There exists at least one set of three data points separated by exactly A_PTS
* and B_PTS consecutive intervening points, respectively, that cannot be 
* contained within or on a circle of radius RADIUS1. The condition is not met
* when NUMPOINTS < 5.
*/
boolean LIC8()
{
	//Initialization
	int i;
	double a, b, r, ang1, ang2, ang3; // a and b are slopes

	// The condition is not met when NUMPOINTS < 5, also checking for valid
	// inputs per spec (page three #8)
	if ((NUMPOINTS < 5) ||
		(PARAMETERS.A_PTS < 1) ||
		(PARAMETERS.B_PTS < 1) ||
		((PARAMETERS.A_PTS + PARAMETERS.B_PTS) > (NUMPOINTS - 3)))
	{
		return 0;
	}
	// For each point (X[i], Y[i]), determine the next point as seperated by the 
	// number of points designated by A_PTS. Take that point, and determine the
	// next point as seperated by the number of points designated by B_PTS.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2)); i++)
	{
		//Note: the "+1" is necessary to seperate out the number of points 
		// designated by A_PTS. I.e. if A_PTS is 2, the we need to check X[0] and
		// X[3], since there are two points in between 0 and 3.
		int pt_one = i + PARAMETERS.A_PTS + 1;
		int pt_two = pt_one + PARAMETERS.B_PTS + 1;

		//Find the slope of the line
		if ((X[pt_two] != X[pt_one]) && (X[pt_one] != X[i]))
		{	//Determine the slopes
			a = ((Y[pt_two] - Y[pt_one]) / (X[pt_two] - X[pt_one]));
			b = ((Y[i] - Y[pt_one]) / (X[i] - X[pt_one]));
		}
		else if ((X[pt_two] == X[pt_one]) && (X[pt_one] == X[i]))
		{
			a = 1;
			b = 1;
		}
		else
		{
			a = 1;
			b = 5;
		}
		//Compare the slopes to decide if the points form a line or triangle
		if (DOUBLECOMPARE(a, b) == EQ)
		{
			//The points form a line, so compute the greatest separation between 
			// the points to find the length of the line.
			a = length_point(X[i], Y[i], X[pt_one], Y[pt_one]);
			b = length_point(X[i], Y[i], X[pt_two], Y[pt_two]);
			r = length_point(X[pt_two], Y[pt_two], X[pt_one], Y[pt_one]);

			// Find the longest distance formed by the three points, which should
			// correspond to the total length of the line.
			if (DOUBLECOMPARE(a, b) == GT)
			{
				if (DOUBLECOMPARE(a, r) == GT)
				{
					// The radius of the circle must be greater than or equal to
					// half the length of the line
					if (DOUBLECOMPARE((a / 2), PARAMETERS.RADIUS1))
						return 1;
				}
				else
				{
					//The radius of the circle must be greater than or equal to
					// half the length of the line
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS1))
						return 1;
				}
			}
			else
			{
				if (DOUBLECOMPARE(b, r) == GT)
				{
					//The radius of the circle must be greater than or equal to 
					/// half the length of the line
					if (DOUBLECOMPARE((b / 2), PARAMETERS.RADIUS1))
						return 1;
				}
				else
				{
					//The radius of the circle must be greater than or equal to 
					// half the length of the line
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS1))
						return 1;
				}
			}
		}
		else
		{
			//The points form a triangle, and all triangles are circumscribable. 
			// Thus, the radius of the circle should be greater than or equal to
			// the circumradius if the triangle is an acute or right triangle. 
			// For obtuse triangles, the radius of circle must be greater than 
			// half the length of the longest side.
			ang1 = angle_points(X[i], Y[i], X[pt_one], Y[pt_one], 
				X[pt_two], Y[pt_two]);
			ang2 = angle_points(X[i], Y[i], X[pt_two], Y[pt_two], 
				X[pt_one], Y[pt_one]);
			ang3 = angle_points(X[pt_one], Y[pt_one], X[i], Y[i], 
				X[pt_two], Y[pt_two]);

			// If the triangle is an acute or right triangle, then RADIUS 1 
			// should be greater than or equal to the  circumradius of the 
			// triangle. For obtuse triangles, the radius of circle must be 
			// greater than half the length of the longest side.
			if ((DOUBLECOMPARE(ang1, PI / 2) < GT) && 
				(DOUBLECOMPARE(ang2, PI / 2) < GT) && 
				(DOUBLECOMPARE(ang3, PI / 2) < GT))
				r = circumcenter(X[i], Y[i], X[pt_one], Y[pt_one], 
				X[pt_two], Y[pt_two]);
			else
			{
				if (DOUBLECOMPARE(ang1, PI / 2) == GT)
					r = (length_point(X[i], Y[i], X[pt_two], Y[pt_two])) / 2;
				else if (DOUBLECOMPARE(ang2, PI / 2) == GT)
					r = (length_point(X[i], Y[i], X[pt_one], Y[pt_one])) / 2;
				else
					r = (length_point(X[pt_one], Y[pt_one], 
					X[pt_two], Y[pt_two])) / 2;
			}

			//Compare the value with RADIUS1, and return 1 if necessary.
			if (DOUBLECOMPARE(PARAMETERS.RADIUS1, r) == LT)
				return 1;
		}
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 9
* There exists at least one set of three data points separated by exactly C PTS 
* and D PTS consecutive intervening points, respectively, that form an angle such
* that:
* angle < (PI-EPSILON)
* or
* angle > (PI+EPSILON)
*/
boolean LIC9()
{
	//Initialization
	int i;

	//The condition is not met when NUMPOINTS < 5
	if (NUMPOINTS < 5)
		return 0;

	//For each point (X[i], Y[i]), determine the next point as seperated by the 
	// number of points designated by C_PTS. Take that point, and determine the 
	// next point as seperated by the number of points designated by D_PTS.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.C_PTS + PARAMETERS.D_PTS + 2)); i++)
	{
		//Note: the "+1" is necessary to seperate out the number of points 
		// designated by C_PTS. I.e. if C_PTS is 2, the we need to check X[0] and
		// X[3], since there are two points in between 0 and 3.
		int pt_one = i + PARAMETERS.C_PTS + 1;
		int pt_two = pt_one + PARAMETERS.D_PTS + 1;

		//Determine if the first or last poiint coincides with the vertex. If 
		// not, then compute the angle and compare it to EPSILON. Return true if 
		// the angle is outside of PI within the boundary as designated by 
		// EPSILON.
		if (((DOUBLECOMPARE(X[i], X[pt_one]) == EQ) && 
			(DOUBLECOMPARE(Y[i], Y[pt_one]) == EQ)) || 
			((DOUBLECOMPARE(X[pt_one], X[pt_two]) == EQ) && 
			(DOUBLECOMPARE(Y[pt_one], Y[pt_two]) == EQ)))
			continue;
		else
		{
			double Angle = angle_points(X[i], Y[i], X[pt_one], 
				Y[pt_one], X[pt_two], Y[pt_two]);
			if ((DOUBLECOMPARE(Angle, PI - PARAMETERS.EPSILON) == LT) ||
				(DOUBLECOMPARE(Angle, PI + PARAMETERS.EPSILON) == GT))
				return 1;
		}
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 10
* There exists at least one set of three data points separated by exactly E PTS
* and F PTS consecutive intervening points, respectively, that are the vertices
* of a triangle with area greater than AREA1. The condition is not met when 
* NUMPOINTS < 5.
*/
boolean LIC10()
{
	//Initialization
	int i;

	//The condition is not met when NUMPOINTS < 5
	if (NUMPOINTS < 5)
		return 0;

	//For each  point (X[i], Y[i]), determine the next point as seperated by the 
	// number of points designated by E_PTS. Take that point, and determine the 
	// next point as seperated by the number of points designated by F_PTS. 
	// Compute the area of the triangle using these three points, and if it is
	// greater than AREA1, then return true. Do this for all points.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2)); i++)
	{
		//Note: the "+1" is necessary to seperate out the number of points 
		// designated by E_PTS. I.e. if E_PTS is 2, the we need to check X[0] and
		// X[3], since there are two points in between 0 and 3.
		int pt_one = i + PARAMETERS.E_PTS + 1;
		int pt_two = pt_one + PARAMETERS.F_PTS + 1;
		double triangle_area = Calculate_Area_Triangle(X[i], Y[i], 
			X[pt_one], Y[pt_one], X[pt_two], Y[pt_two]);
		if (DOUBLECOMPARE(triangle_area, PARAMETERS.AREA1) == GT)
			return 1;
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 11
* There exists at least one set of two data points, (X[i],Y[i]) and (X[j],Y[j]),
* separated by exactly G_PTS consecutive intervening points, such that X[j] - X
* [i] < 0 (where i < j ). The condition is not met when NUMPOINTS < 3.
*/
boolean LIC11()
{
	//Initialization
	int i;

	//The condition is not met when NUMPOINTS < 3
	if (NUMPOINTS < 3)
		return 0;

	//For each point (X[i], Y[i]), determine the next point as seperated by the 
	// number of points designated by G_PTS.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.G_PTS + 1)); i++)
	{
		//If the difference between the two points is less than zero, return rue.
		if (DOUBLECOMPARE(X[i], X[i + PARAMETERS.G_PTS + 1]) == GT)
			return 1;
	}

	//If no points are found that satisfy the condition, return false.
	return 0;
}

/*
* Launch Intercept Condition 12
* There exists at least one set of two data points, separated by exactly K_PTS
* consecutive intervening points, which are a distance greater than the length, 
* LENGTH1, apart. In addition, there exists at least one set of two data points 
* (which can be the same or different from the two data points just mentioned), 
* separated by exactly K PTS consecutive intervening points, that are a distance 
* less than the length, LENGTH2, apart. Both parts must be true for the LIC to be
* true. The condition is not met when NUMPOINTS < 3.
*/
boolean LIC12()
{
	//Initialization
	boolean cond_1 = 0;
	boolean cond_2 = 0;
	double dist;
	int i;

	//The condition is not met when NUMPOINTS < 3
	if (NUMPOINTS < 3)
		return 0;

	//For each point (X[i], Y[i]), determine the next point as seperated by the 
	// number of points designated by K_PTS.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.K_PTS + 1)); i++)
	{
		dist = length_point(X[i], Y[i], 
			X[i + PARAMETERS.K_PTS + 1], Y[i + PARAMETERS.K_PTS + 1]);
		if (DOUBLECOMPARE(dist, PARAMETERS.LENGTH1) == GT)
			cond_1 = 1;
		if (DOUBLECOMPARE(dist, PARAMETERS.LENGTH2) == LT)
			cond_2 = 1;
	}

	//Return true if both conditions are satisfied, otherwise return false.
	return (cond_1 & cond_2);
}

/*
* Launch Intercept Condition 13
* There exists at least one set of three data points, separated by exactly A_PTS 
* and B_PTS consecutive intervening points, respectively, that cannot be 
* contained within or on a circle of radius RADIUS1. In addition, there exists
* at least one set of three data points (which can be the same or different from 
* the three data points just mentioned) separated by exactly A PTS and B PTS 
* consecutive intervening points, respectively, that can be contained in or
* on a circle of radius RADIUS2. Both parts must be true for the LIC to be true. 
* The condition is not met when NUMPOINTS < 5.
*/
boolean LIC13()
{
	//Initialization
	boolean cond_1 = 0;
	boolean cond_2 = 0;
	int i;
	double a, b, r, ang1, ang2, ang3;

	//The condition is not met when NUMPOINTS < 5
	if (NUMPOINTS < 5)
		return 0;

	//For each  point (X[i], Y[i]), determine the next point as seperated by the
	// number of points designated by A_PTS. Take that point, and determine the 
	// next point as seperated by the number of points designated by B_PTS.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2)); i++)
	{
		//Note: the "+1" is necessary to seperate out the number of points 
		// designated by A_PTS. I.e. if A_PTS is 2, the we need to check X[0] and
		// X[3], since there are two points
		//in between 0 and 3.
		int pt_one = i + PARAMETERS.A_PTS + 1;
		int pt_two = pt_one + PARAMETERS.B_PTS + 1;

		//Find the slope of the line
		if ((X[pt_two] != X[pt_one]) && (X[pt_one] != X[i]))
		{	//Determine the slopes
			a = ((Y[pt_two] - Y[pt_one]) / (X[pt_two] - X[pt_one]));
			b = ((Y[i] - Y[pt_one]) / (X[i] - X[pt_one]));
		}
		else if ((X[pt_two] == X[pt_one]) && (X[pt_one] == X[i]))
		{
			a = 1;
			b = 1;
		}
		else
		{
			a = 1;
			b = 5;
		}

		//Compares Slopes to decide if line or Triangle
		if (DOUBLECOMPARE(a, b) == EQ)
		{
			//The points form a line, so compute the greatest separation between 
			// the points to find the length of the line.
			a = length_point(X[i], Y[i], X[pt_one], Y[pt_one]);
			b = length_point(X[i], Y[i], X[pt_two], Y[pt_two]);
			r = length_point(X[pt_two], Y[pt_two], X[pt_one], Y[pt_one]);

			//Find the longest distance formed by the three points, which should 
			// correspond to the total length of the line.
			if (DOUBLECOMPARE(a, b) == GT)
			{
				if (DOUBLECOMPARE(a, r) == GT)
				{
					// The radius of the circle must be greater than or equal to 
					// half the length of the line.
					if (DOUBLECOMPARE((a / 2), PARAMETERS.RADIUS1) == GT)
						cond_1 = 1;
					if (DOUBLECOMPARE((a / 2), PARAMETERS.RADIUS2) < GT)
						cond_2 = 1;
				}
				else
				{
					//The radius of the circle must be greater than or equal to 
					// half the length of the line.
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS1) == GT)
						cond_1 = 1;
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS2) < GT)
						cond_2 = 1;
				}
			}
			else
			{
				if (DOUBLECOMPARE(b, r) == GT)
				{
					//The radius of the circle must be greater than or equal to 
					// half the length of the line.
					if (DOUBLECOMPARE((b / 2), PARAMETERS.RADIUS1) == GT)
						cond_1 = 1;
					if (DOUBLECOMPARE((b / 2), PARAMETERS.RADIUS2) < GT)
						cond_2 = 1;
				}
				else
				{
					//The radius of the circle must be greater than or equal to 
					// half the length
					//of the line.
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS1) == GT)
						cond_1 = 1;
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS2) < GT)
						cond_2 = 1;
				}
			}
		}
		else
		{
			//The points form a triangle, and all triangles are circumscribable. 
			// Thus, the radius of the circle should be greater than or equal to 
			// the circumradius if the triangle is an acute or right triangle. 
			// For obtuse triangles, the radius of circle must be greater than 
			// half the length of the longest side.
			ang1 = angle_points(X[i], Y[i], 
				X[i + PARAMETERS.A_PTS + 1], 
				Y[i + PARAMETERS.A_PTS + 1], 
				X[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2], 
				Y[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2]);
			ang2 = angle_points(X[i], Y[i], 
				X[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2], 
				Y[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2], 
				X[i + PARAMETERS.A_PTS + 1], 
				Y[i + PARAMETERS.A_PTS + 1]);
			ang3 = angle_points(
				X[i + PARAMETERS.A_PTS + 1], 
				Y[i + PARAMETERS.A_PTS + 1], 
				X[i], 
				Y[i], 
				X[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2], 
				Y[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2]);

			// If the triangle is an acute or right triangle, then RADIUS 1
			// should be greater than or equal to the  circumradius of the 
			// triangle. For obtuse triangles, the radius of circle must be 
			// greater than half the length of the longest side.
			if ((DOUBLECOMPARE(ang1, PI / 2) < GT) && 
				(DOUBLECOMPARE(ang2, PI / 2) < GT) && 
				(DOUBLECOMPARE(ang3, PI / 2) < GT))
				r = circumcenter(X[i], Y[i], X[pt_one], Y[pt_one], 
				X[pt_two], Y[pt_two]);
			else
			{
				if (DOUBLECOMPARE(ang1, PI / 2) == GT)
					r = (length_point(X[i], Y[i], X[pt_two], Y[pt_two])) / 2;
				else if (DOUBLECOMPARE(ang2, PI / 2) == GT)
					r = (length_point(X[i], Y[i], X[pt_one], Y[pt_one])) / 2;
				else
					r = (length_point(X[pt_one], Y[pt_one], 
					X[pt_two], Y[pt_two])) / 2;
			}

			//Set the conditions
			if (DOUBLECOMPARE(PARAMETERS.RADIUS1, r) == LT)
				cond_1 = 1;
			if (DOUBLECOMPARE(PARAMETERS.RADIUS2, r) > LT)
				cond_2 = 1;
		}
	}

	//Return true if both conditions are satisfied, otherwise return false.
	return (cond_1 & cond_2);
}

/*
* Launch Intercept Condition 14
* There exists at least one set of three data points, separated by exactly E_PTS 
* and F_PTS consecutive intervening points, respectively, that are the vertices 
* of a triangle with area greater than AREA1. In addition, there exist three
* data points (which can be the same or different from the three data points just
* mentioned) separated by exactly E PTS and F PTS consecutive intervening points,
* respectively, that are the vertices of a triangle with area less than AREA2. 
* Both parts must be true for the LIC to be true. The condition is not met when 
* NUMPOINTS < 5.
*/
boolean LIC14()
{
	//Initialization
	boolean cond_1 = 0;
	boolean cond_2 = 0;
	double area;
	int i;

	//The condition is not met when NUMPOINTS < 5
	if (NUMPOINTS < 5)
		return 0;

	//For each  point (X[i], Y[i]), determine the next point as seperated by the 
	// number of points designated by E_PTS. Take that point, and determine the 
	// next point as seperated by the number of points designated by F_PTS.
	for (i = 0; i < (NUMPOINTS - (PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2)); i++)
	{
		area = Calculate_Area_Triangle(
			X[i], 
			Y[i], 
			X[i + PARAMETERS.E_PTS + 1], 
			Y[i + PARAMETERS.E_PTS + 1], 
			X[i + PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2], 
			Y[i + PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2]);
		if (DOUBLECOMPARE(area, PARAMETERS.AREA1) == GT)
			cond_1 = 1;
		if (DOUBLECOMPARE(area, PARAMETERS.AREA2) == LT)
			cond_2 = 1;
	}

	//Return true if both conditions are satisfied, otherwise return false.
	return (cond_1 & cond_2);
}


// -- Helper Functions -- //
/*
* This function calculates the area of a triangle given three points in the same 
* plane.
*/
double Calculate_Area_Triangle(double ax, double ay, double bx, double by, 
	double cx, double cy)
{
	//Determine the length between the given points
	double A = length_point(ax, ay, bx, by);
	double B = length_point(bx, by, cx, cy);
	double C = length_point(ax, ay, cx, cy);

	//Heron's formula for area calculation
	double s = (A + B + C) / 2;
	double area = sqrt(s * (s - A) * (s - B) * (s - C));

	//Return the resulting area calculation
	return area;
}

/*
* This function takes in a two by two boolean matrix and the index of a row 
* number. It returns 1 (TRUE) if all elements in the given row are 1 (TRUE). 
* Otherwise it returns FALSE.
*/
boolean all_elements_in_row_are_true(BMATRIX two_by_two_matrix, int row)
{
	//Initialization
	int column;

	// Loop through each element in the row
	for (column = 0; column < 15; column++)
	{
		//Return false if there is a false element
		if (two_by_two_matrix[row][column] == 0)
			return 0;
	}
	return 1;
}


/*
* This function takes the points in space and returns the distance of seperation 
* of the points. The formula used is that of a standard coordinate distance 
* between poinrs.
*/
double length_point(double x1, double y1, double x2, double y2)
{
	return sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
}

/*
* This function takes the vertices of a triangle and returns their circumradius.
* The formula used is that of a standard circumradius of a triangle.
*/
double circumcenter(double x1, double y1, double x2, double y2, 
	double x3, double y3)
{
	//Initialization
	double area, a, b, c;

	//Calculate the distances between the points
	a = length_point(x1, y1, x2, y2);
	b = length_point(x1, y1, x3, y3);
	c = length_point(x3, y3, x2, y2);

	//Calculate the area of the triangle
	area = Calculate_Area_Triangle(x1, y1, x2, y2, x3, y3);

	//Determine the radius from the area and return
	return (a*b*c) / (4 * area);
}

/*
* This function returns the angle as calculated between the three points.
*/
double angle_points(double x1, double y1, double x2, double y2, 
	double x3, double y3)
{
	//Initialization
	double cos_Angle, a, b, c;

	//Calculate the distances between the points
	a = length_point(x1, y1, x2, y2);
	b = length_point(x3, y3, x2, y2);
	c = length_point(x1, y1, x3, y3);

	//Use the Law of Cosines to determine the angle and return
	cos_Angle = (((a*a) + (b*b) - (c*c)) / (2 * a*b));
	return acos(cos_Angle);
}

/*
* This function determines the quadrant that the given point lies within. Giving 
* priority by quandrant number to ambiquous quandrant points.
*/
int Quadrant_point(double x, double y)
{
	if ((x >= 0) && (y >= 0))
		return 1;
	else if ((x < 0) && (y >= 0))
		return 2;
	else if ((x <= 0) && (y < 0))
		return 3;
	return 4;
}s