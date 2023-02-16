#ifndef SQLITEPRIMARYKEYS_H
#define SQLITEPRIMARYKEYS_H

#include "sqlitedatabase.h"

class SQLitePrimaryKeys
{
public:
    SQLitePrimaryKeys(SQLiteDataBase& _db);

    bool isExist(int primaryKey)const;
    QVector<QVariant> existIDs()const;

private:
    SQLiteDataBase& db;
};

#endif // SQLITEPRIMARYKEYS_H
