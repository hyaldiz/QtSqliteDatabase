#include "sqlitequerydata.hpp"

#include <QSqlQuery>
#include <QDebug>

SQLiteQueryData::SQLiteQueryData(SQLiteDataBase& _db)
    :db(_db)
{

}

QVariant SQLiteQueryData::queryData(const QString &parameter, int primaryKey)
{
    QSqlQuery dataQuery(db);
    QString queryDataCmd = SQLiteDataBase::scmdSelect + " " + SQLiteDataBase::removeSpecialCharacters(parameter) + " " + SQLiteDataBase::scmdFrom + " " +
            db.tableName() + " " + SQLiteDataBase::scmdWhere + " " + db.primaryKeyName() + "='" + QString::number(primaryKey) + "'";

    if(!dataQuery.exec(queryDataCmd))   db.sqlError(dataQuery.lastError(),"queryData exec");
    while(dataQuery.next())
        return dataQuery.value(0);
    return QVariant();
}
