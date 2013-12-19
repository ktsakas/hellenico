#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct dims { int w, h; };

// Finds all the factors of num that are up to max
// and returns them along with their counterparts (num/factor)
vector<dims> getFactorCouples ( int num, int max ) {
	vector<dims> factorCouples;
	dims factorCouple;
	for ( int i= ceil(float(num)/max); i <= max; i++ ) {
		// If the number is a factor
		if ( num%i == 0 ) {
			factorCouple.w = i;
			factorCouple.h = num/i;
			factorCouples.push_back( factorCouple );
		}
	}

	return factorCouples;
}


// Count the number of coordinates that are empty in an area
int countEmptyCoords ( dims box, int tranX, int tranY, vector< vector<int> > coords ) {
	int empty = 0;
	// Go left
	for ( int x= tranX; x < tranX+box.w; x++ ) {
		// Go top
		for ( int y= tranY; y < tranY+box.h; y++ ) {
			if ( coords[x][y] == 0 ) empty++;
		}
	}

	return empty;
}

int main () {
	ifstream input("nered.in");
	ofstream output("nered.out");

	int N, boxes;
	input >> N >> boxes;
	// Set the number of cubes on all coords to zero
	vector< vector<int> > coords; // x, y
	for ( int x= 0; x <= N; x++ ) {
		coords.push_back( vector<int>() );
		for ( int y= 0; y <= N; y++ ) coords[x].push_back(0);
	}
	// Read coords
	int x, y;
	while ( input >> x >> y ) coords[x][y]++;


	// Get possible box dimentions
	vector<dims> areas = getFactorCouples( boxes, N );
	dims box;
	int emptyCoords,
		minSwaps = boxes;

	// Loop possible box dimentions
	for ( int i= 0; i < areas.size(); i++ ) {
		box = areas[i];

		// Loop possible box positions
		for ( int tranX= 1; tranX+box.w <= 1+N; tranX++ ) {
			for ( int tranY= 1; tranY+box.h <= 1+N; tranY++ ) {
				emptyCoords = countEmptyCoords( box, tranX, tranY, coords );

				// Pick the one that has the least empty coordinates
				minSwaps = min(emptyCoords, minSwaps);
			}
		}
	}

	cout << minSwaps << endl;

	// Wrap things up
	input.close();
	output.close();
	
	return 0;
}