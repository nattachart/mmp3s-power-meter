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
	int readRegs;
	readRegs = this->mp->readRegisters(VOLT_ADDR, 1, &volt);
	if(readRegs == -1)
		volt = -1;
	return (int16_t)volt;
}
int16_t MMP3S::readCurrent() //in Amperes
{
	uint16_t current;
	int readRegs;
	readRegs = this->mp->readRegisters(AMP_ADDR, 1, &current);
	if(readRegs == -1)
		current = -1;
	return (int16_t)current;
}
int16_t MMP3S::readPower() //in Kilowatts
{
	uint16_t power;
	int readRegs;
	readRegs = this->mp->readRegisters(KW_ADDR, 1, &power);
	if(readRegs == -1)
		power = -1;
	return (int16_t)power;
}
int16_t MMP3S::readPowerFactor()
{
	uint16_t pf;
	int readRegs;
	readRegs = this->mp->readRegisters(PF_ADDR, 1, &pf);
	if(readRegs == -1)
		pf = -1;
	return (int16_t)pf;
}
