#if !defined(__PERSIANSUPPORT_H_4WINCE42)
#define __PERSIANSUPPORT_H_4WINCE42


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define N_DISTINCT_CHARACTERS 205


void ArabicReverse(CString &s);
BOOL isFromTheSet1(WCHAR ch);
BOOL isFromTheSet2(WCHAR ch);
CString Arabize (LPCTSTR in);
void MakeCharArrayWCHARARRAY(char* cCharArray, WCHAR* wCharArray);
void gregorian_to_jalali(
	int *j_y,
	int *j_m,
	int *j_d,
	const int g_y,
	const int g_m,
	const int g_d);


#endif