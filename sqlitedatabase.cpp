#include "sqlitedatabase.hpp"
#include <QSqlQuery>
#include <QDebug>

QString SQLiteDataBase::scmdCreateTabNoExist{"CREATE TABLE IF NOT EXISTS"};
QString SQLiteDataBase::scmdInsert{"INSERT INTO"};
QString SQLiteDataBase::scmdUpdate{"UPDATE"};
QString SQLiteDataBase::scmdSet{"SET"};
QString SQLiteDataBase::scmdValues{"VALUES"};
QString SQLiteDataBase::scmdWhere{"WHERE"};
QString SQLiteDataBase::scmdDelete{"DELETE"};
QString SQLiteDataBase::scmdSelect{"SELECT"};
QString SQLiteDataBase::scmdFrom{"FROM"};
QString SQLiteDataBase::scmdAll{"*"};
QString SQLiteDataBase::scmdExists{"EXISTS"};

SQLiteDataBase::SQLiteDataBase(const QString dbName,const QString& _connectionName) : QSqlDatabase(addDatabase(SQLType,_connectionName))
  ,connectionName(_connectionName)
{
    setDatabaseName(dbName+".db");
    bool ok = open();
    if(!ok)
        qCritical() << "SQLite DataBase was not opened for " << connectionName;
}

SQLiteDataBase::~SQLiteDataBase()
{
    close();
}

void SQLiteDataBase::createTable(const QString &tableName,QList<QPair<QString,QString>> table,
                                 const QString &primaryKey,int primaryKeyIndex)
{
    QString createTable = "(";
    QString dbValuesTail = " " + scmdValues + "(";
    dbvalues += SQLiteDataBase::scmdInsert + " " + tableName + "(";

    qsizetype index = 0;
    foreach (auto& element,table)
    {
        bool ok = true;
        if(element.second.indexOf("AUTOINCREMENT") != -1)
            ok = false;
        else
            ok = true;
        if(ok)
        {
            dbvalues += removeSpecialCharacters(element.first);
            dbValuesTail += ":" + removeSpecialCharacters(element.first);
            dbbindingList.append(":" + removeSpecialCharacters(element.first));
        }
        createTable += removeSpecialCharacters(element.first) + " " + element.second;
        if(table.last() != element)
        {
            createTable += ",";
            if(ok)
            {
                dbValuesTail += ",";
                dbvalues += ",";
            }
        }
        else
        {
            createTable += ")";
            dbValuesTail += ")";
            dbvalues += ")";
        }
        index++;
    }
    createTable.insert(0,SQLiteDataBase::scmdCreateTabNoExist + " " + tableName);
    dbvalues += dbValuesTail;

    qDebug() << createTable;
    qDebug() << dbvalues;

    QSqlQuery createQuery{createTable,database(connectionName)};
    if(!createQuery.exec())                 sqlError(createQuery.lastError(),"createTable exec");
    else if(!createQuery.prepare(dbvalues)) sqlError(createQuery.lastError(),"createTable prepare");
    else
    {
        dbPartTable = table;
        dbtableName = tableName;
        dbprimaryKeyName = primaryKey;
        dbprimaryKeyIndex = primaryKeyIndex;
    }
}

const QString& SQLiteDataBase::values() const
{
    return dbvalues;
}

QStringList SQLiteDataBase::bindingList() const
{
    return dbbindingList;
}

const QString &SQLiteDataBase::tableName() const
{
    return dbtableName;
}

const QString &SQLiteDataBase::primaryKeyName() const
{
    return dbprimaryKeyName;
}

const QList<QPair<QString, QString> > &SQLiteDataBase::partTable() const
{
    return dbPartTable;
}

int SQLiteDataBase::primaryKeyIndex() const
{
    return dbprimaryKeyIndex;
}

void SQLiteDataBase::sqlError(const QSqlError &error,const QString& sender)
{
    qWarning() << "Sender --> " << sender << ": sqlite error" << error.text() << "sqlite error type " << error.type();
}

bool SQLiteDataBase::isInteger(const QVariant &variant)
{
    switch (variant.userType())
    {
        case QMetaType::Int:
        case QMetaType::UInt:
        case QMetaType::LongLong:
        case QMetaType::ULongLong:
            return true;
    }
        return false;
}

QString SQLiteDataBase::removeSpecialCharacters(QString string)
{
    return string.remove(' ').remove('-').remove('/');
}
