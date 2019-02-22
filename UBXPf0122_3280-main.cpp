#include <iostream>
#include <stdlib.h>
#include "UBXPf0122_3280.hpp"

int main(int argc, char* argv[]) {
    if (argc < 5) {
	cerr << argv[0] << ": expecting 5 args, state OrigMonth(YYYYMM) AsofMonth(YYYYMM) OrigLTV factor" << endl;
	exit(0);
    }
    cout <<"ok, executing"<< endl;
    UBXPf0122_3280 ubxp = UBXPf0122_3280();
    double ret = ubxp.fCalc(argv[1], atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atof(argv[5]));
    cout <<"UBXpf0122_3280.fCalc() = "<< ret << endl;
}
