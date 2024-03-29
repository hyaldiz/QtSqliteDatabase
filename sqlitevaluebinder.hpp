#ifndef SQLITEVALUEBINDER_H
#define SQLITEVALUEBINDER_H

#include "sqlitedatabase.hpp"
#include <QSqlQuery>
#include <QDebug>

class SQLiteValueBinder
{
public:
    SQLiteValueBinder(SQLiteDataBase& _db) : db(_db) {};

    void bindValues(QVariantList frame)
    {
        QSqlQuery bindQuery(db);
        if(!bindQuery.prepare(db.values()))
            db.sqlError(bindQuery.lastError(),"SQLiteValueBinder prepare");
        for(int index = 0; index < frame.size(); index++)
            bindQuery.bindValue(index,frame.at(index));
        if(!bindQuery.exec())
            db.sqlError(bindQuery.lastError(),"SQLiteValueBinder exec");
    }

private:
    SQLiteDataBase& db;
};

#endif // SQLITEVALUEBINDER_H
