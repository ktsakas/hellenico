#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <vector>
#include <algorithm>
#include <ctime>
#include <list>

using namespace std;

void fillCombos ( list< string > &combos, int positions, int values ) {
	if ( positions == 0 ) {
		combos.push_back("");
		return;
	}
	fillCombos( combos, positions-1, values );

	for ( int i= 0, size= combos.size(); i < size; i++ ) {
		string small_combo = combos.front();
		combos.pop_front();

		for ( char i= '1'; i < '1'+values; i++ ) {
			combos.push_back( small_combo+i );
		}
	}
}

bool comboMatches ( string combo, char code[], int len ) {
	int posCount= 0, colorCount= 0;
	for ( int i= 0; i < len; i++ ) {
		if ( combo[i] == code[i] ) {
			posCount++;
		} else if ( combo.find_first_of(code[i]) != string::npos ) {
			colorCount++;
		}
	}

	// cout << posCount << " " << colorCount << endl;
	// cout << int(code[len]-'0') << " " << int(code[len+1]-'0') << endl;
	return (posCount == code[len]-'0' and colorCount == code[len+1]-'0');
}

void eliminateCombos ( list< string > &combos, char code[], int len ) {
	list<string>::iterator it= combos.begin();
	while ( it != combos.end() ) {
		// cout << *it << " " << comboMatches(*it, code, len) << endl;
		if ( !comboMatches(*it, code, len) ) {
			it = combos.erase(it);
		} else it++;
	}
}

int main () {
	ifstream input("mastermind.in");
	ofstream output("mastermind.out");

	// Read params
	int N, colors, len;
	input >> N >> colors >> len;
	// cout << N << " " << colors << " " << len << endl;
	char *codes = new char[N*(len+2)];
	// Read codes
	for ( int i= 0; input >> codes[i]; i++ );
	// cout << codes[0] << codes[1] << codes[2] << codes[3] << codes[4] << endl;
	
	list< string > combos;
	fillCombos( combos, len, colors );
	// eliminateCombos( combos, codes, len );
	for ( int l= 0; l < N; l++ ) {
		eliminateCombos( combos, &codes[l*(len+2)], len );
	}

	/*list< string >::iterator it= combos.begin();
	for ( ; it != combos.end(); it++ ) {
		output << (*it) << "\n";
	}*/
	output << combos.size() << endl;

	// Wrap things up
	input.close();
	output.close();

	return 0;
}