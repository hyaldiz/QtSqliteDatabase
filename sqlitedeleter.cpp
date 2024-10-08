#include "sqlitedeleter.hpp"

#include <QSqlQuery>

SQLiteDeleter::SQLiteDeleter(SQLiteDataBase& _db)
    :db(_db)
{
}

void SQLiteDeleter::deleteFrame(QVariant primaryKey)
{
    QString valueStr = SQLiteDataBase::isInteger(primaryKey)
        ? QString::number(primaryKey.toInt())
        : "'" + primaryKey.toString() + "'";

    QSqlQuery deleteQuery(db);
    QString deletecmd =
        SQLiteDataBase::scmdDelete  + " "+
        SQLiteDataBase::scmdFrom    + " " +
        db.tableName()              + " " +
        SQLiteDataBase::scmdWhere   + " " +
        db.primaryKeyName()         + "=" +
        valueStr                    + """";

    if(!deleteQuery.prepare(deletecmd))
        db.sqlError(deleteQuery.lastError(),"deleteFrame prepare");

    if(!deleteQuery.exec())
        db.sqlError(deleteQuery.lastError(),"deleteFrame exec");
}

void SQLiteDeleter::deleteAll()
{
    QSqlQuery deleteAllQuery(db);
    QString deleteAllcmd = SQLiteDataBase::scmdDelete + " " + SQLiteDataBase::scmdFrom + " " + db.tableName();

    if(!deleteAllQuery.prepare(deleteAllcmd))
        db.sqlError(deleteAllQuery.lastError(),"deleteAll prepare");

    if(!deleteAllQuery.exec())
        db.sqlError(deleteAllQuery.lastError(),"deleteAll exec");
}
