#include <iostream>
#include <algorithm>
#include <cmath>

#include "UBXPUtils.hpp"
#include "UBXPf0122_3280.hpp"
#include "UBXPf0122_3280-data.hpp"

UBXPf0122_3280::UBXPf0122_3280() :
    numQtrs_(StateHPIs.size()), qtr0_(StateHPIs[0].first)
{
    month0_ = qtr0_ - qtr0_ % 100 + (qtr0_ % 100) * 3 - 2; // month0_ start from the first month of a quarter
    for(States s = AK; s != NumStates; s = (States)(s + 1)) state2Idx_[StateName[s]] = s;
}

double UBXPf0122_3280::fCalc(const string& sLTVKey, int iOrigMonth, int iAsofMonth, double fOrigLTV, double fFactor) const
{
    int origQtrIdx = max<int>(0, GetRelativeMonth(iOrigMonth, month0_) / 3);
    int currQtrIdx = min<int>(numQtrs_ - 1, GetRelativeMonth(iAsofMonth, month0_) / 3);
    const auto it = state2Idx_.find(sLTVKey);
    int LTVIdx = (it != state2Idx_.end()) ? state2Idx_.at(sLTVKey): DefaultStateIdx;
    double origHPI = StateHPIs[origQtrIdx].second[LTVIdx];
    double currHPI = StateHPIs[currQtrIdx].second[LTVIdx];
    //cout <<origHPI<<" "<<currHPI<<endl;
    return fOrigLTV * fFactor * origHPI / currHPI;
}
