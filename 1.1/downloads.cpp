#include <iostream>
#include <fstream>
#include<time.h>

using namespace std;

int main()
{
    ifstream input("downloads.in");
    ofstream output("downloads.out");

    // Initialize variables and read data into them
    int N;
    input >> N;
    double speed[N], time[N];
    for ( int c= 0; input >> speed[c] >> time[c]; c++ );

    double totalTime= 0;
    for ( int t= 0; t < N; t++ ) {
        // Find the time when the next download will end
        int i= 0;
        double nextDown= 0;
        do {
            if ( ( time[i] != 0 && time[i] < nextDown ) ||
                 ( nextDown == 0 ) ) {
                nextDown= time[i];
            }
            i++;
        } while ( i < N );

        // Add the time of that download to the total time
        totalTime += nextDown;

        // Remove the time that passed from each download
        for ( int t= 0; t < N; t++ ) {
            if ( time[t] != 0 ) time[t] -= nextDown;
        }

        // Find the extra bandwith available
        double extraBand= 0;
        for ( int x= 0; x < N; x++ ) {
            if ( time[x] == 0 && speed[x] != 0 ) {
                extraBand += speed[x];
                speed[x]= 0;
            }
        }

        // Find a download to distribute the extra bandwith
        int c= 0;
        while ( c < N-1 ) {
            if ( time[c] != 0 ) break;
            c++;
        }

        // Calculate the download's new speed and time
        if ( time[c] != 0 ) {
            time[c] *= speed[c]/(speed[c]+extraBand);
            speed[c] += extraBand;
        }
    }

    // Output rounded download time to file
    output << int( totalTime + 0.5 ) << "\n";

    input.close();
    output.close();

    return 0;
}
