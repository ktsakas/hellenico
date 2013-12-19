#include <iostream>
#include "hiddenlib.h"

using namespace std;

int findBox( int rangeMin, int rangeMax ) {
	// If the range has converged to a number return it
	if ( rangeMin == rangeMax ) return rangeMin;

	int diff = rangeMax-rangeMin,
		x = int( rangeMin + float(diff)/4 + 0.5 ),
		y = int( rangeMin + 3*float(diff)/4 + 0.5 ),
		comp = compare(x, y);

	// x and y are equally distant
	if ( comp == 0 ) {
		return (x+y)/2;
	// x is closer
	} else if ( comp == 1 ) {
		return findBox( rangeMin, (x+y)/2 );
	// y is closer
	} else {
		return findBox( (x+y)/2 + 1, rangeMax );
	}
}


int main () {
	// Call is hidden to end game
	// with the box we found
	ishidden( findBox(1, getN()) );

	return 1;
}
