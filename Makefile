all: readerprog producerprog

readerprog:./reader/reader.c
	gcc ./reader/reader.c -I/usr/include/mysql -lmysqlclient -o readerprog -lm -std=c99


producerprog:./producer/producer.c
	gcc ./producer/producer.c -I/usr/include/mysql -lmysqlclient -o producerprog -lm