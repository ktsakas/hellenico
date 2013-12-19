#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main () {
	ifstream input("crocodiles.in");
	ofstream output("crocodiles.out");
	
	int N;
	input >> N;
	int *births = new int[N],
		*deaths = new int[N];
	for ( int i= 0; input >> births[i] >> deaths[i]; i++ );

	// Sort birth and death years
	sort( births, births+N );
	sort( deaths, deaths+N );
	
	int maxAlive = 0,
		curAlive = 0;
	int birthI= 0, deathI= 0;
	// Loop years from first birth to last death
	for ( int year= births[0]; year <= deaths[N-1]; year++ ) {
		// Add new born crocodiles to alive
		while ( birthI < N and births[birthI] == year ) {
			curAlive++;
			birthI++;
		}
		// Remove crocodiles that died
		while ( deathI < N and deaths[deathI] == year ) {
			curAlive--;
			deathI++;
		}

		if ( maxAlive < curAlive ) maxAlive = curAlive;
	}

	output << maxAlive << endl;


	// Wrap things up
	delete[] births;
	delete[] deaths;
	input.close();
	output.close();

	return 0;
}