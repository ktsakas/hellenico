#include <iostream>
#include <fstream>

using namespace std;

int main () {
	ifstream input("sort3.in");
	ofstream output("sort3.out");

	// Read total number of metals
	int totalMetals;
	input >> totalMetals;

	// Read metals in array
	int *metals = new int[totalMetals];
	// inRange[ range ][ metalCount ]
	int inRange[4][4] = {0};
	int count[4] = {0};

	// Count occurences of each metal
	int metal;
	for ( int i= 0; input >> metals[i]; i++ ) count[ metals[i] ]++;

	for ( int i= 0, range= 1; i < totalMetals; i += count[range], range++ ) {
		// Loop through metals in range
		for ( int c= 0; c < count[range]; c++ ) {
			inRange[ range ][ metals[i+c] ]++;
		}
	}

	// Count efficient swaps first where
	// exchanging two metals sorts both of them
	int minSwaps = 0;
	int swaps = min(inRange[1][2], inRange[2][1]);
	minSwaps += swaps;
	inRange[1][2] -= swaps;
	inRange[2][1] -= swaps;

	swaps = min(inRange[1][3], inRange[3][1]);
	minSwaps += swaps;
	inRange[1][3] -= swaps;
	inRange[3][1] -= swaps;

	swaps = min(inRange[2][3], inRange[3][2]);
	minSwaps += swaps;
	inRange[2][3] -= swaps;
	inRange[3][2] -= swaps;

	// Do inefficient swaps
	minSwaps += 2 * (inRange[1][2] + inRange[2][1]);
	
	output << minSwaps << endl;

	// Wrap things up
	input.close();
	output.close();
	delete[] metals;

	return 0;
}
