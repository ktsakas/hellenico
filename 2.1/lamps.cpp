#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool criteriaMatches ( string lamps, int on[], int off[] ) {
	// cout << on[0] << " " << on[1] << endl;
	// cout << off[0] << " " << off[1] << endl;
	if ( 
		(on[0] != -1 and lamps[on[0]-1] == '0') or
		(on[1] != -1 and lamps[on[1]-1] == '0')
	) return false;

	if ( 
		(off[0] != -1 and lamps[off[0]-1] == '1') or
		(off[1] != -1 and lamps[off[1]-1] == '1')
	) return false;

	return true;
}

bitset<100> press ( int button, bitset<100> lamps, int N ) {
	if ( button == 1 ) return lamps.flip();

	bitset<100> mask;
	int i= (button == 3) ? 1 : 0,
		leap = (button == 4) ? 3 : 2;

	for ( ; i < N; i+= leap) mask[i]= 1;

	return lamps^mask;
}

int main () {
	ifstream input("lamps.in");
	ofstream output("lamps.out");

	int N, flips;
	input >> N >> flips;

	int on[2]= {-1, -1}, off[2]= {-1, -1};
	for ( int i= 0; (input >> on[i]) and on[i] != -1; i++ );
	for ( int i= 0; (input >> off[i]) and off[i] != -1; i++ );


	/*bitset<100> lamps( string("1111111111") ), lampsState;
	int states[8][4] = {
		{0,0,0,0}, {0,0,0,1}, {0,1,0,1}, {0,0,1,1},
		{1,0,0,1}, {0,0,1,0}, {1,0,0,0}, {0,1,0,0}
	};
	for (int i= 0; i < 8; i++) {
		lampsState = lamps;
		for (int button= 1; button <= 4; button++) {
			if ( states[i][button-1] == 1 )
				lampsState = press(button, lampsState, N);
		}

		cout << "State " << i+1 << ": " << lampsState.to_string().substr(100-N, 100) << endl;
	}*/

	bitset<100> lamps, lampsState;
	vector<string> lampStates;
	lamps.set();
	// cout << criteriaMatches(lamps, on, off) << endl;
	// Buttons array has zero for a button pressed an even number of times
	// and one for buttons that are pressed odd times
	int buttons[4] = {0,0,0,0}, count;
	// Loop through every possible combination of button presses
	for (int i= flips%2; i <= min(4, flips); i+= 2) {
		for (int k= 0; k < i; k++) buttons[3-k]= 1;

		do {
			lampsState= lamps;
			count= 0;
			for (int c= 0; c < 4; c++) {
				if ( buttons[c]== 1 )
					lampsState= press(c+1, lampsState, N);
			}
			
			// cout << lampsState.to_string().substr(100-N, 100) << endl;
			string stateStr = lampsState.to_string().substr(100-N, 100);
			if ( criteriaMatches(stateStr, on, off) ) 
				lampStates.push_back( stateStr );
			// cout << buttons[0] << buttons[1] << buttons[2] << buttons[3] << endl;

		} while ( next_permutation(buttons, buttons+4) );
	}

	sort(lampStates.begin(), lampStates.end());
	unique(lampStates.begin(), lampStates.end());

	vector<string>::iterator it= lampStates.begin();
	for ( ; it != lampStates.end(); it++ ) {
		cout << (*it) << "\n";
	}

	// Wrap things up
	input.close();
	output.close();

	return 0;
}