#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

// Check if three ints have all digits from 1-9
bool all9Digits ( int M, int M1, int M2 ) {
	int i, digits[10] = {0};
	do { digits[M%10]++; M /= 10; } while (M > 0);
	do { digits[M1%10]++; M1 /= 10; } while (M1 > 0);
	do { digits[M2%10]++; M2 /= 10; } while (M2 > 0);

	for ( i= 1; i < 10 and digits[i] > 0; i++ );
	return (i == 10);
}

int main () {
	ifstream input("digits.in");
	ofstream output("digits.out");

	// Read M as string first to get length
	string Mstr;
	input >> Mstr;

	int M, M1= 0, M2;
	istringstream(Mstr) >> M;

	int Msize = Mstr.length(),
		M1size = (9-2*Msize+1)/2,
		M2size = 9-M1size-Msize,
		skipZeros = 0,
		M1min, M1max;

	// Calculate number to add to skip zeros (eg. for 100 its 11)
	for ( int p= 0; p < M1size-1; p++ ) skipZeros += pow(10, p);
	// Calculate min and maximum M1
	M1min = ceil( pow(10, M1size-1) );
	M1max = ceil( (pow(10, M2size)-1)/M );

	for ( M1 = M1min; M1 < M1max; M1++ ) {
		// Skip mutipliers with zeros
		if ( M1%M1min == 0 ) M1 += skipZeros;
		M2 = M*M1;
		// Check if the numbers match the criteria
		if ( all9Digits(M, M1, M2) ) break;
	}


	// Output result
	if ( M1 < M1max ) 
		output << M1 << " " << M2 << endl;
	else output << "0" << endl;


	// Wrap things up
	input.close();
	output.close();

	return 0;
}