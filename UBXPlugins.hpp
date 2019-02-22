#ifndef _UBXPlugins_H_
#define _UBXPlugins_H_
#include <string>
using namespace std;

// UBXPlugin interface naming conventions: UBXPosif: o - object; s - string; i - integer; f - floating-point 
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
    
class UBXP0122
{
public:
    virtual double fCalc(const string& sInput, int iInput1, int iInput2,
			 double fInput1, double fInput2) const = 0;
};
    
#endif // _UBXPlugins_H_
