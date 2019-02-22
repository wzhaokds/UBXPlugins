#include <iostream>
#include <stdlib.h>
#include "UBXPf0115_0302.hpp"

int main(int argc, char* argv[]) {
    if (argc < 7) {
	cerr << argv[0] << ": expecting 7 args, product asofdate wac wam wala tune1 tune2" << endl;
    }
    cout <<"ok, executing"<< endl;
    UBXPf0115_0302 ubxp = UBXPf0115_0302();
    double ret = ubxp.fCalc(argv[1], atoi(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
    cout <<"UBXpf0115_0302.fCalc() = "<< ret << endl;
}
