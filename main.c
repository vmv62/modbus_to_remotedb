#include <stdio.h>
#include <string.h>
#include <modbus/modbus.h>
#include <unistd.h>
#include "defineses.h"

float result_convert(uint16_t *raw_data);

int main(int argc, char **argv){

	pid_t pid;		//fork context
	uint16_t buff[10];	//buffer for temporary data
	float read_data[12]; 	//Array for store read data
	int i=0;		//Servise variable
	modbus_t *ctx;		//modbus context for work whith protocol

	//Run programm like a daemon
	pid = fork();
	if(pid){
		return -1;
	}

	ctx = modbus_new_rtu("/dev/ttyUSB0", 2400, 'N', 8, 1);
	if (ctx == NULL) {
	    fprintf(stderr, "Unable to create the libmodbus context\n");
	    return -1;
	}

	modbus_set_slave(ctx, 1);
	modbus_connect(ctx);

	while(1){
		for(i; i < 13; i++){
			read_data[i] = modbus_read_input_registers(ctx, registers[i], 0x02, buff);
			printf("%20s: %10.2f\n", legend[i], result_convert(buff));
		}
	}
	modbus_free(ctx);
	return 0;
}


float result_convert(uint16_t *raw_data){
	float data;
	int tmp;

	tmp = ((raw_data[0]<<16) | raw_data[1]);
	memcpy(&data, &tmp, sizeof(data));
	return data;
}
