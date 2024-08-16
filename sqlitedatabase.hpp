#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <QSqlDatabase>
#include <QList>
#include <QPair>
#include <QSqlError>
#include <QVariant>
#include <QMetaType>

class SQLiteDataBase : public QSqlDatabase
{
    inline const static QString SQLType = "QSQLITE";

    using DebugCallBack = std::function<void(const QString&)>;
public:
    static QString scmdCreateTabNoExist;
    static QString scmdInsert;
    static QString scmdUpdate;
    static QString scmdSet;
    static QString scmdValues;
    static QString scmdWhere;
    static QString scmdDelete;
    static QString scmdSelect;
    static QString scmdFrom;
    static QString scmdAll;
    static QString scmdExists;
    static QString scmdIsNotNull;

    SQLiteDataBase(const QString dbName,const QString& _connectionName);
    virtual ~SQLiteDataBase();

    void createTable(const QString& tableName,QList<QPair<QString,QString>> table,
                     const QString &primaryKey,int primaryKeyIndex);
    const QString& values()const;
    QStringList bindingList()const;
    const QString& tableName()const;
    const QString& primaryKeyName()const;
    const QList<QPair<QString,QString>>& partTable()const;
    int primaryKeyIndex()const;

    void sqlError(const QSqlError& error,const QString& sender);

    static bool isInteger(const QVariant &variant);
    static QString removeSpecialCharacters(QString string);

    void setDebugCallBack(DebugCallBack debugCallBack);

private:
    QString connectionName;
    QString dbtableName;
    QString dbvalues;
    QStringList dbbindingList;

    QString dbprimaryKeyName;
    int dbprimaryKeyIndex;

    QList<QPair<QString,QString>> dbPartTable;

    DebugCallBack _debugCallBack = nullptr;
};

#endif // SQLITEDATABASE_H
