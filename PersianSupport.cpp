#include "stdafx.h"
#include "CONTOR.h"
#include "PersianSupport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void ArabicReverse(CString &s)
{
    CString out, rev;
    s.MakeReverse();

    int i=0;
    while(i<s.GetLength())
    {
        if((s[i]>='0' && s[i]<='9'))    // isDigit(s[i]) ?
        {
            rev.Empty();
            while((s[i]>='0' && s[i]<='9'))    // isDigit(s[i]) ?
            {
                rev = rev + s[i];
                ++i;
            }
            rev.MakeReverse();
            out = out + rev;
        }
        else
        {
            out = out + s[i];
            ++i;
        }
    }
    s=out;
}

BOOL isFromTheSet1(WCHAR ch)
{
    static WCHAR theSet1[27/*22*/]={
        0x62c, 0x62d, 0x62e, 0x647, 0x639, 0x63a, 0x641, 0x642,
        0x62b, 0x635, 0x636, 0x637, 0x643, 0x645, 0x646, 0x62a,
        0x644, 0x628, 0x64a, 0x633, 0x634, 0x638, 0x6Af, 0x6A9,
		0x686, 0x67E, 0x626};
    int i = 0;
    while (i < 27/*22*/)
    {
        if(ch == theSet1[i])
            return TRUE;
        ++i;
    }
    return FALSE;
}
//////////////////////////////////////////////////////////////////////
BOOL isFromTheSet2(WCHAR ch)
{
    static WCHAR theSet2[13/*12*/]={
        0x627, 0x623, 0x625, 0x622, 0x62f, 0x630, 0x631, 0x632,
        0x648, 0x624, 0x629, 0x649, 0x698};
    int i = 0;
    while (i < 13/*12*/)
    {
        if(ch == theSet2[i])
            return TRUE;
        ++i;
    }
    return FALSE;
}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
CString Arabize (LPCTSTR in)
{
    static struct
    {
        WCHAR character;
        WCHAR endGlyph;
        WCHAR iniGlyph;
        WCHAR midGlyph;
        WCHAR isoGlyph;
    }a[N_DISTINCT_CHARACTERS]=
    {
        {0x630, 0xfeac, 0xfeab, 0xfeac, 0xfeab},
        {0x62f, 0xfeaa, 0xfea9, 0xfeaa, 0xfea9},
        {0x62c, 0xfe9e, 0xfe9f, 0xfea0, 0xfe9d},
        {0x62d, 0xfea2, 0xfea3, 0xfea4, 0xfea1},
        {0x62e, 0xfea6, 0xfea7, 0xfea8, 0xfea5},
        {0x647, 0xfeea, 0xfeeb, 0xfeec, 0xfee9},
        {0x639, 0xfeca, 0xfecb, 0xfecc, 0xfec9},
        {0x63a, 0xfece, 0xfecf, 0xfed0, 0xfecd},
        {0x641, 0xfed2, 0xfed3, 0xfed4, 0xfed1},
        {0x642, 0xfed6, 0xfed7, 0xfed8, 0xfed5},
        {0x62b, 0xfe9a, 0xfe9b, 0xfe9c, 0xfe99},
        {0x635, 0xfeba, 0xfebb, 0xfebc, 0xfeb9},
        {0x636, 0xfebe, 0xfebf, 0xfec0, 0xfebd},
        {0x637, 0xfec2, 0xfec3, 0xfec4, 0xfec1},
        {0x643, 0xfeda, 0xfedb, 0xfedc, 0xfed9},
        {0x645, 0xfee2, 0xfee3, 0xfee4, 0xfee1},
        {0x646, 0xfee6, 0xfee7, 0xfee8, 0xfee5},
        {0x62a, 0xfe96, 0xfe97, 0xfe98, 0xfe95},
        {0x627, 0xfe8e, 0xfe8d, 0xfe8e, 0xfe8d},
        {0x644, 0xfede, 0xfedf, 0xfee0, 0xfedd},
        {0x628, 0xfe90, 0xfe91, 0xfe92, 0xfe8f},
        {0x64a, 0xfef2, 0xfef3, 0xfef4, 0xfef1},
        {0x633, 0xfeb2, 0xfeb3, 0xfeb4, 0xfeb1},
        {0x634, 0xfeb6, 0xfeb7, 0xfeb8, 0xfeb5},
        {0x638, 0xfec6, 0xfec7, 0xfec8, 0xfec5},
        {0x632, 0xfeb0, 0xfeaf, 0xfeb0, 0xfeaf},
        {0x648, 0xfeee, 0xfeed, 0xfeee, 0xfeed},
        {0x629, 0xfe94, 0xfe93, 0xfe93, 0xfe93},
        {0x649, 0xfef0, 0xfeef, 0xfef0, 0xfeef},
        {0x631, 0xfeae, 0xfead, 0xfeae, 0xfead},
        {0x624, 0xfe86, 0xfe85, 0xfe86, 0xfe85},
        {0x621, 0xfe80, 0xfe80, 0xfe80, 0xfe7f},
        {0x626, 0xfe8a, 0xfe8b, 0xfe8c, 0xfe89},
        {0x623, 0xfe84, 0xfe83, 0xfe84, 0xfe83},
        {0x622, 0xfe82, 0xfe81, 0xfe82, 0xfe81},
        {0x625, 0xfe88, 0xfe87, 0xfe88, 0xfe87},
		{0x6A9, 0xfb8f, 0xfb90, 0xfb91, 0xfb8e},
		{0x6Af, 0xfb93, 0xfb94, 0xfb95, 0xfb92},
		{0x698, 0xfb8b, 0xfb8a, 0xfb8b, 0xfb8a},
		{0x686, 0xfb7b, 0xfb7c, 0xfb7d, 0xfb7a},
		{0x67E, 0xfb57, 0xfb58, 0xfb59, 0xfb56},
    };
    BOOL linkBefore, linkAfter;
    CString out;
    out=in;
    for(UINT i=0; i<_tcslen(in); i++)
    {
        WCHAR ch=in[i];
        if((ch>=0x0621 && ch<=0x064a)||(ch==0x6A9)||(ch==0x6Af)||(ch==0x686)||(ch==0x67E)) // is a Persian character?
        {
            int idx = 0;
            while (idx < N_DISTINCT_CHARACTERS)
            {
                if (a[idx].character == in[i])
                    break;
                ++idx;
            }
            
            if(i == _tcslen(in) - 1)
                linkAfter=0;
            else
                linkAfter = (isFromTheSet1(in[i+1]) || 
                                   isFromTheSet2(in[i+1]));
            if(i == 0)
                linkBefore=0;
            else
                linkBefore=isFromTheSet1(in[i-1]);
    
            if(linkBefore && linkAfter)
                out.SetAt(i, a[idx].midGlyph);
            if(linkBefore && !linkAfter)
                out.SetAt(i, a[idx].endGlyph);
            if(!linkBefore && linkAfter)
                out.SetAt(i, a[idx].iniGlyph);
            if(!linkBefore && !linkAfter)
                out.SetAt(i, a[idx].isoGlyph);
        }
    }
    ArabicReverse (out);
    return out;
}


