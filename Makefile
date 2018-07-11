main:
	gcc main.c -o mdbcounter -I/usr/include/mysql /home/vmv/programming/mysql/mysql_cli.c -lmodbus -lmysqlclient
