#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;

struct control {

};

int calc ( int company, map< map<int> > control, map< map<int> > percents ) {
    for (int i= 1; i < control[company].size(); i++) {
        if ( control[company][i] == true ) {
            
        }
    }


}

int main() {
    ifstream input("companies.in");
    ofstream output("companies.out");

    // Read params
    int N;
    input >> N;

    map< int,  > control, percents;
    int companies, controler, controlee, percent;
    while ( input >> controler >> controlee >> percent ) {
        percents[controler][controlee] = percent;
        if ( percent > 50 ) control[controler][controlee]= true;
    }

    /*for (int i= 1; i < control[2].size(); i++) {
        cout << control[2][i] << endl;
    }*/

    input.close();
    output.close();

    return 0;
}