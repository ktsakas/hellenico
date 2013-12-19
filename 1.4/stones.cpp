#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct stone {
	int volume;
	int mass;
};

// Sort by ratio
bool operator <( stone a, stone b ) {
	double aRatio, bRatio;
	aRatio = double(a.volume) / a.mass;
	bRatio = double(b.volume) / b.mass;
	return aRatio < bRatio;
}

int main () {
	ifstream input("stones.in");
	ofstream output("stones.out");
	
	// Initialize variables	
	int N, max_vol;
	input >> N >> max_vol;
	stone* stones = new stone[N];

	// Read file
	for ( int i= 0; input >> stones[i].volume >> stones[i].mass; i++ );

	// Sort stones by volume/mass ratio
	sort( stones, stones+N );

	double max_mass = 0;
	for ( int i= 0; max_vol > 0; i++ ) {
		// The available volume is enough
		if ( stones[i].volume <= max_vol ) {
			max_mass += stones[i].mass;
			max_vol -= stones[i].volume;
		// Break the stone in smaller piece	
		} else {
			max_mass += stones[i].mass * double(max_vol)/stones[i].volume;
			max_vol = 0;
		}
	}

	// Output to file
	output.precision(3);
	output.setf( ios::fixed, ios::floatfield );
	output << max_mass << endl;

	// Wrap things up
	input.close();
	output.close();

	return 0;
}