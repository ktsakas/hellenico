#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main () {
	ifstream input("coins.in");
	ofstream output("coins.out");

	// Read params
	int c[3]= {1}, N;
	input >> c[1] >> c[2] >> N;
	int gameCoins[N];
	for (int i= 0; input >> gameCoins[i]; i++);

	// Memory usage can be improved vastly
	int maxCoins= *max_element(gameCoins, gameCoins+N);
	bool wins[maxCoins+1];
	for ( int i= 0; i < maxCoins+1; i++ ) {
		if (
			(0 <= i-c[0] and !wins[i-c[0]]) or
			(0 <= i-c[1] and !wins[i-c[1]]) or
			(0 <= i-c[2] and !wins[i-c[2]])
		   ) {
			wins[i]= true;
		} else {
			wins[i]= false;
		}
	}
	
	for (int i= 0; i < N; i++) {
		output << (wins[ gameCoins[i] ] ? "A" : "B");
	}
	output << endl;

	// Wrap things up
	input.close();
	output.close();

	return 0;
}