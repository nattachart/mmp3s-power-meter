#include "ModBusManager.h"
#include <errno.h>
#include <stdio.h>

ModBusManager::~ModBusManager()
{
	this->disconnect();
}

int ModBusManager::connectRTU(const int slaveID, const char *port, const int baud, const char parity, const int dataBit, int stopBit)
{
	this->mb = modbus_new_rtu(port, baud, parity, dataBit, stopBit);
	//printf("slaveID: %d, port: %s, baud: %d, parity: %c, dataBit: %d, stopBit: %d\n", slaveID, port, baud, parity, dataBit, stopBit);
	if(this->mb == NULL)
	{
		fprintf(stderr, "Unable to create the libmodbus context.\n");
	}
	

	struct timeval response_timeout;
	response_timeout.tv_sec = 2;
	response_timeout.tv_usec = 0;
	modbus_set_response_timeout(this->mb, &response_timeout);
	
	modbus_set_slave(this->mb, slaveID);

	if(modbus_connect(this->mb) == -1){
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(this->mb);
		return -1;
	}
}

void ModBusManager::disconnect()
{
	if(this->mb != NULL)
	{
		modbus_close(this->mb);
		modbus_free(this->mb);
	}
}

int ModBusManager::readRegisters(int addr, int nb, uint16_t *dest)
{
	int rr = modbus_read_registers(this->mb, addr, nb, dest);
	if(rr == -1)
		fprintf(stderr, "Read Error: %s\n", modbus_strerror(errno));
	return rr;
}
