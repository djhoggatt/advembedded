boolean LIC8()
{
	debug1 = 533;
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
		debug1 = 545;
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
		debug1 = 558;
		//Find the slope of the line
		if ((X[pt_two] != X[pt_one]) && (X[pt_one] != X[i]))
		{	//Determine the slopes
			debug1 = 562;
			a = ((Y[pt_two] - Y[pt_one]) / (X[pt_two] - X[pt_one]));
			b = ((Y[i] - Y[pt_one]) / (X[i] - X[pt_one]));
		}
		else if ((X[pt_two] == X[pt_one]) && (X[pt_one] == X[i]))
		{
			debug1 = 568;
			a = 1;
			b = 1;
		}
		else
		{
			debug1 = 574;
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
			debug1 = 586;
			// Find the longest distance formed by the three points, which should
			// correspond to the total length of the line.
			if (DOUBLECOMPARE(a, b) == GT)
			{
				debug1 = 591;
				if (DOUBLECOMPARE(a, r) == GT)
				{
					debug1 = 594;
					// The radius of the circle must be greater than or equal to
					// half the length of the line
					if (DOUBLECOMPARE((a / 2), PARAMETERS.RADIUS1))
					{
						debug1 = 599;
						return 1;
					}
				}
				else
				{
					debug1 = 605;
					//The radius of the circle must be greater than or equal to
					// half the length of the line
					if (DOUBLECOMPARE((r / 2), PARAMETERS.RADIUS1))
					{
						debug1 = 610;
						return 1;
					}
				}
			}
			else
			{
				debug1 = 617;
				if (DOUBLECOMPARE(b, r) == GT)
				{
					debug1 = 620;
					//The radius of the circle must be greater than or equal to 
					/// half the length of the line
					if (DOUBLECOMPARE((b / 2), PARAMETERS.RADIUS1))
					{
						debug1 = 625;
						return 1;
					}
				}
				else
				{
					debug1 = 631;
					//The radius of the circle must be greater than or equal to 
					// half the length of the line
					double r_half = r / (double)2;
					if (DOUBLECOMPARE((r_half), PARAMETERS.RADIUS1))
					{
						debug1 = 636;
						return 1;
					}
				}
			}
		}
		else
		{
			debug1 = 644;
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
			{
				debug1 = 664;
				r = circumcenter(X[i], Y[i], X[pt_one], Y[pt_one],
					X[pt_two], Y[pt_two]);
			}
			else
			{
				debug1 = 669;
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
			{
				debug1 = 682;
				return 1;
			}
		}
	}
	debug1 = 687;
	//If no points are found that satisfy the condition, return false.
	return 0;
}