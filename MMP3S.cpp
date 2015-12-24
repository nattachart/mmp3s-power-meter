#include <stdio.h>
#include <string.h>
#include "MMP3S.h"

MMP3S::MMP3S(const int slaveID, const char *port, const int baud, const int parity)
{
	this->slaveID = slaveID;
	strcpy(this->port, port);
	this->baud = baud;
	switch(parity)
	{
		case P_ODD:
			this->parity = 'O';
			this->stopBit = 1;
			break;
		case P_EVEN:
			this->parity = 'E';
			this->stopBit = 1;
			break;
		default:
			this->parity = 'N';
			this->stopBit = 2;
			break;
	}
}
MMP3S::~MMP3S()
{
	this->closeConnection();
}
int MMP3S::openConnection()
{
	this->mp = new ModBusManager();
	this->mp->connectRTU(slaveID, port, baud, parity, DATA_BIT, stopBit);
}
void MMP3S::closeConnection()
{
	delete(this->mp);
}
int16_t MMP3S::readVoltage() //in Volts
{
	uint16_t volt;
	this->mp->readRegisters(slaveID, VOLT_ADDR, 1, &volt);
	printf("uint16_t: %d\n", volt);
	return (int16_t)volt;
}
int16_t MMP3S::readCurrent() //in Amperes
{return 0;}
int16_t MMP3S::readPower() //in Kilowatts
{return 0;}
int16_t MMP3S::readPowerFactor()
{return 0;}
int64_t MMP3S::readEnergy() //in Kilowatt-hours
{return 0;}
