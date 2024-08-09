#ifndef SQLITEPRIMARYKEYS_H
#define SQLITEPRIMARYKEYS_H

#include "sqlitedatabase.hpp"

class SQLitePrimaryKeys
{
public:
    SQLitePrimaryKeys(SQLiteDataBase& _db);

    bool isExist(QVariant primaryKey)const;
    QVector<QVariant> existIDs()const;

private:
    SQLiteDataBase& db;
};

#endif // SQLITEPRIMARYKEYS_H
