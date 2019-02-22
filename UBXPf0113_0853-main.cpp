#include <iostream>
#include <stdlib.h>
#include "UBXPf0113_0853.hpp"

int main(int argc, char* argv[]) {
    if (argc < 5) {
	cerr << argv[0] << ": expecting 5 args, product asofdate wac wam wala" << endl;
	exit(0);
    }
    cout <<"ok, executing"<< endl;
    UBXPf0113_0853 ubxp = UBXPf0113_0853();
    double ret = ubxp.fCalc(argv[1], atoi(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
    cout <<"UBXpf0113_0853.fCalc() = "<< ret << endl;
}
