#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <modbus/modbus.h>
#include <unistd.h>
#include "defineses.h"
#include "/home/vmv/programming/mysql/mysql_cli.h"

float result_convert(uint16_t *raw_data);

int main(int argc, char **argv){

	pid_t pid;		//fork context
	uint16_t buff[10];	//buffer for temporary data
	float read_data[12]; 	//Array for store read data
	int i=0, tmp_result;		//Servise variable
	modbus_t *ctx;		//modbus context for work whith protocol

	DBDAT *db;
	db = (DBDAT *)malloc(sizeof(DBDAT));

	strcpy(db->user, "root");
	strcpy(db->passwd, "23272829");
	strcpy(db->server, "194.67.204.166");
        strcpy(db->name, "sensors");
	strcpy(db->table, "Counter");

	//Run programm like a daemon
	pid = fork();
	if(pid){
		return 0;
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
			modbus_read_input_registers(ctx, registers[i], 0x02, buff);
			sprintf(db->col[i].data, "%.2f",  result_convert(buff));
			strcpy(db->col[i].name, legend[i]);
			strcpy(db->col[i].type, "DECIMAL(5,2)");
		}
		db->tc_num = i;
		i = 0;
		add_to_db(db);
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
