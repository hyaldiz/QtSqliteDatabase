#include "sqlitereader.hpp"

#include <QSqlQuery>
#include <QDebug>

SQLiteReader::SQLiteReader(SQLiteDataBase& _db)
    :db(_db)
{
}

QVariantList SQLiteReader::readAll(int primaryKey)
{
    QSqlQuery readAllQuery(db);
    QString readdAllCmd = SQLiteDataBase::scmdSelect + " " + SQLiteDataBase::scmdAll + " " +SQLiteDataBase::scmdFrom + " " +
            db.tableName() + " " + SQLiteDataBase::scmdWhere + " " + db.primaryKeyName() + "='" + QString::number(primaryKey) + "'";
    if(!readAllQuery.exec(readdAllCmd))  db.sqlError(readAllQuery.lastError(),"readAll exec");

    QVariantList frame;
    while (readAllQuery.next())
    {
        qsizetype index = 0;
        while(index  < db.bindingList().size())
        {
            frame.append(readAllQuery.value(index));
            index++;
        }
    }
    return frame;
}
