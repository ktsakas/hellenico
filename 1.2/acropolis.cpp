#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("acropolis.in");
    ofstream output("acropolis.out");

    int N;
    input >> N;
    int nums[N];
    for ( int i= 0; i < N; i++ ) input >> nums[i];

    // Bubble sort
    int temp;
    for ( int i= 0; i < N; i++ ) {
        if ( nums[i] == 1 ) continue;
        for ( int c= i+1; c < N; c++ ) {
            if ( nums[c] == 1 ) continue;
            // Swap integers
            if ( nums[i] > nums[c] ) {
                temp= nums[i];
                nums[i]= nums[c];
                nums[c]= temp;
            }
        }
    }

    for ( int i= 0; i < N; i++ ) output << nums[i] << "\n";

    return 0;
}
