cmake_minimum_required(VERSION 3.24)

project(QtSqliteDatabase LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(TARGET Qt6::Core AND TARGET Qt6::Sql)
    set(QT_VERSION_MAJOR 6)
    set(QT_CORE_LIB Qt6::Core)
    set(QT_SQL_LIB  Qt6::Sql)

elseif(TARGET Qt5::Core AND TARGET Qt5::Sql)
    set(QT_VERSION_MAJOR 5)
    set(QT_CORE_LIB Qt5::Core)
    set(QT_SQL_LIB  Qt5::Sql)
else()
    find_package(Qt6 QUIET COMPONENTS Core Sql)
    if(Qt6_FOUND)
        set(QT_VERSION_MAJOR 6)
        set(QT_CORE_LIB Qt6::Core)
        set(QT_SQL_LIB  Qt6::Sql)
    else()
        find_package(Qt5 REQUIRED COMPONENTS Core Sql)
        set(QT_VERSION_MAJOR 5)
        set(QT_CORE_LIB Qt5::Core)
        set(QT_SQL_LIB  Qt5::Sql)
    endif()
endif()

if(NOT QT_VERSION_MAJOR)
    message(FATAL_ERROR "QtSqliteDatabase: Neither Qt5 nor Qt6 found. Please call find_package(Qt6/Qt5 ...) in the parent project.")
endif()

add_library(QSQLite
    sqlitedatabase.cpp
    sqlitedataupdateder.cpp
    sqlitedeleter.cpp
    sqliteprimarykeys.cpp
    sqlitequerydata.cpp
    sqlitereader.cpp
)

target_include_directories(QSQLite
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(QSQLite
    PUBLIC
        ${QT_CORE_LIB}
        ${QT_SQL_LIB}
)

add_library(QtSqliteDatabase::QSQLite ALIAS QSQLite)

option(QSQLITE_BUILD_EXAMPLE "Build QtSqliteDatabase example (main.cpp)" OFF)

if(QSQLITE_BUILD_EXAMPLE)
    add_executable(QtSqliteDatabaseExample
        main.cpp
    )

    target_link_libraries(QtSqliteDatabaseExample
        PRIVATE
            QtSqliteDatabase::QSQLite
    )
endif()
