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
    QString update =
        SQLiteDataBase::scmdUpdate  + " " +
        db.tableName()              + " " +
        SQLiteDataBase::scmdSet     + " ";

    qsizetype index = 0;
    qsizetype listSize = db.bindingList().size();

    if (frame.size() != listSize) {
        db.sqlError(QSqlError("Frame and list size not match"),"SQLiteDataUpdateder::updateFrame");
        return;
    }

    if (frame.isEmpty() || db.bindingList().isEmpty()) {
        db.sqlError(QSqlError("Frame or binding list is empty"),"SQLiteDataUpdateder::updateFrame");
        return;
    }

    foreach(auto element,db.bindingList()) {
        auto value = element.remove(":");

        QVariant fieldValue = frame.at(index);
        QString fieldString;

        switch (fieldValue.userType()) {
        case QMetaType::Type::Int:
            fieldString = QString::number(fieldValue.toInt());
            break;
        case QMetaType::Type::Double:
            fieldString = QString::number(fieldValue.toDouble());
            break;
        case QMetaType::Type::QString:
            fieldString = fieldValue.toString();
            break;
        case QMetaType::Type::Bool:
            fieldString = QString::number(fieldValue.toBool());
            break;
        default:
            db.sqlError(QSqlError("Unknown Type"),"SQLiteDataUpdateder::updateFrame");
            continue;
        }

        update += value + "='" + fieldString + "'";

        if(index < listSize - 1) {
            update += ",";
        }

        index++;
    }

    QString valueStr = SQLiteDataBase::isInteger(primaryKey)
        ? QString::number(primaryKey.toInt())
        : "'" + primaryKey.toString() + "'";

    update += " " + SQLiteDataBase::scmdWhere +
              " " + db.primaryKeyName() +
              "=" + valueStr;

    if (!updateQuery.prepare(update)) {
        db.sqlError(updateQuery.lastError(), "updateFrame prepare");
        return;
    }

    if (!updateQuery.exec()) {
        db.sqlError(updateQuery.lastError(), "updateFrame exec");
    }
}

void SQLiteDataUpdateder::updateData(const QString& parameter,QVariant primaryKey, QVariant data)
{
    QSqlQuery updateDataQuery(db);

    QString valueStr = "";

    if(SQLiteDataBase::isInteger(primaryKey))
        valueStr = QString::number(primaryKey.toInt());
    else
        valueStr = "'" + primaryKey.toString() + "'";

    QString updateDataCmd =
        SQLiteDataBase::scmdUpdate                          + " " +
        db.tableName()                                      + " " +
        SQLiteDataBase::scmdSet                             + " " +
        SQLiteDataBase::removeSpecialCharacters(parameter)  + "='" + "%1' " +
        SQLiteDataBase::scmdWhere                           + " " +
        db.primaryKeyName()                                 + "=" +
        valueStr                                            + """";

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
