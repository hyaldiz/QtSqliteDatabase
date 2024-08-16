#ifndef SQLITEREADER_H
#define SQLITEREADER_H

#include "sqlitedatabase.hpp"
#include <QVariantList>

class SQLiteReader
{
public:
    SQLiteReader(SQLiteDataBase& _db);

    QVariantList readAll(QVariant primaryKey);

private:
    SQLiteDataBase& db;
};

#endif // SQLITEREADER_H
