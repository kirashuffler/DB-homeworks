#include <stdio.h>
#include "insert_coach.c"
#include "sqlite3.h"
int main(){
    int rc;
    char *err;
    int choice = 0;
    sqlite3 *db;
    rc = sqlite3_open("test1.db", &db);
    if (rc)
    {
        printf("Error opening SQLite3 database:%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    insert_coach(db);
    return 0;
}
