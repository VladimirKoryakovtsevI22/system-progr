#include <QCoreApplication>
#include <QTextStream>
#include "database.h"
#include <windows.h>

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

    db.commands_start();

    return a.exec();
}
