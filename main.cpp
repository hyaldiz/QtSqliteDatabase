#include "sqlitedatabase.hpp"
#include "sqlitevaluebinder.hpp"
#include "sqlitedataupdateder.hpp"
#include "sqlitedeleter.hpp"
#include "sqlitequerydata.hpp"
#include "sqlitereader.hpp"
#include "sqliteprimarykeys.hpp"

#include <iostream>
#include <QDebug>
#include <QDialog>
#include <QApplication>

void testCreateDataBase();
void testBindValue();
void testUpdateFrame();
void testUpdateData();
void testDeleteFrame();
void testDeleteAll();
void testIsExistID();
void testIsExistsIDs();
void testQueryData();
void testReadAll();

SQLiteDataBase x("sqliteExample","huseyinYALDIZ");

void errorCallBack(const QString& error) {
    qDebug() << "[CALLBACK]" << error;
}

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

    x.setDebugCallBack(errorCallBack);
    x.sqlError(QSqlError("Dummy Error"),"Me");

    testCreateDataBase();

    testDeleteAll();

    return a.exec();
}

void testCreateDataBase()
{
    //passed
    QList<QPair<QString,QString>> table
    {
        {"ID","TEXT PRIMARY KEY"},
        {"droneID","INTEGER"},   /*"INTEGER PRIMARY KEY UNIQUE"*/   /*"INTEGER AUTOINCREMENT"*/
        {"pilotID","INTEGER"},
        {"startPosition","INTEGER"},
        {"sessionID","INTEGER"},
        {"flightTime","REAL"},
        {"stopPosition","INTEGER"},
        {"information","TEXT"}
    };
    x.createTable("mytable5",table,"ID",0);
}

void testBindValue()
{
    //DONE
    QVariantList vl1{{"Veli"},{1},{2},{3},{4},{5},{"Update Test!"}};
    QVariantList vl2{{"Huseyin"},{1},{2},{3},{4},{5},{"Update Test!"}};
    QVariantList vl3{{"Yakup"},{1},{2},{3},{4},{5},{"Update Test!"}};

    SQLiteValueBinder vb(x);
    vb.bindValues(vl1);
    vb.bindValues(vl2);
    vb.bindValues(vl3);

    //    for(int i=0;i<10;i++)
//    {
//        int val =(vl.at(0).toInt());
//        val+=10;
//        vl[0] = val;
//        SQLiteValueBinder vb(x);
//        vb.bindValues(vl);
//    }
}

void testUpdateFrame()
{
    //DONE
    QVariantList ut{"Tunahan",10,{5.8},{10.1234},{7},{8},{9},{"Update Test! hahahah"}};
    SQLiteDataUpdateder(x).updateFrame("Veli",ut);
}

void testUpdateData()
{
    //DONE
    SQLiteDataUpdateder sdu(x);
    sdu.updateData("information","Huseyin","updateSingle data Test xxx!");
}

void testDeleteFrame()
{
    //DONE
    SQLiteDeleter(x).deleteFrame("Huseyin");
}

void testDeleteAll()
{
    SQLiteDeleter(x).deleteAll();
}

void testIsExistID()
{
    //DONE
    SQLitePrimaryKeys pk(x);
    qDebug() << pk.isExist("Huseyin");
    qDebug() << pk.isExist("Uygar");
    qDebug() << pk.isExist("Eylül");
}

void testIsExistsIDs()
{
    //DONE
    foreach(auto& id,SQLitePrimaryKeys(x).existIDs())
        qDebug() << id.toString();
}

void testQueryData()
{
    //DONE
    qDebug() << SQLiteQueryData(x).queryData("stopPosition","Huseyin").toString();
}

void testReadAll()
{
    //DONE
    foreach (auto element,SQLiteReader(x).readAll("Huseyin"))
    {
        if(SQLiteDataBase::isInteger(element))
            qDebug() << element.toInt();
        if(element.userType() == QMetaType::Type::Double)
            qDebug() << element.toDouble();
        if(element.userType() == QMetaType::Type::QString)
            qDebug() << element.toString();
    }
}
