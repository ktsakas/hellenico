#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Check if a number is prime
bool isPrime ( int num ) {
	if ( num < 2 ) return false;
	if ( num < 4 ) return true;
	if ( num%2 == 0 ) return false;
	
	for ( int i= 3, numSqrt = sqrt(num); i <= numSqrt; i+= 2 ) {
		if ( num%i == 0 ) return false;
	}
	return true;
}

int main() {
	ifstream input("goldbach.in");
	ofstream output("goldbach.out");

	// Read N
	int N;
	input >> N;

	// Save to file the fist two integers,
	// that add up to N
	for ( int i= 2; i < N; i++ ) {
		if ( isPrime(i) and isPrime(N-i) ) {
			output << i << " " << N-i << "\n";
			break;
		}
	}

	return 0;
}
