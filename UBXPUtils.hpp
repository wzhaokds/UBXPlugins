#ifndef _UBXPUtils_H_
#define _UBXPUtils_H_

int GetDateYYYYMM(int delta, int startYYYYMM) {
    int months = startYYYYMM % 100 + int(startYYYYMM / 100) * 12 + delta;
    int month = months % 12;
    if (month == 0)
	return (months/12 - 1) * 100 + 12;
    return (months/12) * 100 + month;
};

int GetRelativeMonth(int date1, int date2) { 
    return (date1 / 100 - date2 / 100) * 12 + date1 % 100 - date2 % 100;
};

#endif // _UBXPUtils_H_
