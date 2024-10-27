#include "include/db_func.h"

int rc = 0;
char* err_msg = NULL;

int retrive_tasks(sqlite3* db) {
    char* sql = "SELECT Id, Title FROM Tasks WHERE Done = False;";

    rc = sqlite3_exec(db, sql, print_task, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error retriving tasks: %s\n", err_msg);

        sqlite3_free(err_msg);
        return DBE_RETRIVE;
    }

    return EXEC_OK;
}

int print_task(void* arg, int argc, char** argv, char** arColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s\t", arColName[i]);
    }
    printf("\n");
    printf("__\t_____\n");
    for (int j = 0; j < argc; j++) {
        printf("%s\t", argv[j] ? argv[j] : NULL);
    }
    printf("\n");
    printf("\n");

    return EXEC_OK;
}

int insert_task(sqlite3* db, char* title) {
    char sql[256];
    sprintf(sql, "INSERT INTO Tasks(Title, Done) VALUES ('%s', FALSE);", title);

    rc = sqlite3_exec(db, sql, print_task, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error inserting task: %s\n", err_msg);

        sqlite3_free(err_msg);
        return DBE_INSERT;
    }

    return EXEC_OK;
}

int delete_task(sqlite3* db, int id) {
    char sql[256];
    sprintf(sql, "DELETE FROM Tasks WHERE Id=%d;", id);

    rc = sqlite3_exec(db, sql, print_task, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error deleting task: %s\n", err_msg);

        sqlite3_free(err_msg);
        return DBE_DELETE;
    }

    return EXEC_OK;
}
