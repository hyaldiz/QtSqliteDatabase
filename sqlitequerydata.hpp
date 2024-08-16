#ifndef SQLITEQUERYDATA_H
#define SQLITEQUERYDATA_H

#include <QVariant>
#include "sqlitedatabase.hpp"

class SQLiteQueryData
{
public:
    SQLiteQueryData(SQLiteDataBase& _db);

    QVariant queryData(const QString& parameter,QVariant primaryKey);

private:
    SQLiteDataBase& db;
};

#endif // SQLITEQUERYDATA_H
