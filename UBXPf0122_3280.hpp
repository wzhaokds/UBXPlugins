#ifndef _UBXPf0122_3280_H_
#define _UBXPf0122_3280_H_
#include "UBXPlugins.hpp"
#include <vector>
#include <map>
#include <utility>

class UBXPf0122_3280 : public UBXP0122
{
public:
    UBXPf0122_3280();
    double fCalc(const string& sLTVKey, int iOrigMonth, int iAsofMonth, double fOrigLTV, double fFactor) const;
    // sLTVKey, e.g., state; OrigMonth and AsofMonth: integer in YYYYMM; fFactor: loan factor or ratio of currLnSz/origLnSz
private:
    pair<int,int> dateBounds_;       // start and ending months
    map<string, int> state2Idx_;     // state field position in the StateHPI
    int numQtrs_, qtr0_, month0_;    // number quarters, first quarter and month
};

#endif // _UBXPf0122_3280_H_
