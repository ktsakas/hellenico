#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream input("time.in");
    ofstream output("time.out");

    // Initialize variables
    int hours, minutes, seconds;
    int newHours= 0, newMinutes= 0, newSeconds= 0;
    // Read time
    input >> hours;
    input.seekg (3, ios::beg);
    input >> minutes;
    input.seekg (6, ios::beg);
    input >> seconds;

    // Save new time
    newSeconds= (seconds*2)%60;
    if ( seconds*2 >= 60 ) newMinutes++;

    newMinutes += (minutes*2);
    if ( newMinutes >= 60 ) {
        newMinutes %= 60;
        newHours++;
    }

    newHours += (hours*2);

    // Output to file with leading zeros
    output << setw(2) << setfill('0') << newHours << ":"
           << setw(2) << setfill('0') << newMinutes << ":"
           << setw(2) << setfill('0') << newSeconds << endl;

    return 0;
}
