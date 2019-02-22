#ifndef _UBXPf0113_0853_H_
#define _UBXPf0113_0853_H_
#include "UBXPlugins.hpp"
#include <vector>
#include <map>
#include <utility>

class UBXPf0113_0853 : public UBXP0113
{
public:
    UBXPf0113_0853();
    double fCalc(const string& sProd, int iAsofdt, double fWAC, double fWAM, double fWALA) const;

private:
    vector<vector<double> > aCurves_;      // CPR vector age 0 to 360/180 for each product
    vector<vector<double> > seasonality_;  // seasonality multiplier for each product
    vector<vector<double> > sCurves_;      // refi incentive multiplier for each product
    vector<pair<int, int> > sCurveRanges_; // (min, max) bounds incentive for each product
    map<string, int> name2Prod_;           // product name to a numerical ID for the above vectors
};
#endif // _UBXPf0113_0853_H_
