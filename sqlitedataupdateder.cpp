#include "sqlitedataupdateder.hpp"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SQLiteDataUpdateder::SQLiteDataUpdateder(SQLiteDataBase& _db)
    :db(_db)
{
}

void SQLiteDataUpdateder::updateFrame(int primaryKey, QVariantList frame)
{
    QSqlQuery updateQuery(db);
    QString update = SQLiteDataBase::scmdUpdate + " " + db.tableName() + " " + SQLiteDataBase::scmdSet + " ";

    qsizetype index = 0;
    foreach(auto element,db.bindingList())
    {
        auto value = element;
        value = value.remove(":");

        qDebug() << value;

        switch (static_cast<int>(frame.at(index).type()))
        {
        case QVariant::Type::Int:
            update += value + "='" + QString::number(frame.at(index).toInt()) + "'";
            break;
        case QVariant::Type::Double:
            update += value + "='" + QString::number(frame.at(index).toDouble()) + "'";
            break;
        case QVariant::Type::String:
            update += value + "='" + frame.at(index).toString() + "'";
            break;
        case QVariant::Type::Bool:
            update += value + "='" + QString::number(frame.at(index).toBool()) + "'";
            break;
        }
        qDebug() << update;

        if(element != db.bindingList().last())
            update += ",";
        index++;
    }
    update +=  " " + SQLiteDataBase::scmdWhere + " " + db.primaryKeyName() + "=" + QString::number(primaryKey) + """";

    if(!updateQuery.prepare(update))    db.sqlError(updateQuery.lastError(),"updateFrame prepare");
    if(!updateQuery.exec())             db.sqlError(updateQuery.lastError(),"updateFrame exec");
}

void SQLiteDataUpdateder::updateData(const QString& parameter,int primaryKey, QVariant data)
{
    QSqlQuery updateDataQuery(db);
    QString updateDataCmd = SQLiteDataBase::scmdUpdate + " " + db.tableName() + " " + SQLiteDataBase::scmdSet + " " +parameter + "='" +
            "%1' " + SQLiteDataBase::scmdWhere + " " + db.primaryKeyName() + "=" + QString::number(primaryKey) + """";

    if(SQLiteDataBase::isInteger(data))
        updateDataCmd = updateDataCmd.arg(QString::number(data.toLongLong()));
    else if(data.type() == QVariant::Type::Double)
        updateDataCmd = updateDataCmd.arg(QString::number(data.toDouble()));
    else if(data.type() == QVariant::Type::String)
        updateDataCmd = updateDataCmd.arg(data.toString());

    if(!updateDataQuery.prepare(updateDataCmd))     db.sqlError(updateDataQuery.lastError(),"updateData prepare");
    if(!updateDataQuery.exec())                     db.sqlError(updateDataQuery.lastError(),"updateData exec");
}
