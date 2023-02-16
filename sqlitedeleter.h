#ifndef SQLITEDELETER_H
#define SQLITEDELETER_H

#include "sqlitedatabase.h"

class SQLiteDeleter
{
public:
    SQLiteDeleter(SQLiteDataBase& _db);

    void deleteFrame(int primaryKey);
    void deleteAll();

private:
    SQLiteDataBase& db;
};

#endif // SQLITEDELETER_H
