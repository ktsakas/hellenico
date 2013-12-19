#include <iostream>
#include <istream>
#include <cstdlib>
#include <fstream>

using namespace std;

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int main()
{
    ifstream input("elevator.in");
    ofstream output("elevator.out");

    int N;
    input >> N;
    int weight[N], e= (N/2 + N%2), lift[e];
    // Read and sort weights
    for ( int i= 0; i < N; i++ ) input >> weight[i];
    qsort (weight, N, sizeof(int), compare);

    // Go from outermost to innermost weights
    // and add them every two
    for ( int i= 0; i < N/2; i++ ) {
        lift[i]= weight[i]+weight[(N-1)-(N%2)-i];
    }
    if ( N%2 == 1 ) lift[N-1]= weight[N-1];

    // Resort array
    qsort(lift, e, sizeof(int), compare);

    output << e << " " << lift[e-1] << "\n";

    return 0;
}
