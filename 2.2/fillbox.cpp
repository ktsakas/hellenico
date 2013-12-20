#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

unsigned long long int fillBox ( int L, int W, int H ) {
	if ( L == 0 or W == 0 or H == 0 ) return 0; 

	int maxBox = pow(2, int(log2(min(min(L, W), H))));
	unsigned long long int
		Lx = L/maxBox, remL = L%maxBox,
		Wx = W/maxBox, remW = W%maxBox,
		Hx = H/maxBox, remH = H%maxBox,
		boxes = Lx*Wx*Hx;

	boxes += fillBox(L, W, remH);
	boxes += fillBox(L, remW, H-remH);
	boxes += fillBox(remL, W-remW, H-remH);

	return boxes;
}

int main() {
	ifstream input("fillbox.in");
	ofstream output("fillbox.out");

	int L, W, H;
	input >> L >> W >> H;

	output << fillBox(L, W, H) << endl;

	input.close();
	output.close();

	return 0;
}