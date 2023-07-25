#ifndef SQLITEREADER_H
#define SQLITEREADER_H

#include "sqlitedatabase.hpp"
#include <QVariantList>

class SQLiteReader
{
public:
    SQLiteReader(SQLiteDataBase& _db);

    QVariantList readAll(int primaryKey);

private:
    SQLiteDataBase& db;
};

#endif // SQLITEREADER_H
