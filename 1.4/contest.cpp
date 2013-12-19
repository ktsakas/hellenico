#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// Find the path that has the most corals
int findMaxCorals ( map<int, int> nodes[], int cur_node= 1 ) {
	map<int, int> links = nodes[cur_node];
	// The path stops
	if ( links.empty() ) return 0;
	
	map<int, int>::iterator it;
	int link, corals, maxPathCorals,
		maxCorals = 0;

	// Loop through node links
	// and find path with the maximum corals recursively
	for ( it= links.begin(); it != links.end(); it++ ) {
		link = it->first;
		corals = it->second;
		maxPathCorals = corals + findMaxCorals( nodes, link );

		if ( maxCorals < maxPathCorals ) maxCorals = maxPathCorals;
	}
	return maxCorals;
}

int main () {
	ifstream input("contest.in");
	ofstream output("contest.out");

	// Read from file
	int N;
	input >> N;

	int node, link, corals;
	map<int, int>* nodes = new map<int, int>[N+1];
	for ( int i= 0; input >> node >> link >> corals; i++ ) {
		nodes[node][link] = corals;
	}

	output << findMaxCorals( nodes ) << endl;

	// Wrap things up
	delete[] nodes;
	input.close();
	output.close();
	
	return 0;
}