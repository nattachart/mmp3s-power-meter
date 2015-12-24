#include <modbus.h> //libmodbus library

#ifndef __MBMAN__
#define __MBMAN__

class ModBusManager
{
	private:
		modbus_t *mb;

	public:
		~ModBusManager();
		//See modbus_new_rtu manual for values of the parameters
		int connectRTU(const int slaveID, const char *port, const int baud, const char parity, const int dataBit, int stopBit);
		void disconnect();
		void readRegisters(int slaveID, int addr, int nb, uint16_t *dest);
};
#endif
