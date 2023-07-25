QT += sql

SOURCES += \
    $$PWD/sqlitedatabase.cpp \
    $$PWD/sqlitedataupdateder.cpp \
    $$PWD/sqlitedeleter.cpp \
    $$PWD/sqliteprimarykeys.cpp \
    $$PWD/sqlitequerydata.cpp \
    $$PWD/sqlitereader.cpp

HEADERS += \
    $$PWD/sqlitedatabase.hpp \
    $$PWD/sqlitedataupdateder.hpp \
    $$PWD/sqlitedeleter.hpp \
    $$PWD/sqliteprimarykeys.hpp \
    $$PWD/sqlitequerydata.hpp \
    $$PWD/sqlitereader.hpp \
    $$PWD/sqlitevaluebinder.hpp
