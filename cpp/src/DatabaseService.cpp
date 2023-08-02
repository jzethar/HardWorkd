
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
    query.prepare("CREATE TABLE IF NOT exists words(id INTEGER PRIMARY KEY AUTOINCREMENT, word TEXT, translation TEXT);");

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
    query.prepare("CREATE TABLE IF NOT exists score(date INTEGER, score INTEGER);");

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

bool DatabaseService::getWords(QList<WordInfo> &words, int amountOfWords, bool getLastWords) const
{
    QSqlQuery querySelectWords;
    QString selectWords = QString("SELECT word, translation from words ") + QString(getLastWords ? " order by id DESC " : "") + QString("LIMIT ") + QString::number(amountOfWords) + ";";
    querySelectWords.prepare(selectWords);
    if (querySelectWords.exec())
    {
        if (querySelectWords.next())
        {
            WordInfo word;
            word.word = querySelectWords.value(0).toString();
            word.translation = querySelectWords.value(1).toString();
            words.insert(words.end(), word);
        }
        else
        {
            return true;
        }
    }
    else
    {
        qDebug() << querySelectWords.lastError();
        return false;
    }
    return false;
}

bool DatabaseService::getLastScore(ScoreInfo &score) const
{
    QSqlQuery querySelectScore;
    querySelectScore.prepare("SELECT * from score where date = (select max(date) from score);");
    if (querySelectScore.exec())
    {
        if (querySelectScore.next())
        {
            score.timestamp = querySelectScore.value(0).toLongLong();
            score.score = querySelectScore.value(1).toInt();
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
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

bool DatabaseService::saveScore(const ScoreInfo &score)
{
    QSqlQuery querySaveScore;
    querySaveScore.prepare("INSERT INTO score VALUES (:date, :score)");
    querySaveScore.bindValue(":date", score.timestamp);
    querySaveScore.bindValue(":score", score.score);

    if (querySaveScore.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "add person failed: " << querySaveScore.lastError();
        return false;
    }
}