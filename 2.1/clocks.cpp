#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <list>
#include <string>

using namespace std;

void runMove ( int move, string &board ) {
	string moves[9] = {
		"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"
	};

	move--;
	char clockI;
	for ( int i= 0; i < moves[move].length(); i++ ) {
		clockI = moves[move][i]-'A';
		board[clockI]= (board[clockI]-'0'+1)%4 + '0';
	}
}

void fillCombos ( list< string > &combos, int positions, int values ) {
	if ( positions == 0 ) {
		combos.push_back("");
		return;
	}
	fillCombos( combos, positions-1, values );

	for ( int i= 0, size= combos.size(); i < size; i++ ) {
		string small_combo = combos.front();
		combos.pop_front();

		for ( char i= '0'; i < '0'+values; i++ ) {
			combos.push_back( small_combo+i );
		}
	}
}

bool blueprintsOverlay ( string &bp1, string &bp2 ) {
	for (int i= 0; i < 9; i++) {
		if ( bp1[i] != '-' and bp2[i] != '-' and bp1[i] != bp2[i] ) {
			return false;
		} else if ( bp1[i] == '-' ) {
			bp1[i] = bp2[i];
		}
	}
	return true;
}

void overlayCombos ( list<string> &blueprints1, list<string> &blueprints2 ) {
	for (int i= 0, size= blueprints1.size(); i < size; i++ ) {
		string blueprint = blueprints1.front();
		blueprints1.pop_front();

		list<string>::iterator it= blueprints2.begin();
		for ( ; it != blueprints2.end(); it++ ) {\
			string copyBlueprint = blueprint;
			bool success= blueprintsOverlay( copyBlueprint, (*it) );

			if ( success ) {
				blueprints1.push_back(copyBlueprint);
			}			
		}
	}
}

int main () {
	/*list<string> bp1, bp2;
	bp1.push_back("100------");
	bp1.push_back("--301----");
	bp2.push_back("--0---11-");
	bp2.push_back("------111");
	overlayCombos( bp1, bp2 );
	list<string>::iterator skr= bp1.begin();
	for ( ; skr != bp1.end(); skr++ ) {
		cout << (*skr) << endl;
	}*/

	ifstream input("clocks.in");
	ofstream output("clocks.out");

	// Read board state as string
	string board = "", copyBoard;
	int state;
	while ( input >> state ) board += '0'+state;
	list<string> moveCombos;
	// fillCombos( moveCombos, 2, 3 );
	
	// cout << board << endl;
	// runMove(2, board);
	// cout << board << endl;

	// Create blueprints required to solve a clock
	// eg. A needs on turn a possible blueprint is "10-0-----"
	// numbers represent number of times to run the move
	// and dashed that the move does not affect the clock
	int moves[9][6] = {
		{0,1,3,-1},     // A
		{0,1,2,4,-1},   // B
		{1,2,5,-1},     // C
		{0,3,4,6,-1},   // D
		{0,2,4,6,8,-1}, // E
		{2,4,5,8,-1},   // F
		{3,6,7,-1},     // G
		{4,6,7,8,-1},   // H
		{5,7,8,-1}      // I
		// "ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"
	};

	list<string> blueprints[9];
	list<string>::iterator it;
	// Loop through clocks
	for (int i= 0; i < 9; i++) {
		// Find number of times to turn the clock
		int turns = (4-board[i]+'0')%4;

		// Find number of moves affecting this clock
		int len= 0;
		for ( ; moves[i][len] != -1; len++ );
		// cout << char('A'+i) << " turns: " << turns << " affecting moves: " << len << endl;

		// Create all possible combinations
		// of how many times to run each move
		fillCombos(blueprints[i], len, 4);
		// cout << "Blueprints for " << char('A'+i) << ": \n";
		// Remove all blueprints that do not turn the clock to 12
		it= blueprints[i].begin();
		while ( it != blueprints[i].end() ) {
			int count = 0;
			for ( int c= 0; c < it->size(); c++ )
				count += (*it)[c]-'0';

			if ( turns != count%4 ) {
				it = blueprints[i].erase(it);
			} else {
				it++;
			}
		}

		// Create the actual blueprints
		// eg. --1--00--
		it= blueprints[i].begin();
		for ( ; it != blueprints[i].end(); it++ ) {
			string blueprint(9, '-');
			for (int c= 0; moves[i][c] != -1; c++) {
				blueprint[ moves[i][c] ] = (*it)[c];
			}

			*it = blueprint;
			// cout << "\t" << blueprint << "\n";
		}
	}




	// Loop through clocks and eliminate solutions
	// between any two clocks that do not agree
	list<string> solutions = blueprints[0];
	for (int i= 1; i < 9; i++) {
		overlayCombos( solutions, blueprints[i] );

		/*cout << "Solutions until: " << char('A'+i) << endl;
		cout << "Size: " << solutions.size() << endl;
		list<string>::iterator skr= solutions.begin();
		for ( ; skr != solutions.end(); skr++ ) {
			cout << (*skr) << endl;
		}*/
	}

	/*list<string>::iterator skr= solutions.begin();
	for ( ; skr != solutions.end(); skr++ ) {
		cout << (*skr) << endl;
	}*/



	// There is only one blueprint of
	// moves that give out a solution

	// Sort the possible solutions
	/*solutions.sort();

	// Pick the first with the smallest count of moves
	int minCount = 3*18;
	string solution;
	it = solutions.begin();
	for ( ; it != solutions.end(); it++ ) {
		// cout << (*it) << endl;
		int count = 0;
		for ( int i= 0; i < 9; i++ ) count += (*it)[i]-'0';

		if ( count < minCount ) {
			solution= (*it);
			minCount= count;
		}
	}*/

	// cout << solution << endl;

	// string solution = solutions.front();
	// Print solution
	for ( int i= 0; i < 9; i++ ) {
		for ( int c= 0; c < solution[i]-'0'; c++ ) {
			// runMove(i+1, board);
			output << i+1 << " ";
		}
	}

	// cout << board << endl;

	// Wrap things up
	input.close();
	output.close();

	return 0;
}