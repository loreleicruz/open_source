main2:main2.c
	gcc main2.c -I/usr/include/mysql -lmysqlclient -o main2 -lm -std=c99
	gcc populate.c -I/usr/include/mysql -lmysqlclient -o populate -lm