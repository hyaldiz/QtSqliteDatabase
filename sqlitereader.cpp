#include "sqlitereader.hpp"

#include <QSqlQuery>
#include <QDebug>

SQLiteReader::SQLiteReader(SQLiteDataBase& _db)
    :db(_db)
{
}

QVariantList SQLiteReader::readAll(QVariant primaryKey)
{

    QString valueStr = "";

    if(SQLiteDataBase::isInteger(primaryKey))
        valueStr = QString::number(primaryKey.toInt());
    else
        valueStr = primaryKey.toString();

    QSqlQuery readAllQuery(db);
    QString readdAllCmd =
        SQLiteDataBase::scmdSelect  + " "  +
        SQLiteDataBase::scmdAll     + " "  +
        SQLiteDataBase::scmdFrom    + " "  +
        db.tableName()              + " "  +
        SQLiteDataBase::scmdWhere   + " "  +
        db.primaryKeyName()         + "='" +
        valueStr                    + "'";

    if(!readAllQuery.exec(readdAllCmd))
        db.sqlError(readAllQuery.lastError(),"readAll exec");

    QVariantList frame;

    while (readAllQuery.next()) {
        qsizetype index = 0;
        while(index  < db.bindingList().size()) {
            frame.append(readAllQuery.value(index));
            index++;
        }
    }

    return frame;
}
