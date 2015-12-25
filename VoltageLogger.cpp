#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MMP3S.h"

FILE *of;
MMP3S *mmp3s;

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

	#include <windows.h>
	#include <ctype.h>
	inline void delay( unsigned long ms )
	{
		Sleep( ms );
	}
	BOOL WINAPI ctrlCHandler(DWORD signal)
	{
		if(signal == CTRL_C_EVENT)
		{
			fclose(of);
			delete mmp3s;
		}
		return TRUE;
	}

#else  /* presume POSIX */

	#include <unistd.h>
	#include <signal.h>
	inline void delay( unsigned long ms )
	{
		usleep( ms * 1000 );
	}
	void ctrlCHandler(int signal)
	{
		fclose(of);
		delete mmp3s;
	}
#endif 

int main(int argc, char* argv[])
{
	int slaveID = 1;
	char *port;
	char *outFile;
	int baud = 19200;
	int parity = P_NONE;
	time_t rawTime;
	struct tm *timeInfo;
	char outString[100];

	int16_t volt;
	char voltStr[7];
	int i, n;


	if(argc != 3)
	{
		printf("Usage:\n");
		printf("\t%s <device> <output file name>\n\n", argv[0]);
		printf("Example:\n");
		printf("On Linux:\n");
		printf("\t%s /dev/ttyUSB0 voltage-log.csv\n", argv[0]);
		printf("On Windows:\n");
		printf("\t%s COM1 voltage-log.csv\n\n", argv[0]);
		return -1;
	}

	printf("\nPress Ctrl-C to quit.\n");

	port = argv[1];
	outFile = argv[2];

	mmp3s = new MMP3S(slaveID, port, baud, parity);

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
	n = strlen(port);
	for(i=0; i<n; i++)
	{
		port[i] = toupper(port[i]);
	}
	SetConsoleCtrlHandler(ctrlCHandler, TRUE);
#else
	signal(SIGINT, ctrlCHandler);
#endif

	of = fopen(outFile, "a");

	int err = mmp3s->openConnection();
	
	while(1)
	{
		volt = mmp3s->readVoltage();
		sprintf(voltStr, "%d.%d", volt/10, volt%10);
		time(&rawTime);
		timeInfo = localtime(&rawTime);

		sprintf(outString, "%02d-%02d-%04d %02d:%02d:%02d, %s\n"
			, timeInfo->tm_mday, 1+timeInfo->tm_mon, 1900+timeInfo->tm_year
			, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, voltStr);

		//printf("%s", outString);
		if(volt != -1)
		{
			fprintf(of, "%s", outString);
			fflush(of);
		}
		delay(500);
	}
	printf("\n");

	delete mmp3s;
	fclose(of);

	return 0;
}
