#ifndef SQLITEDATAUPDATEDER_H
#define SQLITEDATAUPDATEDER_H

#include "sqlitedatabase.h"
#include <QVariantList>

class SQLiteDataUpdateder
{
public:
    SQLiteDataUpdateder(SQLiteDataBase& _db);

    void updateFrame(int primaryKey,QVariantList frame);
    void updateData(const QString& parameter,int primaryKey,QVariant data);

private:
    SQLiteDataBase& db;
};

#endif // SQLITEDATAUPDATEDER_H
