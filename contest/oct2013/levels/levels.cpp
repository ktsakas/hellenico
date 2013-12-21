#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main () {
    ifstream input("levels.in");
    ofstream output("levels.out");

    int N;
    input >> N;
    unsigned long long int levels[N];

    for ( int i= 0; i < N; i++ ) {
        input >> levels[i];
    }

    sort( levels, levels+N );

    unsigned long long int sum= levels[0];
    for ( int i= 1; i < N; i++ ) {
        levels[i] = levels[i-1] + levels[i];
        sum += levels[i];
    }
    
    output << sum << endl;

    input.close();
    output.close();

    return 0;
}