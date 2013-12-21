#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ns4 ( string &word ) {
	if ( word.find('L') == string::npos ) return;
	
	for (int i=0; i < word.length(); i++) {
		switch ( word[i] ) {
			case 'A':
				word[i]= '4';
				break;
			case 'I':
				word[i]= '1';
				break;
			case 'O':
				word[i]= '0';
				break;
		}
	}
}

int main () {
	ifstream input("ns4.in");
	ofstream output("ns4.out");

	int N;
	input >> N;

	string word;
	while ( input >> word ) {
		ns4(word);
		output << word << endl;
	}

	input.close();
	output.close();

	return 0;
}