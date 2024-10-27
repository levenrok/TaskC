#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define noOptions 4

char* options[noOptions] = {"1. Show all tasks", "2. Add task", "3. Delete task", "4. Exit"};
int rc = 0;
char* err_msg = NULL;

int retrive_tasks(sqlite3* db);
int print_task(void* arg, int argc, char** argv, char** arColName);
int insert_task(sqlite3* db, char* title);
int delete_task(sqlite3* db, int id);

enum ErrNo { EXEC_OK, DBE_ACCESS, DBE_CREATE, DBE_RETRIVE, DBE_INSERT, DBE_DELETE };

int main(void) {
    sqlite3* db = NULL;
    char* sql = NULL;

    int option = 0;
    char title[256];
    int deleteId = 0;

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
                exit(EXEC_OK);

            default:
                break;
        }
    }
}

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
