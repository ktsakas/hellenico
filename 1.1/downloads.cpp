#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main()
{
    ifstream input("downloads.in");
    ofstream output("downloads.out");

    // Initialize variables and read data into them
    int N;
    input >> N;
    double speed[N], time[N], totalTime= 0;
    for ( int c= 0; input >> speed[c] >> time[c]; c++ );

    int i, c;
    for ( int t= 0; t < N; t++ ) {
        // Find the time when the next download will end
        double nextDown= 0;
        for ( i= 0; i < N; i++ ) {
            if ( ( time[i] != 0 and time[i] < nextDown ) or
                 ( nextDown == 0 ) ) {
                nextDown= time[i];
            }
        }

        // Add the time of that download to the total time
        totalTime += nextDown;

        // Remove the time that passed from each download
        for ( i= 0; i < N; i++ ) {
            if ( time[i] != 0 ) time[i] -= nextDown;
        }

        // Find the extra bandwith available
        double extraBand= 0;
        for ( int i= 0; i < N; i++ ) {
            if ( time[i] == 0 && speed[i] != 0 ) {
                extraBand += speed[i];
                speed[i]= 0;
            }
        }

        // Find a download to distribute the extra bandwith
        for ( c= 0; c < N-1; c++ ) {
            if ( time[c] != 0 ) break;
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
