#include <Windows.h>

int hiredis_win_init()
{
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data);
}

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
int gettimeofday(struct timeval *tv, const char *tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
 
	if (NULL != tv)
	{
		GetSystemTimeAsFileTime(&ft);
 
		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;
 
		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS; 
		tmpres /= 10;  /*convert into microseconds*/
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}
 
	return 0;
}
