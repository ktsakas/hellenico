#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;

struct client {
	int id, start, end;
};

bool operator< (const client &a, const client &b) {
	return a.end < b.end;
}

// Non-weighted interval scheduling
int main() {
	ifstream input("rentacar.in");
	ofstream output("rentacar.out");

	// Read params
	int N;
	input >> N;

	client clients[N];
	for (int i= 0; input >> clients[i].id >> clients[i].start >> clients[i].end; i++);

	// Sort clients by end
	sort(clients, clients+N);

	int start= 0, end= clients[0].end, count= 1;
	for (int i= 1; i < N; i++) {
		start= max(start, clients[i].start);

		if ( end < start ) {
			end= clients[i].end;
			count++;
		}
	}

	// cout << count << endl;
	output << count << endl;

	input.close();
	output.close();

	return 0;
}