void MakeCharArrayWCHARARRAY(char* cCharArray, WCHAR* wCharArray)
{
	//removing spaces:
	int i=0;
	while(cCharArray[i]==' ')
		i++;	
	int j=0;
	int iLen=strlen(cCharArray);
	for(;i<iLen; i++)
	{
		switch(cCharArray[i])
		{
		case '¿'://ARABIC QUESTION MARK
			wCharArray[j++]=0x061F;
			break;
		case 'À'://ARABIC LETTER HEH GOAL
			wCharArray[j++]=0x06C1;
			break;
		case 'Á'://ARABIC LETTER HAMZA
			wCharArray[j++]=0x0621;
			break;
		case 'Â'://ARABIC LETTER ALEF WITH MADDA ABOVE
			wCharArray[j++]=0x0622;
			break;
		case 'Ã'://ARABIC LETTER ALEF WITH HAMZA ABOVE
			wCharArray[j++]=0x0623;
			break;
		case 'Ä'://ARABIC LETTER WAW WITH HAMZA ABOVE
			wCharArray[j++]=0x0624;
			break;
		case 'Å'://ARABIC LETTER ALEF WITH HAMZA BELOW
			wCharArray[j++]=0x0625;
			break;
		case 'Æ'://ARABIC LETTER YEH WITH HAMZA ABOVE
			wCharArray[j++]=0x0626;
			break;
		case 'Ç'://ARABIC LETTER ALEF
			wCharArray[j++]=0x0627;
			break;
		case 'È'://ARABIC LETTER BEH
			wCharArray[j++]=0x0628;
			break;
		case 'É'://ARABIC LETTER TEH MARBUTA
			wCharArray[j++]=0x0629;
			break;
		case 'Ê'://ARABIC LETTER TEH
			wCharArray[j++]=0x062A;
			break;
		case 'Ë'://ARABIC LETTER THEH
			wCharArray[j++]=0x062B;
			break;
		case 'Ì'://ARABIC LETTER JEEM
			wCharArray[j++]=0x062C;
			break;
		case 'Í'://ARABIC LETTER HAH
			wCharArray[j++]=0x062D;
			break;
		case 'Î'://ARABIC LETTER KHAH
			wCharArray[j++]=0x062E;
			break;
		case 'Ï'://ARABIC LETTER DAL
			wCharArray[j++]=0x062F;
			break;
		case 'Ð'://ARABIC LETTER THAL
			wCharArray[j++]=0x0630;
			break;
		case 'Ñ'://ARABIC LETTER REH
			wCharArray[j++]=0x0631;
			break;
		case 'Ò'://ARABIC LETTER ZAIN
			wCharArray[j++]=0x0632;
			break;
		case 'Ó'://ARABIC LETTER SEEN
			wCharArray[j++]=0x0633;
			break;
		case 'Ô'://ARABIC LETTER SHEEN
			wCharArray[j++]=0x0634;
			break;
		case 'Õ'://ARABIC LETTER SAD
			wCharArray[j++]=0x0635;
			break;
		case 'Ö'://ARABIC LETTER DAD
			wCharArray[j++]=0x0636;
			break;
		case '×'://MULTIPLICATION SIGN
			wCharArray[j++]=0x00D7;
			break;
		case 'Ø'://ARABIC LETTER TAH
			wCharArray[j++]=0x0637;
			break;
		case 'Ù'://ARABIC LETTER ZAH
			wCharArray[j++]=0x0638;
			break;
		case 'Ú'://ARABIC LETTER AIN
			wCharArray[j++]=0x0639;
			break;
		case 'Û'://ARABIC LETTER GHAIN
			wCharArray[j++]=0x063A;
			break;
		case 'Ü'://ARABIC TATWEEL
			wCharArray[j++]=0x0640;
			break;
		case 'Ý'://ARABIC LETTER FEH
			wCharArray[j++]=0x0641;
			break;
		case 'Þ'://ARABIC LETTER QAF
			wCharArray[j++]=0x0642;
			break;
		case 'ß'://ARABIC LETTER KAF
			wCharArray[j++]=0x0643;
			break;
		case 'á'://ARABIC LETTER LAM
			wCharArray[j++]=0x0644;
			break;
		case 'ã'://ARABIC LETTER MEEM
			wCharArray[j++]=0x0645;
			break;
		case 'ä'://ARABIC LETTER NOON
			wCharArray[j++]=0x0646;
			break;
		case 'å'://ARABIC LETTER HEH
			wCharArray[j++]=0x0647;
			break;
		case 'æ'://ARABIC LETTER WAW
			wCharArray[j++]=0x0648;
			break;
		case ''://ARABIC LETTER PEH
			wCharArray[j++]=0x067E;
			break;
		case 'Š'://ARABIC LETTER TTEH
			wCharArray[j++]=0x0679;
			break;
		case ''://ARABIC LETTER TCHEH
			wCharArray[j++]=0x0686;
			break;
		case 'Ž'://ARABIC LETTER JEH
			wCharArray[j++]=0x0698;
			break;
		case ''://ARABIC LETTER GAF
			wCharArray[j++]=0x06AF;
			break;
		case '˜'://ARABIC LETTER KEHEH
			wCharArray[j++]=0x06A9;
			break;
		case 'í'://ARABIC LETTER YEH
			wCharArray[j++]=0x064A;
			break;
		case '¡'://ARABIC COMMA
			wCharArray[j++]=0x060C;
			break;
		case '0'://DIGIT ZERO
			wCharArray[j++]=0x0030;
			break;
		case '1'://DIGIT ONE
			wCharArray[j++]=0x0031;
			break;
		case '2'://DIGIT TWO
			wCharArray[j++]=0x0032;
			break;
		case '3'://DIGIT THREE
			wCharArray[j++]=0x0033;
			break;
		case '4'://DIGIT FOUR
			wCharArray[j++]=0x0034;
			break;
		case '5'://DIGIT FIVE
			wCharArray[j++]=0x0035;
			break;
		case '6'://DIGIT SIX
			wCharArray[j++]=0x0036;
			break;
		case '7'://DIGIT SEVEN
			wCharArray[j++]=0x0037;
			break;
		case '8'://DIGIT EIGHT
			wCharArray[j++]=0x0038;
			break;
		case '9'://DIGIT NINE
			wCharArray[j++]=0x0039;
			break;
		default://SPACE
			wCharArray[j++]=0x0020;
		}
	}
		wCharArray[j]=0;
}



