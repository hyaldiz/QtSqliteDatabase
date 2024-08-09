#include "sqlitedataupdateder.hpp"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SQLiteDataUpdateder::SQLiteDataUpdateder(SQLiteDataBase& _db)
    :db(_db)
{
}

void SQLiteDataUpdateder::updateFrame(QVariant primaryKey, QVariantList frame)
{
    QSqlQuery updateQuery(db);
    QString update = SQLiteDataBase::scmdUpdate + " " + db.tableName() + " " + SQLiteDataBase::scmdSet + " ";

    qsizetype index = 0;
    foreach(auto element,db.bindingList())
    {
        auto value = element;
        value = value.remove(":");

        switch (static_cast<int>(frame.at(index).userType()))
        {
        case QMetaType::Type::Int:
            update += value + "='" + QString::number(frame.at(index).toInt()) + "'";
            break;
        case QMetaType::Type::Double:
            update += value + "='" + QString::number(frame.at(index).toDouble()) + "'";
            break;
        case QMetaType::Type::QString:
            update += value + "='" + frame.at(index).toString() + "'";
            break;
        case QMetaType::Type::Bool:
            update += value + "='" + QString::number(frame.at(index).toBool()) + "'";
            break;
        }

        if(element != db.bindingList().at(db.bindingList().size() - 1))
            update += ",";
        index++;
    }

    QString valueStr = "";

    if(SQLiteDataBase::isInteger(primaryKey))
        valueStr = QString::number(primaryKey.toInt());
    else
        valueStr = primaryKey.toString();

    update +=  " " + SQLiteDataBase::scmdWhere + " " + db.primaryKeyName() + "=" + valueStr + """";

    if(!updateQuery.prepare(update))
        db.sqlError(updateQuery.lastError(),"updateFrame prepare");
    if(!updateQuery.exec())
        db.sqlError(updateQuery.lastError(),"updateFrame exec");
}

void SQLiteDataUpdateder::updateData(const QString& parameter,QVariant primaryKey, QVariant data)
{
    QSqlQuery updateDataQuery(db);

    QString valueStr = "";

    if(SQLiteDataBase::isInteger(primaryKey))
        valueStr = QString::number(primaryKey.toInt());
    else
        valueStr = primaryKey.toString();

    QString updateDataCmd = SQLiteDataBase::scmdUpdate + " " + db.tableName() + " " + SQLiteDataBase::scmdSet + " " + SQLiteDataBase::removeSpecialCharacters(parameter) + "='" +
            "%1' " + SQLiteDataBase::scmdWhere + " " + db.primaryKeyName() + "=" + valueStr + """";

    if(SQLiteDataBase::isInteger(data))
        updateDataCmd = updateDataCmd.arg(QString::number(data.toLongLong()));
    else if(data.userType() == QMetaType::Type::Double)
        updateDataCmd = updateDataCmd.arg(QString::number(data.toDouble()));
    else if(data.userType() == QMetaType::Type::QString)
        updateDataCmd = updateDataCmd.arg(data.toString());

    if(!updateDataQuery.prepare(updateDataCmd))
        db.sqlError(updateDataQuery.lastError(),"updateData prepare");
    if(!updateDataQuery.exec())
        db.sqlError(updateDataQuery.lastError(),"updateData exec");
}
