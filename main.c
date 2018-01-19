#include <stdio.h>
#include <string.h>
#include <modbus/modbus.h>
#include "defineses.h"

float result_convert(uint16_t *raw_data);

int main(int argc, char **argv){

	modbus_t *ctx;

	ctx = modbus_new_rtu("/dev/ttyUSB0", 2400, 'N', 8, 1);
	if (ctx == NULL) {
	    fprintf(stderr, "Unable to create the libmodbus context\n");
	    return -1;
	}

	modbus_set_slave(ctx, 1);
	modbus_connect(ctx);
	uint16_t buff[20];

	int rc = modbus_read_input_registers(ctx, CURRENT, 0x02, buff);
	if (rc == -1) {
	    return -1;
	}

	float data;

	printf("Result: %.2f\n", result_convert(buff));

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
