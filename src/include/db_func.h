#ifndef __DB_FUNC__
#define __DB_FUNC__

#include <sqlite3.h>
#include <stdio.h>

enum DbErrNo { EXEC_OK, DBE_ACCESS, DBE_CREATE, DBE_RETRIVE, DBE_INSERT, DBE_DELETE };

int retrive_tasks(sqlite3* db);
int print_task(void* arg, int argc, char** argv, char** arColName);
int insert_task(sqlite3* db, char* title);
int delete_task(sqlite3* db, int id);

#endif  // __DB_FUNC__
