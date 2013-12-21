#include <iostream>
#include <fstream>

using namespace std;

// Get total cost for some students with a certain discount
int cost ( int totalStudents, float discount ) {
    return int( (totalStudents*10) * (1-discount) + 0.5 );
}

int main()
{
    ifstream input("tickets.in");
    ofstream output("tickets.out");

    // Initialize variables
    int N, mins[5]= {0};
    float discount[5]= {0, 0.1, 0.2, 0.3, 0.5};
    input >> N >> mins[1] >> mins[2] >> mins[3] >> mins[4];

    // Find minimun number of students
    int c= 0;
    while ( c+1 <= 4 && mins[c+1] <= N ) c++;

    // Find normal cost
    int normalPrice= cost( N, discount[c] );
    // Find cost of buying extra tickets
    int extraTicketsPrice= cost( mins[c+1], discount[c+1] );
    for ( int i= c+2; i <= 4; i++ ) {
        if ( extraTicketsPrice > cost( mins[i], discount[i] ) )
            extraTicketsPrice= cost( mins[i], discount[i] );
    }

    // Output the cheapest to the file
    if ( normalPrice < extraTicketsPrice ) {
        output << normalPrice << "\n";
    } else {
        output << extraTicketsPrice << "\n";
    }

    return 0;
}
