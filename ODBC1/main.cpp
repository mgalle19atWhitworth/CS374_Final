#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
using namespace std;



const int MAX_DATA=100;
void listProducts(float maxPrice);
string GetQuery(char* szPrice);

int main() {
	listProducts(20.5);

	return 0;
}

void listProducts(float maxPrice) {
	RETCODE rc;
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	char szData[MAX_DATA];
	string stSQL;
	SQLLEN cbData;
	char szPrice[10];
	
	_gcvt_s(szPrice, 10, maxPrice, 6);

	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);

	SQLCHAR szConnectOut[1024];
	SQLSMALLINT cchConnect;


	string stConnect = "DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:\\Users\\mgalle19\\Documents\\GitHub\\CS374_Final\\Final_Project_DATABASE.accdb;UID=Admin;PWD=;";

	stSQL = GetQuery(szPrice);
	rc = SQLDriverConnect(hdbc, NULL, (SQLCHAR *) stConnect.c_str(), stConnect.length(), szConnectOut, 1024, &cchConnect, SQL_DRIVER_NOPROMPT);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, NULL, state, &code, error, 255, &cb);
		cout << error << endl;
		exit(0);
	}
	SQLAllocStmt(hdbc, &hstmt);
	cout << stSQL << endl;
	rc = SQLExecDirect(hstmt, (SQLCHAR*) stSQL.c_str(), SQL_NTS);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, hstmt, state, &code, error, 255, &cb);
		cout << error << endl;
		exit(0);
	}

	while (rc == SQL_SUCCESS) {
		rc = SQLFetch(hstmt);
		if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
			cout<< szData;
		if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
			cout << szData;
		cout << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}

string GetQuery(char* szFee) {
	string stSQL = "SELECT FoodName ";
	stSQL += "FROM Food ";
	stSQL += "WHERE FoodGroup = 'Fruit'";

	return stSQL;
}
