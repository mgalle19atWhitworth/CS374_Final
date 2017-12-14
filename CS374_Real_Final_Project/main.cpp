#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


// Calls all query executions
const int MAX_DATA=500;
void query(float maxPrice);
string GetQuery();
string GetQuery2();
string GetQuery3();
string GetQuery4();
string GetQuery5();
string GetQuery6();
string GetQuery7();
string GetQuery8();



int main() {
	query(20.5);

	return 0;
}

void query(float maxPrice) {
	int x = 1;
	while (x != 0) {
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
	
		// Displays the menu where user can choose from
		cout << "Please select an Option : \n";
		cout << "1) Display all information about the food in the fridge.\n";
		cout << "2) Display all food that will expire today.\n";
		cout << "3) Display all food that are GMO.\n";
		cout << "4) Display all the items in the freezer compartment.\n";
		cout << "5) Display all items that are gluten-free.\n";
		cout << "6) Display all items that contain nuts.\n";
		cout << "7) Display all the location where soda can be bought.\n";
		cout << "8) Display the shoping list.\n";
		cout << "0) Quit.";
		cout << endl;

		cin >> x;
		if (x == 0) // Assigns 0 as an arbitrary switch that exists program
			break;
		// creates a switch case for selection menu
		switch (x) {
		case 1: stSQL = GetQuery();
			cout << setw(25) << "Name" << setw(25) << "Type" << setw(25) << "Group" << endl;
			break;
		case 2: stSQL = GetQuery2();
			cout << setw(25) << "Name" << setw(25) << "Brand" << endl;
			break;
		case 3: stSQL = GetQuery3();
			cout << setw(25) << "Name" << setw(25) << "Quality" << endl;
			break;
		case 4: stSQL = GetQuery4();
			cout << setw(50) << "Name" << endl;
			break;
		case 5: stSQL = GetQuery5();
			cout << setw(50) << "Name" << endl;
			break;
		case 6: stSQL = GetQuery6();
			cout << setw(50) << "Name" << endl;
			break;
		case 7: stSQL = GetQuery7();
			cout << setw(25) << "Name" << setw(25) << "Address" << setw(25) << "Aisle" << endl;
			break;
		case 8: stSQL = GetQuery8();
			cout << setw(25) << "Name" << setw(25) << "Expire Date" << setw(25) << "Quantity" << endl;
			break;
		case 0: break;
		}


		// Connecting to the database
		string stConnect = "DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:\\Users\\mgalle19\\Documents\\GitHub\\CS374_Final\\Final_Project_DB.accdb;UID=Admin;PWD=;";

		rc = SQLDriverConnect(hdbc, NULL, (SQLCHAR *)stConnect.c_str(), stConnect.length(), szConnectOut, 1024, &cchConnect, SQL_DRIVER_NOPROMPT);
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
		//cout << stSQL << endl;
		rc = SQLExecDirect(hstmt, (SQLCHAR*)stSQL.c_str(), SQL_NTS);
		if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
		{
			SQLTCHAR state[255], error[255];
			SQLINTEGER code;
			SQLSMALLINT cb;
			SQLError(henv, hdbc, hstmt, state, &code, error, 255, &cb);
			cout << error << endl;
			exit(0);
		}

			
		// Sets the weight indents so the outcomes look more organized
		while (rc == SQL_SUCCESS) {
			rc = SQLFetch(hstmt);
			// If query 1 or 8 :: Display the set weight of 25
			if (x == 1 || x == 8) {
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << setw(25);
				cout << szData;
				if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << setw(25);
				cout << szData;
				if (SQLGetData(hstmt, 3, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << setw(25);
				 cout << szData;
			} // If query 2 or 3 :: Display the set weight of 25
			else if (x == 2 || x == 3) {
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << setw(25);
				cout << szData;
				if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS) {
					cout << setw(25);
					cout << szData;
				}
			} // If query 4, 5, or 6 :: Display the set weight of 50
			else if (x == 4 || x == 5 || x == 6) {
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS) {
					cout << setw(50);
					cout << szData;
				}
			}
			// If query 7 :: Display the set weight differs depending on the data size
			else if (x == 7) {
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << setw(25);
				cout << szData;
				if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << setw(40);
				cout << szData;
				if (SQLGetData(hstmt, 3, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << setw(10);
				cout << szData;
			}
			
			cout << endl;
		}

		SQLFreeStmt(hstmt, SQL_DROP);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
	}
}

// Displays all items in the fridge
string GetQuery() {
	string stSQL = "SELECT O.FoodName, O.FoodType, O.FoodGroup ";
	stSQL += "FROM Fridge R, Food O ";
	stSQL += "WHERE O.ID = R.FoodID";
	return stSQL;
}

// Displays all items that will expire before 12/14/2017
string GetQuery2() {
	string stSQl = "Select O.FoodName, R.TypeBrand ";
	stSQl += "From Fridge R, Food O ";
	stSQl += "Where ExpireDate = #12/14/17# AND O.ID = R.FoodID";
	return stSQl;
}

// Displays all items that are GMO
string GetQuery3() {
	string stSQL = "SELECT O.FoodName, R.Quality ";
	stSQL += "From Fridge R, Food O ";
	stSQL += "WHERE R.Quality = \'GMO\' AND O.ID = R.FoodID";
	return stSQL;
}

// Displays all items in freezer
string GetQuery4() {
	string stSQL = "SELECT O.FoodName ";
	stSQL += "FROM Fridge R, Food O ";
	stSQL += "WHERE Compartment = \'Freezer\' AND O.ID = R.FoodID";
	return stSQL;
}

// Displays all items that are gluten-free
string GetQuery5() {
	string stSQL = "SELECT FoodName ";
	stSQL += "FROM Food O ";
	stSQL += "WHERE Allergy = \'Gluten-Free\'";
	return stSQL;
}

// Displays all items that contain nuts
string GetQuery6() {
	string stSQL = "SELECT FoodName ";
	stSQL += "FROM Food O ";
	stSQL += "WHERE Allergy = \'Nuts\' ";
	return stSQL;
}

// Displays all location in which soda can be found
string GetQuery7() {
	string stSQL = "SELECT L.Name, L.Address,L.Aisle ";
	stSQL += "FROM Location L, Food O ";
	stSQL += "WHERE O.ID = L.FoodID AND O.FoodName = \'Soda\'";
	return stSQL;
}

// Displays all items that expire before 12/20/17 or has a quantity less than 3 in the fridge into the grocery-shopping list.
string GetQuery8() {
	string stSQL = "Select O.FoodName, R.ExpireDate, R.Quantity ";
	stSQL += "From Food O, Fridge R ";
	stSQL += "Where (ExpireDate < #12/20/17# OR R.Quantity< 3)  AND O.ID = R.FoodID ";
	return stSQL;
}