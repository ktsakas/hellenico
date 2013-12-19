#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
	ifstream input("boat.in");
	ofstream output("boat.out");

	// Read total number of names
	int totalLines;
	input >> totalLines;

	// Initialize variables
	vector<string> carStack;
	string car, cars;
	int carsOut, carsIn;

	for ( int i= 0; i < totalLines; i++ ) {
		input >> carsOut >> carsIn;

		// Pop cars going out from the stack
		for ( int c= 0; c < carsOut; c++ ) {
			carStack.pop_back();
		}

		// Push the cars going in
		// onto the stack
		getline( input, cars );
		istringstream is(cars);
		while ( is >> car ) {
			carStack.push_back( car );
		}
	}

	// Sort cars alphabetically
	sort( carStack.begin(), carStack.end() );

	// Output cars to file
	for ( int i= 0; i < carStack.size(); i++ ) {
		output << carStack[i] << endl;
	}

	// Wrap things up
	input.close();
	output.close();

	return 0;
}
