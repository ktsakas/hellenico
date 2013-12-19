#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

// Calculate the minimum number of cubes required
// to reach a certain height for a given step
int minCubes ( int height, int step ) {
	// Calculate the first term of
	// the arithmetic sequence (can be 0)
	// as the height of the first step
	int firstStep = height % step;
	// Calculate the total number of terms
	// in the arithmetic sequence (total steps)
	int totalSteps = height / step + 1;

	// Return the sum of the arithmetic sequence
	return ( float(totalSteps) / 2 ) * ( firstStep + height );
}

int main () {
	ifstream input("cubes.in");
	ofstream output("cubes.out");

	// Read total number of names
	int cubes, step;
	input >> cubes >> step;

	// When the minimum # of cubes required
	// to reach a certain height becomes larger
	// than the number of given cubes, the (height-1) is
	// the maximum height we can reach with the given cubes
	int height = 1;
	for ( ; minCubes( height, step ) <= cubes; height++ );

	// Output max height to file
	int maxHeight = height-1;
	output << maxHeight;

	// Wrap things up
	input.close();
	output.close();

	return 0;
}
