#include "sqlitequerydata.hpp"

#include <QSqlQuery>
#include <QDebug>

SQLiteQueryData::SQLiteQueryData(SQLiteDataBase& _db)
    :db(_db)
{

}

QVariant SQLiteQueryData::queryData(const QString &parameter, QVariant primaryKey)
{
    QString valueStr = "";

    if(SQLiteDataBase::isInteger(primaryKey))
        valueStr = QString::number(primaryKey.toInt());
    else
        valueStr = primaryKey.toString();

    QSqlQuery dataQuery(db);
    QString queryDataCmd =
        SQLiteDataBase::scmdSelect                          + " " +
        SQLiteDataBase::removeSpecialCharacters(parameter)  + " " +
        SQLiteDataBase::scmdFrom                            + " " +
        db.tableName()                                      + " " +
        SQLiteDataBase::scmdWhere                           + " " +
        db.primaryKeyName()                                 + "='" +
        valueStr                                            + "'";

    if(!dataQuery.exec(queryDataCmd))
        db.sqlError(dataQuery.lastError(),"queryData exec");

    while(dataQuery.next())
        return dataQuery.value(0);

    return QVariant();
}
