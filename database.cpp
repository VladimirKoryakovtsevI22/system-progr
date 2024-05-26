#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
}

Database::~Database()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool Database::db_connect(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Не удалось открыть базу данных: " << db.lastError().text();
        return false;
    }

    qDebug() << "Подключение в бд выполнено.";
    return true;
}


