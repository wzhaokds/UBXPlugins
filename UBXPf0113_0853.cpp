#include "UBXPf0113_0853.hpp"
#include "UBXPf0113_0853-data.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>


UBXPf0113_0853::UBXPf0113_0853() :
    aCurves_(aCurves), seasonality_(Seasonality), sCurves_(NumProds), sCurveRanges_(NumProds)
{
    for(Prod p = FN30; p != NumProds; p = (Prod)(p + 1)) name2Prod_[ProdName[p]] = p;

    for(auto& e: seasonality_) // convert CPR's to multipliers using the average CPR per product
	transform(e.begin(), e.end()-1, e.begin(), [&e](double s){ return s / e.at(12); });

    int prod = 0;
    auto sCurvesCopy = sCurves;
    for(auto& sPoints: sCurvesCopy) {
	for(auto& e: sPoints) {
	    e.second /= seasonality_.at(prod).at(12); // scale the CPR to average CPR of the product
	}
	int nSections = sPoints.size() - 1;
	sCurveRanges_[prod] = {sPoints[0].first, sPoints[nSections].first};
	int nPoints = sPoints[sPoints.size()-1].first - sPoints[0].first + 1;
	sCurves_[prod] = vector<double>(nPoints);
	vector<double>& sc = sCurves_[prod];
	//cout <<ProdName[prod]<<": "<<sPoints[0].first<<", "<<sPoints[nSections].first<<": "<< sc.size() <<": ";
	int idx = 1;
	sc[0] = sPoints[0].second;
	for(int i=1; i<=nSections; ++i) { // linearly interpolate intermediate values within each secion, say, [-250, -225]
	    int cnt = sPoints[i].first - sPoints[i-1].first;
	    double step = (sPoints[i].second - sPoints[i-1].second) / cnt;
	    double value = sPoints[i-1].second;
	    generate_n(sc.begin() + idx, cnt, [&value, step]() { return value += step; });
	    idx += cnt;
	}
	//cout <<sc[0]<<","<<sc[100]<<","<<sc[200]<<":"<<sc[250]<<":"<<sc[300]<<","<<sc[400]<<","<<sc[500]<<endl;
	++prod;
    }

}

double UBXPf0113_0853::fCalc(const string& sProgID, int iAsofdt, double fSpread, double fWAM, double fWALA) const {
    int oterm = lround(fWAM + fWALA);
    auto it = name2Prod_.find(sProgID.substr(0,2) + (oterm > 270? string("30"): string("15")));
    int prod = it != name2Prod_.end() ? it->second: FN30; // default to FN30

    int month = (iAsofdt) % 100 - 1;
    int age = min<int>(aCurves_[prod].size()-1, lround(fWALA)); // round to an integer age field
    int spreadOffset = min<int>(sCurveRanges_[prod].second - sCurveRanges_[prod].first, lround(fSpread) - sCurveRanges_[prod].first);
    //cout << prod<<','<<month<<','<<age<<','<<spreadOffset<<'\n';
    return min<double>(100., seasonality_[prod][month] * aCurves_[prod][age] * sCurves_[prod][spreadOffset]);
}
