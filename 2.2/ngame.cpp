#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <string>

using namespace std;

struct state {
	int score;
	state *prev;
};

int main () {
	ifstream input("ngame.in");
	ofstream output("ngame.out");

	// Read params
	int N;
	input >> N;
	int nums[N];
	for (int i= 0; input >> nums[i]; i++);

	string board;
	state tmp= {0, NULL},
		  *leftState, *rightState;
	int leftScore, rightScore;
	map<string, state> scores;
	scores[""]= tmp;
	scores[""].prev = &scores[""];

	// Loop lengths
	for (int i= 1; i <= N; i++) {
		// Loop start position
		for (int p= 0; p <= N-i; p++) {
			board= "";
			// Loop numbers
			for (int c= 0; c < i; c++) {
				board += char(nums[p+c]+'0') + string(" ");
			}

			// Play optimally by chosing the side
			// from which the number you pick plus the score
			// you get from the rest of the numbers is the greatest
			leftState = &scores[board.substr(2, board.length())],
			rightState = &scores[board.substr(0, board.length()-2)];

			leftScore = leftState->prev->score + nums[p],
			rightScore = rightState->prev->score + nums[p+i-1];
			
			if ( leftScore < rightScore ) {
				tmp.score = rightScore;
				tmp.prev = rightState;
			} else {
				tmp.score = leftScore;
				tmp.prev = leftState;
			}
			scores[board] = tmp;

		}
	}

	output << scores[board].score << " " << scores[board].prev->score;

	// Wrap things up
	input.close();
	output.close();

	return 0;
}