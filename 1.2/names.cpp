#include <iostream>
#include <fstream>

using namespace std;

int main () {
	ifstream input("names.in");
	ofstream output("names.out");

	// Read total number of names
	int totalNames;
	input >> totalNames;

	// Initialize variables
	string curName, curEqualName, minName, minEqualName;
	string lastLetter;

	// Skip first line break
	getline(input, curName);

	// Read first name
	getline(input, curName);
	minEqualName = minName = curEqualName = curName;

	for ( int i= 0; i < totalNames; i++ ) {
		int nameLength = curName.length();
		for ( int c= 0; c < nameLength; c++ ) {
			// If this form of the name is
			// lexically smaller than the minimum name form
			if ( curEqualName < minEqualName ) {
				minEqualName = curEqualName;
				minName = curName;
			}

			// Create equal name
			// by adding the last letter at the beggining of the word
			lastLetter = curEqualName[ nameLength-1 ];
			curEqualName = lastLetter + curEqualName.erase(nameLength-1, 1);
		}

		// Read next name
		getline(input, curName);
		curEqualName = curName;
	}

	// Write min name to file
	output << minName;

	// Wrap things up
	input.close();
	output.close();

	return 0;
}
