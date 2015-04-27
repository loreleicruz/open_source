#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
#include <time.h>
#include <unistd.h>

void put_temperature(MYSQL * con,double temperature)
{
	char SQLString[100];
	sprintf(SQLString,"INSERT INTO mixer_temp VALUES (NOW(),%f)",temperature);
	printf("%s\n",SQLString);
	if(mysql_query(con,SQLString))
	{
		printf("%s\n",mysql_error(con));
	}
}

void deletefromdb(MYSQL * con)
{
	char SQLString[100];
	sprintf(SQLString,"DELETE FROM mixer_temp");
	printf("%s\n",SQLString);
	if(mysql_query(con,SQLString))
	{
		printf("%s\n",mysql_error(con));
	}	

}
int main()
{
	int i,j;
	MYSQL *con=mysql_init(NULL);
	if (con==NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(1);
		
	}
	if (mysql_real_connect(con,"localhost","root","toor","process_control",0,NULL,0)==NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(con));
		exit(2);
	}

	char type;
	//wanted to give the choice of two 
	//an unmodified populate.c and a revised version for better results
	//hence the sitch case
	printf("\nWhat type of populate do you want?");
	printf("\nModified input  (A)");
	printf("\nUnModified input  (literally anything else)\n");

	scanf(" %c", &type);
	printf("input type %c \n",type);

	switch(type)
	{
		case 'A' :
		deletefromdb(con);
		for (i=0;i<100;i++)
		{
			printf("input entry: %d ",i+1);
			sleep(1);
			put_temperature(con,sin(2.0*3.141592 * (double)i/100.0));
			
		}
		mysql_close(con);
		exit(0);    
		break;

		default :
		deletefromdb(con);
		for (i=0;i<100;i++)
		{
			put_temperature(con,sin(2.0*3.141592 * (double)i/100.0));
		}
		mysql_close(con);
		exit(0);
	}
}