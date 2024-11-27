#include "ntc.h"

unsigned int GetNTCTable_Temp(float Vout)
{
		unsigned int R1 = 10000;
		unsigned int res = (Vout * R1) / (4095 - Vout);
    unsigned int low=0,high=100,mid;
    unsigned int dat;
		const unsigned int NTC_Table[]={ 
					32814,31179,29636,28178,26800,25497,24263,23096,21992,20947,
					19958,19022,18135,17294,16498,15742,15025,14345,13699,13086,
					12504,11951,11426,10926,10452,10000,9570,9162,8773,8402,
					8049,7713,7393,7088,6797,6520,6255,6003,5762,5532,
					5313,5103,4903,4711,4529,4354,4187,4027,3874,3728,
					3588,3454,3326,3203,3086,2973,2865,2761,2662,2567,
					2476,2388,2304,2224,2146,2072,2001,1932,1866,1803,
					1742,1684,1628,1574,1522,1472,1424,1378,1333,1290,
					1249,1209,1171,1134,1099,1065,1032,1000,969,940,
					911,884,857,831,807,783,760,738,716,695,
					675
					};

    if(res>NTC_Table[low])            return 0;
    else if(res<NTC_Table[high])      return 1000;
    while(1)
    {
        mid = (high + low)/2;
        dat = NTC_Table[mid];
        if(res < dat)        low = mid;
        else if(res > dat)   high= mid;
        else               return mid * 10;
        if((high-low)<=1)  break;  //找到了最小的区间
    }
    dat = low*10 + (NTC_Table[low]-res)*10/(NTC_Table[low]-NTC_Table[high]);
    return dat;
}

