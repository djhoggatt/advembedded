// This is version 4 of this file.

#include <math.h>

//////////// CONSTANT //////////

static const double PI = 3.1415926535;

//////////// TYPE DECLARATIONS ///////////

typedef enum { NOTUSED=777, ORR, ANDD } CONNECTORS;

// pointer to an array of 100 doubles
typedef double *COORDINATE;

// pointer to a 2-D array of [15,15] CONNECTORS
typedef CONNECTORS **CMATRIX;

// always in the range [0..1]
typedef int boolean;

// pointer to a 2-D array of [15,15] booleans
typedef boolean **BMATRIX;

// pointer to an array of 15 booleans
typedef boolean *VECTOR;

typedef enum { LT=1111, EQ, GT} COMPTYPE;

static inline
COMPTYPE DOUBLECOMPARE (double A,
double B)
{
	if (fabs(A-B)<0.000001) return EQ;
	if (A<B) return LT;
	return GT;
}