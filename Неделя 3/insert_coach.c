#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
int insert_coach(sqlite3 *db){
    sqlite3_stmt *res;
    int rc;
    char q[255];
    char* err;
    int id;
    char name[15];
    printf("Enter the coach name:\n");
    scanf("%s", name);
    sprintf(q, "SELECT COALESCE(MAX(ID)+1, 1) FROM coaches");
    rc = sqlite3_prepare_v2(db, q, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    rc = sqlite3_step(res);
    id = atoi((const char *)(sqlite3_column_text(res, 0)));
    char insertline[255];
    sprintf(insertline, "insert into coaches values(%d, '%s')", id, name);
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    rc = sqlite3_exec(db, insertline, 0, 0, &err);
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    if (rc)
    {
        printf("Error executing SQLite3 statement:%s\n", sqlite3_errmsg(db));
        sqlite3_free(err);
    }
    sqlite3_close(db);
    return 0;
}
