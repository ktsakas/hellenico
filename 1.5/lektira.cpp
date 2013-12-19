#include <iostream>
#include <fstream>

using namespace std;

// Find the maximum reversed substring of a string
// beggining from the first letter that is
// the lexicographically smallest
string findSubString ( string str ) {
	string min(1, str[0]);
	string subStr, reversedSubStr;
	for ( int len= 2; len <= str.size(); len++ ) {
		subStr = str.substr(0, len);
		reversedSubStr = string( subStr.rbegin(), subStr.rend() );

		if ( reversedSubStr < min ) min= reversedSubStr;
	}

	return min;
}

int main () {
	ifstream input("lektira.in");
	ofstream output("lektira.out");

	string str;
	input >> str;
	int N = str.length();

	int len = 0;
	string str1 = findSubString( str.substr(0, N-2) );
	len += str1.length();
	string str2 = findSubString( str.substr(len, N-1-len) );
	len += str2.length();
	string str3 = str.substr(len, N-len);
	str3 = string( str3.rbegin(), str3.rend() );

	output << str1 << str2 << str3 << endl;

	// Wrap things up
	input.close();
	output.close();
	
	return 0;
}