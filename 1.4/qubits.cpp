#include <iostream>
#include <fstream>

using namespace std;

// Tower of hanoi aglorithm
void towerOfHanoi ( ofstream &output, int disks, char a= 'A', char b= 'B', char c= 'C' ) {
	if ( disks == 1 ) {
		output << a << " " << c << "\n";
	} else {
		// Move all disks but last from a to b
		towerOfHanoi( output, disks-1, a, c, b );
		// Move last disk to c
		output << a << " " << c << "\n";
		// Move the disks from b to c
		towerOfHanoi( output, disks-1, b, a, c );
	}
}

int main () {
	ifstream input("qubits.in");
	ofstream output("qubits.out");

	int N;
	input >> N;
	towerOfHanoi( output, N );

	input.close();
	output.close();
	
	return 0;
}