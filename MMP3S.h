#include "ModBusManager.h"

#ifndef __MMP3S__
#define __MMP3S__

#define P_NONE 0
#define P_ODD 1
#define P_EVEN 2

#define DATA_BIT 8

#define VOLT_ADDR 0x20
#define AMP_ADDR 0x21
#define KW_ADDR 0x22
#define PF_ADDR 0x23
#define HZ_ADDR 0x24
#define KWH_ADDR_HIGH_WORD 0x25
#define KWH_ADDR_LOW_WORD 0x26

class MMP3S
{
	private:
		ModBusManager *mp;
		char port[50];
		int baud;
		char parity;
		int stopBit;
		int slaveID;

	public:
		MMP3S(const int slaveID, const char *port, const int baud, const int parity);
		~MMP3S();
		int openConnection();
		void closeConnection();
		int16_t readVoltage(); //in Volts
		int16_t readCurrent(); //in Amperes
		int16_t readPower(); //in Kilowatts
		int16_t readPowerFactor();
		int64_t readEnergy(); //in Kilowatt-hours
};
#endif
