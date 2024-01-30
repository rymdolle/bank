#ifndef BANK_DATABASE_HPP
#define BANK_DATABASE_HPP

#include "user.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#if defined (_WIN32)
#include <windows.h>
#else
#define GetDesktopWindow() nullptr
#endif

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

class Database
{
private:
  bool connected_;
  SQLHENV henv;
  SQLHDBC hdbc;
public:
  std::string driver;
  std::string host;
  std::string port;
  std::string database;
  std::string username;
  std::string password;

  Database()
  {
    connected_ = false;
    henv = nullptr;
    hdbc = nullptr;
  }

  bool disconnect()
  {
    if (isConnected()) {
      // Disconnect from db
      SQLDisconnect(hdbc);

      // Free the environment
      SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
      SQLFreeHandle(SQL_HANDLE_ENV, henv);

      connected_ = false;
    } else {
      std::cerr << "Not connected.\n";
    }
    return true;
  }

  bool connect()
  {
    if (isConnected()) {
      std::cerr << "Already connected.\n";
      return true;
    }
    SQLRETURN ret;
    //std::stringstream dsn;
    //dsn << "DRIVER="   << driver   << ';'
    //    << "SERVER="   << host     << ';'
    //    << "DATABASE=" << database << ';'
    //    << "USER="     << username << ';'
    //    << "PASSWORD=" << password << ';';

    // Initialize ODBC environment
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (!SQL_SUCCEEDED(ret)) {
      std::cerr << "Could not create handle.\n";
      return false;
    }

    // Set ODBC version to 3
    ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
                        (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (!SQL_SUCCEEDED(ret)) {
      std::cerr << "Could not set env.\n";
      return false;
    }

    // Initialize connection handle
    ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (!SQL_SUCCEEDED(ret)) {
      std::cerr << "Could not alloc handle.\n";
      return false;
    }

    // Connect to the MySQL server
    ret = SQLDriverConnect(hdbc,
                           GetDesktopWindow(),
                           (SQLCHAR*) "DSN=MariaDB-bank;",
                           SQL_NTS,
                           nullptr, 0, nullptr,
                           SQL_DRIVER_COMPLETE);
    if (!SQL_SUCCEEDED(ret)) {
      std::cerr << "Could not connect driver.\n";
      return false;
    }

    connected_ = true;
    return true;
  }

  bool isConnected()
  {
    return connected_;
  }

  std::vector<User> users()
  {
    std::vector<User> users;
    std::string query = "SELECT id, username, password FROM bank.users";
    SQLHSTMT hstmt = nullptr;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    SQLPrepare(hstmt, (SQLCHAR*) query.c_str(), SQL_NTS);
    SQLExecute(hstmt);

    SQLLEN count = 0;
    SQLRowCount(hstmt, &count);
    for (int i = 0; i < count; ++i) {
      SQLFetch(hstmt);

      int id = read_integer(hstmt, 1);
      std::string username = read_string(hstmt, 2);
      std::string password = read_string(hstmt, 3);

      users.emplace_back(username, password, id);
    }

    // Free statment
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return users;
  }

  static int read_integer(SQLHSTMT hstmt, int column)
  {
    int number{0};
    SQLGetData(hstmt, column, SQL_INTEGER, &number, sizeof(number), nullptr);
    return number;
  }

  static std::string read_string(SQLHSTMT hstmt, int column)
  {
    std::string text;
    SQLLEN size;
    SQLGetData(hstmt, column, SQL_C_CHAR, text.data(), 0, &size);
    text.resize(size);
    SQLGetData(hstmt, column, SQL_C_CHAR, text.data(), text.capacity(), &size);
    return text;
  }
};

#endif /* BANK_DATABASE_HPP */
