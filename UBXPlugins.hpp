#ifndef _UBXPlugins_H_
#include <string>
using namespace std;
class UBXP0115
{
public:
    virtual double fCalc(const string& sInput, int iInput,
			double fInput1, double fInput2, double fInput3, double fInput4, double fInput5) = 0;
};
    
class UBXP0113
{
public:
    virtual double fCalc(const string& sInput, int iInput,
			double fInput1, double fInput2, double fInput3) const = 0;
};
    
#endif // _UBXPlugins_H_