int g_days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int j_days_in_month[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};


void gregorian_to_jalali(
	int *j_y,
	int *j_m,
	int *j_d,
	const int g_y,
	const int g_m,
	const int g_d)
{
   int gy, gm, gd;
   int jy, jm, jd;
   long g_day_no, j_day_no;
   int j_np;
 
   int i;
   gy = g_y-1600;
   gm = g_m-1;
   gd = g_d-1;
 
   g_day_no = 365*gy+(gy+3)/4-(gy+99)/100+(gy+399)/400;
   for (i=0;i<gm;++i)
      g_day_no += g_days_in_month[i];
   if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
      /* leap and after Feb */
      ++g_day_no;
   g_day_no += gd;
 
   j_day_no = g_day_no-79;
 
   j_np = j_day_no / 12053;
   j_day_no %= 12053;
 
   jy = 979+33*j_np+4*(j_day_no/1461);
   j_day_no %= 1461;
 
   if (j_day_no >= 366) {
      jy += (j_day_no-1)/365;
      j_day_no = (j_day_no-1)%365;
   }
 
   for (i = 0; j_day_no >= j_days_in_month[i]; ++i) {
      j_day_no -= j_days_in_month[i];
   }
   jm = i+1;
   jd = j_day_no+1;
   *j_y = jy;
   *j_m = jm;
   *j_d = jd;
}
