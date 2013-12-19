#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main () {
	ifstream input("dna.in");
	ofstream output("dna.out");

	// Initialize dna length (N)
	// and maximum symbol period (maxP)
	// and read them from file
	int N, maxP;
	input >> N >> maxP;

	// DNA sequence
	string dna;
	// Read dna sequence
	input >> dna;

	// Holds frequency of nucleod for a given position
	int nucleoidFreq[4],
	// Set min replacements to the max posible
	// which is the dna string length
		minReplace = dna.length();

	// Loop period lengths
	for ( int periodLen= 1; periodLen <= maxP; periodLen++ ) {

		// Minimun replacements for the current period length
		int minPeriodReplace = 0;

		// Loop period positions
		for ( int periodPos= 0; periodPos < periodLen; periodPos++ ) {
			// Initialize freq to 0
			for ( int i= 0; i < 4; i++ ) nucleoidFreq[i] = 0;

			// How many times this period pos exists
			int periodPosTotal = 0;
			// Loop positions in string
			for ( int pos= periodPos; pos < dna.length(); pos += periodLen ) {
				periodPosTotal++;
				switch ( dna[pos] ){
					case 'A':
						nucleoidFreq[0]++;
						break;
					case 'C':
						nucleoidFreq[1]++;
						break;
					case 'G':
						nucleoidFreq[2]++;
						break;
					case 'T':
						nucleoidFreq[3]++;
						break;
				}			
			}

			// Get the max freq of a letter in this position
			int maxFreq = *max_element( nucleoidFreq, nucleoidFreq+4 );
			// Minimun replacements for the current position in a period
			int minPosReplace = periodPosTotal - maxFreq;
			// Add to total minimum replacements for current period length
			minPeriodReplace += minPosReplace;
		}

		// Find the minimum replacements
		if ( minPeriodReplace < minReplace ) {
			minReplace = minPeriodReplace;
		}

	}

	// Output to file
	output << minReplace;

	
	// Wrap things up
	input.close();
	output.close();

	return 0;
}
