#include "sqlitedatabase.h"
#include "sqlitevaluebinder.h"
#include "sqlitedataupdateder.h"
#include "sqlitedeleter.h"
#include "sqlitequerydata.h"
#include "sqlitereader.h"
#include "sqliteprimarykeys.h"

#include <iostream>
#include <QDebug>
#include <QDialog>

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

int main(int argc, char *argv[])
{
    return EXIT_SUCCESS;
}

void testCreateDataBase()
{
    QList<QPair<QString,QString>> table
    {
        {"ID","INTEGER PRIMARY KEY AUTOINCREMENT"},
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
    QVariantList vl{{400},{1},{2},{3},{4},{5},{"Update Test!"}};
    for(int i=0;i<10;i++)
    {
        int val =(vl.at(0).toInt());
        val+=10;
        vl[0] = val;
        SQLiteValueBinder vb(x,vl);
    }
}

void testUpdateFrame()
{
    QVariantList ut{{300},{5.8},{10.1234},{7},{8},{9},{"Update Test! hahahah"}};
    SQLiteDataUpdateder(x).updateFrame(420,ut);
}

void testUpdateData()
{
    SQLiteDataUpdateder sdu(x);
    sdu.updateData("pilotID",641,1998);
    sdu.updateData("information",642,"updateSingle data Test xxx!");
}

void testDeleteFrame()
{
    SQLiteDeleter(x).deleteFrame(410);
}

void testDeleteAll()
{
    SQLiteDeleter(x).deleteAll();
}

void testIsExistID()
{
    SQLitePrimaryKeys pk(x);
    qDebug() << pk.isExist(430);
    qDebug() << pk.isExist(999);
}

void testIsExistsIDs()
{
    foreach(auto& id,SQLitePrimaryKeys(x).existIDs())
        qDebug() << id.toInt();
}

void testQueryData()
{
    qDebug() << SQLiteQueryData(x).queryData("information",440).toString();
}

void testReadAll()
{
    foreach (auto element,SQLiteReader(x).readAll(440))
    {
        if(SQLiteDataBase::isInteger(element))
            qDebug() << element.toInt();
        if(element.type() == QVariant::Type::Double)
            qDebug() << element.toDouble();
        if(element.type() == QVariant::Type::String)
            qDebug() << element.toString();
    }
}
