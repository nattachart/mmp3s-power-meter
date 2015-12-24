#include <stdio.h>
#include "MMP3S.h"

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

  #include <windows.h>

  inline void delay( unsigned long ms )
    {
    Sleep( ms );
    }

#else  /* presume POSIX */

  #include <unistd.h>

  inline void delay( unsigned long ms )
    {
    usleep( ms * 1000 );
    }

#endif 

int main()
{
	int slaveID = 1;
	const char *port = "/dev/ttyUSB0";
	int baud = 19200;
	int parity = P_NONE;

	int16_t volt;
	int i;

	MMP3S mmp3s(slaveID, port, baud, parity);
	int err = mmp3s.openConnection();
	
	printf("Open Connection: %d\n", err);
	for(i=0; i<20; i++)
	{
		volt = mmp3s.readVoltage();
		printf("Volt: %d\n", volt);
		delay(1000);
	}
	printf("\n");

	return 0;
}
