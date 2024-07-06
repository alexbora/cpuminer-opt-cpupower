/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sql
 * @created     : Sâmbătă Mar 30, 2024 16:23:49 EET
 */

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

char *txt;
#ifdef __cplusplus
extern "C" {
static inline int print_cb(void *, int, char **restrict, char **restrict);
}
#endif

static inline int print_cb(void *NotUsed, int argc, char **argv,
                           char **azColName) {
  for (int i = 0; i < argc; i++)
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

  printf("\n");
  txt = calloc(1, 64);
  if (txt == NULL) {
    printf("%d - %s\n", __LINE__, __func__);
    return 1;
  }

  strncpy(txt, azColName[0], 64);

  char *txt2 = calloc(1, 64);
  while ((*txt2++ = *azColName[0]++))
    ;
  printf("txt2: %s\n", txt2);

  /* puts("while loop\n"); */
  /* while ((txt = *azColName++)) { */
  /*   printf("%s\n", txt); */
  /*   txt++; */
  /* } */
  /* puts("while loop\n"); */
  return 0;
}

void *main_x(void *arg) {
  sqlite3 *db = NULL;
  char *err_msg = 0;
  int rc = sqlite3_open("sales.db", &db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }

  char *sql =
      "CREATE TABLE Sales("
      "Id INT PRIMARY KEY NOT NULL,"
      "Name TEXT NOT NULL,"
      "Price INT NOT NULL);";

  sqlite3_exec(db, sql, 0, 0, &err_msg);

  sql =
      "INSERT INTO Sales VALUES(1, 'Alex', 100);"
      "INSERT INTO Sales VALUES(2, 'Bora', 200);"
      "INSERT INTO Sales VALUES(3, 'Alex Bora', 300);";

  sqlite3_exec(db, sql, 0, 0, &err_msg);

  sql = "SELECT * FROM Sales;";

  sqlite3_exec(db, sql, print_cb, 0, &err_msg);

  sql =
      "CREATE TABLE CUSTOMERS("
      "ID INT PRIMARY KEY     NOT NULL,"
      "FIRST_NAME           CHAR(50)    NOT NULL,"
      "LAST_NAME           CHAR(50)    NOT NULL,"
      "EMAIL        CHAR(50) UNIQUE,"
      "SIZE         REAL );";

  sqlite3_exec(db, sql, 0, 0, &err_msg);
  sql =
      "INSERT INTO CUSTOMERS (ID,FIRST_NAME,LAST_NAME,EMAIL,SIZE) VALUES (1, "
      "'Alex', 'Bora', '10', 100);";

  sqlite3_exec(db, sql, 0, 0, &err_msg);

  sql = "SELECT * FROM CUSTOMERS;";
  sqlite3_exec(db, sql, print_cb, 0, &err_msg);

  sql = "SELECT * FROM CUSTOMERS WHERE ID = 1;";
  sqlite3_exec(db, sql, print_cb, 0, &err_msg);

  sql =
      "INSERT INTO CUSTOMERS (ID,FIRST_NAME,LAST_NAME,EMAIL,SIZE) VALUES (2, "
      "'Bogdan', 'Bora','email', 111);";

  sqlite3_exec(db, sql, print_cb, 0, &err_msg);

  sqlite3 *db2 = NULL;
  sqlite3_open("sales2.db", &db2);

  sql =
      "CREATE TABLE IF NOT EXISTS SALES_MID_YEAR("
      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
      "CUSTOMER           CHAR(64)    NOT NULL,"
      "COUNT         REAL );";

  sqlite3_exec(db2, sql, 0, 0, &err_msg);
  sql = "INSERT INTO SALES_MID_YEAR (CUSTOMER,COUNT) VALUES ('Alex', 100);";

  sqlite3_exec(db2, sql, 0, 0, &err_msg);
  printf("result insertion: %s\n", err_msg);
  sql = "INSERT INTO SALES_MID_YEAR (CUSTOMER,COUNT) VALUES ('Bogdan', 100);";
  sqlite3_exec(db2, sql, 0, 0, &err_msg);

  printf("result insertion : %s\n", err_msg);

  sql = "INSERT INTO SALES_MID_YEAR (CUSTOMER,COUNT) VALUES ('Bogdan', 100);";
  sqlite3_exec(db2, sql, 0, 0, &err_msg);

  sql = "INSERT INTO SALES_MID_YEAR (CUSTOMER,COUNT) VALUES ('Bogdan', 100);";
  sqlite3_exec(db2, sql, 0, 0, &err_msg);

  sql = "INSERT INTO SALES_MID_YEAR (CUSTOMER,COUNT) VALUES ('Bogdan', 300);";
  sqlite3_exec(db2, sql, 0, 0, &err_msg);

  puts("Total sales mid year:\n");
  sql = "SELECT SUM(COUNT) FROM SALES_MID_YEAR;";
  sqlite3_exec(db2, sql, print_cb, 0, &err_msg);

  // delete all records from SALES_MID_YEAR
  sql = "DELETE FROM SALES_MID_YEAR;";
  sqlite3_exec(db2, sql, 0, 0, &err_msg);

  printf("result deletion: %s\n", err_msg);
  sql = NULL;
  err_msg = NULL;
  sqlite3_free(err_msg);
  sqlite3_free(sql);
  free(txt);
  sqlite3_close(db2);
  sqlite3_close(db);

  return NULL;
}

typedef int (*CREATE)(void *);
typedef int (*DESTROY)(void *);
typedef int (*UPDATE)(void *);
typedef int (*READ)(void *);
typedef int (*PRINT)(void *);
typedef int (*FIND)(void *);
typedef int (*FINDALL)(void *);
typedef int (*FINDONE)(void *);
typedef int (*FINDMANY)(void *);

typedef void *Data;

int f1(void *arg) {
  printf("f1\n");
  return 0;
}

int f2(Data arg) {
  printf("f2\n");
  return 0;
}

int main(int argc, char *argv[]) {
  main_x(NULL);
  CREATE f = f1;
  f(NULL);
  CREATE f3 = f2;
  f3(NULL);
  return 0;
}
