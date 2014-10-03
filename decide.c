/*
 * Team 11  CS 5785
 * Team Assignment #1: decide.c
 * SPENCER CLEGG, DENVER HOGGATT, ROHITH PRASAD, COLTON OTTLEY
  */

#include "decide.h"

// -- Forward Declarations -- //
boolean LIC0();
boolean LIC1();
boolean LIC2();
boolean all_elements_in_row_are_true(BMATRIX, int);
double Calculate_Area_Triangle(double, double, double, double ,double ,double);
double length_point(double ,double ,double ,double );
double circumcenter(double ,double ,double ,double ,double ,double );

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
 * If Slope of the line formed by any 2 points eqauls that of any other combination, then the points lie on a single Line
 * If the Slope of a line formed by any two points are different, they form a Triangle
 */
boolean LIC1()
{ int ch,ch1,ch2,ch3,i;
  double a,b,r;

  for( i = 0; i<NUMPOINTS-2; i++)
    {
      //Finding slope of a line by standard formulae( Learnt in Highschool)

     a = ((Y[i+2] - Y[i+1])/(X[i+2] - X[i+1]));
     b = ((Y[i] - Y[i+1])/(X[i] - X[i+1]));
     //Compares Slopes to decide if line or Triangle
     ch=  DOUBLECOMPARE(a,b);
       if(ch == EQ)
          {
            // Decidesthat it is a Line So copmute the greatest seperation between the points to find length of the line
            a = length_point(X[i],Y[i],X[i+1],Y[i+1]);
            b = length_point(X[i],Y[i],X[i+2],Y[i+2]);
            r = length_point(X[i+2],Y[i+2],X[i+1],Y[i+1]);
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
            // the Radius of the Cicle should be greater than or equal to the Circumradius
             r  = circumcenter(X[i],Y[i],X[i+1],Y[i+1],X[i+2],Y[i+2]);
             ch1 = DOUBLECOMPARE(PARAMETERS.RADIUS1,r);
             if(ch1 == LT)
                  { return 1;}
           }
    }
   return 0;
}

/*
 * LIC[2]: There exists at least one set of three consecutive data points
 * that are the vertices of a triangle with area greater than AREA1.
 */
boolean LIC2()
{ int i;
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
  NUMPOINTS = 3;
  
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