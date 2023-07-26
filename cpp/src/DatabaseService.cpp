
#include "DatabaseService.h"

#include "QDebug"
#include <QSqlQuery>
#include <QSqlError>

DatabaseService::DatabaseService() {}

DatabaseService::DatabaseService(const QString &path)
{
    wordsDatabase = QSqlDatabase::addDatabase("QSQLITE");
    wordsDatabase.setDatabaseName(path);

    if (!wordsDatabase.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    // if (!createTableWords() || !createTableScore())
    // {
    //     qDebug() << "Error: connection with database fail";
    // }
}

// DatabaseService::DatabaseService(const DatabaseService& service) {
//     service.wordsDatabase = this->wordsDatabase;
// }


// TODO check that it will not remove and create another table 

bool DatabaseService::createTableWords()
{
    bool success = true;

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT exists words(id INTEGER PRIMARY KEY, word TEXT, translation TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'words': one might already exist.";
        return false;
    }

    return success;
}

bool DatabaseService::createTableScore()
{
    bool success = true;

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT exists score(id INTEGER PRIMARY KEY, date INTEGER, score INTEGER);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'score': one might already exist.";
        return false;
    }

    return success;
}

bool DatabaseService::isOpen() const
{
    return wordsDatabase.isOpen();
}

// TODO check if the connector is the same with new

bool DatabaseService::createDatabase(const QString &path)
{
    wordsDatabase = QSqlDatabase::addDatabase("QSQLITE");
    wordsDatabase.setDatabaseName(path);

    if (wordsDatabase.open())
    {
        return (createTableWords() && createTableScore());
    }
    else
    {
        return false;
    }
}

DatabaseService::~DatabaseService()
{
    if (wordsDatabase.isOpen())
    {
        wordsDatabase.close();
    }
}

bool DatabaseService::saveNewWords(const QList<WordInfo> &words) 
{
    for (const auto &w : words)
    {
        if (w.state)
        {
            QSqlQuery queryAdd;
            queryAdd.prepare("INSERT INTO words (word, translation) VALUES (:word, :translation)");
            queryAdd.bindValue(":word", w.word);
            queryAdd.bindValue(":translation", w.translation);

            if (queryAdd.exec())
            {
                continue;
            }
            else
            {
                qDebug() << "add person failed: " << queryAdd.lastError();
                return false;
            }
        }
    }
    return true;
}