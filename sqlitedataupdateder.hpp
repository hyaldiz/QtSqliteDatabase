#ifndef SQLITEDATAUPDATEDER_H
#define SQLITEDATAUPDATEDER_H

#include "sqlitedatabase.hpp"
#include <QVariantList>

class SQLiteDataUpdateder
{
public:
    SQLiteDataUpdateder(SQLiteDataBase& _db);

    void updateFrame(QVariant primaryKey,QVariantList frame);
    void updateData(const QString& parameter,QVariant primaryKey,QVariant data);

private:
    SQLiteDataBase& db;
};

#endif // SQLITEDATAUPDATEDER_H
