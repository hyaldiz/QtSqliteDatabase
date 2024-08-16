#include "sqliteprimarykeys.hpp"

#include <QSqlQuery>
#include <QDebug>

SQLitePrimaryKeys::SQLitePrimaryKeys(SQLiteDataBase& _db)
    :db(_db)
{

}

bool SQLitePrimaryKeys::isExist(QVariant primaryKey)const
{
    QSqlQuery existIdQuery(db);
    QString valueStr = "";

    if(SQLiteDataBase::isInteger(primaryKey))
        valueStr = QString::number(primaryKey.toInt());
    else
        valueStr = "'" + primaryKey.toString() + "'";

    QString existIdCmd =
        SQLiteDataBase::scmdSelect  + " " +
        SQLiteDataBase::scmdAll     + " " +
        SQLiteDataBase::scmdFrom    + " " +
        db.tableName()              + " " +
        SQLiteDataBase::scmdWhere   + " " +
        SQLiteDataBase::scmdExists  + " " + "(" +
        SQLiteDataBase::scmdSelect  + " "  +
        SQLiteDataBase::scmdAll     + " " +
        SQLiteDataBase::scmdFrom    + " " +
        db.tableName()              + " " +
        SQLiteDataBase::scmdWhere   + " " +
        db.primaryKeyName()         + "=" +
        valueStr                    + ");";

    if(!existIdQuery.prepare(existIdCmd))
        db.sqlError(existIdQuery.lastError(),"isExist prepare");

    if(!existIdQuery.exec())
        db.sqlError(existIdQuery.lastError(),"isExist exec");

    while(existIdQuery.next()) {
        if(existIdQuery.value(0) == primaryKey)
            return true;
    }

    return false;
}

QVector<QVariant> SQLitePrimaryKeys::existIDs() const
{
    QSqlQuery existIdsQuery(db);
    QString existIdsCmd =
        SQLiteDataBase::scmdSelect      + " " +
        SQLiteDataBase::scmdAll         + " " +
        SQLiteDataBase::scmdFrom        + " " +
        db.tableName()                  + " " +
        SQLiteDataBase::scmdWhere       + " " +
        db.primaryKeyName()             + " " +
        SQLiteDataBase::scmdIsNotNull;

    if(!existIdsQuery.prepare(existIdsCmd))
        db.sqlError(existIdsQuery.lastError(),"existIDs prepare");

    if(!existIdsQuery.exec())
        db.sqlError(existIdsQuery.lastError(),"existIDs exec");

    QVector<QVariant> ids;

    while(existIdsQuery.next())
        ids.append(existIdsQuery.value(0));

    return ids;
}
