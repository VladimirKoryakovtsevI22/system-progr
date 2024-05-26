#include <QCoreApplication>
#include <QTextStream>
#include "database.h"
#include <windows.h>

void commands_start()
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SetConsoleOutputCP(1251);


    QTextStream input(stdin);
    qDebug() << "Введите название бд: ";
    QString dbName = input.readLine().trimmed();

    Database db;
    if (!db.db_connect(dbName)) {
        return -1;
    }

    commands_start();

    return a.exec();
}
