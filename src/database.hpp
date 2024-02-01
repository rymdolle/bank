#ifndef BANK_DATABASE_HPP
#define BANK_DATABASE_HPP

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
  std::string connect_string;

  Database()
  {
    connected_ = false;
    henv = nullptr;
    hdbc = nullptr;
  }

  static Database& getInstance()
  {
    static Database db;
    return db;
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
                           (SQLCHAR*) connect_string.c_str(),
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

  SQLHSTMT execQuery(std::string query)
  {
    SQLHSTMT hstmt = nullptr;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (!SQL_SUCCEEDED(ret)) {
      std::cerr << "Could not alloc handle.\n";
      return nullptr;
    }

    ret = SQLExecDirect(hstmt, (SQLCHAR*) query.c_str(), query.length());
    if (!SQL_SUCCEEDED(ret)) {
      std::cerr << "Could not execute direct.\n";
      SQLSMALLINT len = 0;
      SQLCHAR state[6], message[1024];
      SQLINTEGER native = 0;
      SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, 1, state, &native, message, 1024, &len);
      std::cerr << "ERROR *** " << state << ' ' << native << '\n';
      std::cerr << message << '\n';
      SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
      return nullptr;
    }
    return hstmt;
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
