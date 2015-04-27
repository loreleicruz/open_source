#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdio.h>

/* this is encase any of the mysql related functions fail 
there must be an easy way to close them */
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

char* receiveInput( char *s ){
    scanf("%99s",s);
    return s;
}

long int returnepoch(char * timestamp ){
struct tm tm;
time_t epoch;
if ( strptime(timestamp, "%Y-%m-%d %H:%M:%S", &tm) != NULL )
  {epoch = mktime(&tm);}
else{printf("bad shit");}
return epoch;
}

int main(int argc, char **argv)
{      
  char str[100];
  MYSQL *con = mysql_init(NULL);
  
  //check is mysql is there
  if (con == NULL)
  {
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }    

  //connect to mysql using credentials put in

  //input info for database stuff
  if (mysql_real_connect(con,"localhost","root","toor","process_control",0,NULL,0)==NULL)
  {
    finish_with_error(con);
  }    
  
  if (mysql_query(con, "SELECT timestamp FROM mixer_temp")) 
  {
    finish_with_error(con);
  }
  MYSQL_RES *result = mysql_store_result(con);

  if (mysql_query(con, "SELECT temperature FROM mixer_temp")) 
  {
    finish_with_error(con);
  }
  MYSQL_RES *result2 = mysql_store_result(con);

  if (result == NULL || result2 == NULL) 
  {
    finish_with_error(con);
  }


  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  MYSQL_ROW row2;

  printf("\n Enter the filename :");
  FILE *fp;
  char *filename = receiveInput(str);
  filename=strcat(filename,".csv");
  long int epoch1;

fp=fopen(filename,"w+");
 int j=0;
  while ((row = mysql_fetch_row(result))&&(row2 = mysql_fetch_row(result2))) 
  { 
    
    for(int i = 0; i < num_fields; i++) 
    { 
      epoch1= returnepoch(row[i]);
      printf("%ld,%ld,%s \n",epoch1 % 10000,epoch1,row2[i] ? row2[i] : "NULL");
      fprintf(fp,"%ld,%ld,%s \n",epoch1 % 10000,epoch1,row2[i] ? row2[i] : "NULL");
    }  
    j++;
  }
   fclose(fp);
  mysql_free_result(result);
  mysql_close(con);
  
  exit(0);
}