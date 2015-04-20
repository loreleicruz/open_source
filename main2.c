#include <my_global.h>
#include <mysql.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main(int argc, char **argv)
{      
  MYSQL *con = mysql_init(NULL);
  
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
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
  while ((row = mysql_fetch_row(result))&&(row = mysql_fetch_row(result2))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s,%s", row[i] ? row[i] : "NULL",row2[i] ? row2[i] : "NULL");
      } 
          printf("\n"); 
  }
  
  mysql_free_result(result);
  mysql_close(con);
  
  exit(0);
}