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

void Database::commands_start()
{
    QTextStream input(stdin);
    QString command;

    while (true) {
        qDebug() << "Введите sql-команду или exit для выхода: ";
        command = input.readLine().trimmed();

        if (command.toLower() == "exit") {
            qDebug() << "Закрываем..";
            break;
        }

        QSqlQuery query;
        if (!query.exec(command)) {
            qDebug() << "Ошибка при выполнении команды:" << query.lastError().text();
            continue;
        }

        if (query.isSelect()) {
            while (query.next()) {
                QStringList row;
                for (int i = 0; i < query.record().count(); ++i) {
                    row << query.value(i).toString();
                }
                qDebug() << row.join(", ");
            }
        } else {
            qDebug() << "Команда выполнена";
        }
    }
}
