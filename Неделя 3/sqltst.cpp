#define  _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include "sqlite3.h"
#include <stdio.h>
#include <ios>
#include <string>


using namespace std;

int insert_coach(sqlite3 *db){
	sqlite3_stmt    *res;
	int rc;
	char *error;
	char q[255];
	int id;
	string name;
	cout << "Enter the coach name:\n";
	cin >> name;
	cout << endl;
	sprintf(q,"SELECT COALESCE(MAX(ID)+1, 1) FROM coaches");
	rc = sqlite3_prepare_v2(db, q, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return -1;
	}
	rc = sqlite3_step(res);
	id = atoi(sqlite3_column_text(res, 0));
	char sqlInsert2[255];
	sprintf(sqlInsert2, "Insert into coaches values(%d, '%s')", id, name.c_str());
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	rc = sqlite3_exec(db, sqlInsert2, NULL, NULL, &error);
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	sqlite3_close(db);

	return 0;
}

int find_coach(sqlite3 *db, string name){
	sqlite3_stmt    *res;
	int rc;
	char *error;
	char q[255];
	int id;
	sprintf(q, "SELECT id FROM coaches where name = '%s'",name.c_str());
	rc = sqlite3_prepare_v2(db, q, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	rc = sqlite3_step(res);
	if (rc == SQLITE_DONE){
		cout << endl << "Wrong coach" << endl;
		return -1;
	}
	id = atoi((char *)sqlite3_column_text(res, 0));
	return id;
}

int insert_team(sqlite3 *db){
	sqlite3_stmt    *res;
	int rc;
	char *error;
	char q[255];
	int id;
	string team;
	string location;
	string coach;
	cout << endl << "Enter the name of the team: ";
	cin >> team;
	cout << endl << "Enter the location of the team: ";
	cin >> location;
	cout << endl<<"Enter coach: ";
	cin >> coach;
	cout << endl;
	int coach_id;
	coach_id = find_coach(db, coach.c_str());
	if (coach_id == -1){
		return -1;
	}
	sprintf(q, "SELECT COALESCE(MAX(ID)+1, 1) FROM teams");
	rc = sqlite3_prepare_v2(db, q, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	rc = sqlite3_step(res);
	id = atoi((char *)sqlite3_column_text(res, 0));
	char sqlInsert2[255];
	sprintf(sqlInsert2, "Insert into teams values(%d, '%s', '%s',%d)", id, team.c_str(), location.c_str(), coach_id);
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	rc = sqlite3_exec(db, sqlInsert2, NULL, NULL, &error);
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	sqlite3_close(db);
	return 0;
}

int disp_coach(sqlite3 *db){
	cout << endl;
	sqlite3_stmt    *res;
	int rc;
	char *error;
	const char *sqlSelect = "SELECT * FROM coaches;";
	char **results = NULL;
	int rows, columns;
	rc = sqlite3_open("chinook.db", &db);
	sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
		return -1;
	}
	else
	{
		cout << "Display table of coaches" << endl;
		for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				int cellPosition = (rowCtr * columns) + colCtr;
				cout.width(12);
				cout.setf(ios::left);
				cout << results[cellPosition] << " ";
			}
			cout << endl;
			if (0 == rowCtr)
			{
				for (int colCtr = 0; colCtr < columns; ++colCtr)
				{
					cout.width(12);
					cout.setf(ios::left);
					cout << "~~~~~~~~~~~~ ";
				}
				cout << endl;
			}
		}
	}
	sqlite3_free_table(results);
	cout << endl;
	return 0;
}

int disp_teams(sqlite3 *db){
	cout << endl;
	sqlite3_stmt    *res;
	int rc;
	char *error;
	const char *sqlSelect = "SELECT * FROM teams;";
	char **results = NULL;
	int rows, columns;
	rc = sqlite3_open("chinook.db", &db);
	sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
		return -1;
	}
	else
	{
		cout << "Display table of teams" << endl;
		for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				int cellPosition = (rowCtr * columns) + colCtr;
				cout.width(25);
				cout.setf(ios::left);
				cout << results[cellPosition] << " ";
			}
			cout << endl;
			if (0 == rowCtr)
			{
				for (int colCtr = 0; colCtr < columns; ++colCtr)
				{
					cout.width(25);
					cout.setf(ios::left);
					cout << "~~~~~~~~~~~~ ";
				}
				cout << endl;
			}
		}
	}
	sqlite3_free_table(results);
	cout << endl;
	return 0;
}
int main(int argc, char* argv[]){
	int rc;
	char *error;
	int choice;
	choice = 0;
	sqlite3 *db;
	rc = sqlite3_open("chinook.db", &db);
	if (rc)
	{
		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_close(db);
		return -1;
	}
	else
	{
		cout << endl;
	}
	while (choice != 5){
		cout << "Enter the number between 1 and 5:" << endl << "1) Insert a new coach" << endl << "2) Insert a new team" <<
			endl << "3) Display table of coaches" << endl << "4) Display table of teams" << endl << "5) Exit" << endl;
		cin >> choice;
		
		if (choice == 1){
			insert_coach(db);
		}
		else if (choice == 2){
			insert_team(db);
		}
		else if (choice == 3){
			disp_coach(db);
		}
		else if (choice == 4){
			disp_teams(db);
		}
		else if (choice != 5){
			cout << "Wrong number" << endl;
		}
	}
	sqlite3_close(db);
}
