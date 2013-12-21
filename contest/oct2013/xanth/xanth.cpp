#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// Walks the circle and sets all lengths to be equal
// Note: the circle can have length one
int circleLength ( int *circleEnter, int links[], int maxLengths[], int circleLength ) {
	int *node = circleEnter;
	do {
		// Visit the next circular node
		// and set its length
		maxLengths[*node] = circleLength;
		node = links + *node;
	} while ( node != circleEnter );
}

// Walks the path as if it were a straight line
// and sets the max length of each node as the length
// of the next one plus one
// it stops when the path ends or it hits a node that it already visited
// which means it entered a circle and sets circleEnter to equal
// the node where the circle was first entered
// it returns the length of the given node
int maxLineLength ( int *node, int links[], int maxLengths[], int **circleEnter ) {
	int nodeIndex = node-links;

	// If the node has been visited
	if ( maxLengths[ nodeIndex ] > -1 ) {
		// If no length has been calculated
		// we are in a circle
		if ( maxLengths[ nodeIndex ] == 0 ) {
			*circleEnter = node;
		} else *circleEnter = NULL;
		// Return it's current length
		return maxLengths[nodeIndex];
	}

	// Mark node as visited, but no length calculated
	maxLengths[ nodeIndex ] = 0;

	// Set the max length of this node to
	// equal that of the next one plus one
	maxLengths[ nodeIndex ] =
		1 + maxLineLength( links + *node, links, maxLengths, circleEnter );
}

int calcMaxLengths ( int *node, int links[], int maxLengths[] ) {
	int *circleEnter;
	maxLineLength( node, links, maxLengths, &circleEnter );
	if ( circleEnter != NULL ) {
		int circleEnterIndex = circleEnter-links;
		circleLength( circleEnter, links, maxLengths, maxLengths[circleEnterIndex] );
	}
}

// The problem asks us to find
// the longest path from one node to another
// in a digraph with an out degree of one
int main () {
	ifstream input("xanth.in");
	ofstream output("xanth.out");

	int N;
	input >> N;
	int links[N],
		maxLengths[N];

	for ( int i= 0; input >> links[i]; i++ ) {
		links[i]--;
		maxLengths[i] = -1;
	}

	for ( int i= 0; i < N; ) {
		calcMaxLengths( links+i, links, maxLengths );

		// Skip the lengths that have been calculated
		while ( maxLengths[i] > 0 ) i++;
	}

	int maxLength = *max_element( maxLengths, maxLengths+N );
	output << maxLength  << endl;

	input.close();
	output.close();

	return 0;
}