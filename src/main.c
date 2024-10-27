#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/db_func.h"

#define noOptions 4

char* options[noOptions] = {"1. Show all tasks", "2. Add task", "3. Delete task", "4. Exit"};

int main(void) {
    sqlite3* db = NULL;
    char* sql = NULL;

    int option = 0;
    char title[256];
    int deleteId = 0;

    int rc = 0;
    char* err_msg = NULL;

    rc = sqlite3_open("tasks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database access error: %s\n", sqlite3_errmsg(db));

        exit(DBE_ACCESS);
    }

    sql = "CREATE TABLE IF NOT EXISTS Tasks(Id INTEGER PRIMARY KEY, Title TEXT, Done INTEGER);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database create error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(DBE_CREATE);
    }

    printf(
        "*********************************************\n"
        "*                                           *\n"
        "*    Welcome to                             *\n"
        "*                                           *\n"
        "  #######  #####   ######   ##    ##  #####  \n"
        "     #    #     #  #        ##   ##  #       \n"
        "     #    #######  ######   #####   #        \n"
        "     #    #     #       #   ##  ##   #       \n"
        "     #    #     #  ######   ##   ##   #### # \n"
        "*                                           *\n"
        "*    Your C-based Task Management App!      *\n"
        "*                                           *\n"
        "*    Stay productive and manage tasks with  *\n"
        "*    simplicity and efficiency.             *\n"
        "*                                           *\n"
        "                                             \n");

    while (1) {
        do {
            for (int i = 0; i < noOptions; i++) {
                printf("%s\n", options[i]);
            }
            printf("Select an option: ");
            scanf("%d", &option);
        } while (option < 1 || option > noOptions);

        switch (option) {
            case 1:
                rc = retrive_tasks(db);

                if (rc != EXEC_OK) {
                    sqlite3_close(db);
                    exit(rc);
                }
                break;

            case 2:
                printf("Enter task title: ");
                scanf(" %[^\n]%*c", title);

                rc = insert_task(db, title);
                if (rc != EXEC_OK) {
                    sqlite3_close(db);
                    exit(rc);
                }
                break;

            case 3:
                rc = retrive_tasks(db);

                if (rc != EXEC_OK) {
                    sqlite3_close(db);
                    exit(rc);
                }
                printf("Enter the Id of the task you want to delete: ");
                scanf("%d", &deleteId);

                rc = delete_task(db, deleteId);
                if (rc != EXEC_OK) {
                    sqlite3_close(db);
                    exit(rc);
                }

                break;

            case 4:
                sqlite3_close(db);
                exit(EXIT_SUCCESS);

            default:
                break;
        }
    }
}
