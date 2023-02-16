#ifndef SQLITEQUERYDATA_H
#define SQLITEQUERYDATA_H

#include <QVariant>
#include "sqlitedatabase.h"

class SQLiteQueryData
{
public:
    SQLiteQueryData(SQLiteDataBase& _db);

    QVariant queryData(const QString& parameter,int primaryKey);

private:
    SQLiteDataBase& db;
};

#endif // SQLITEQUERYDATA_H
