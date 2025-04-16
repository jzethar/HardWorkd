
#include "DatabaseService.h"

#include "QDebug"
#include <QSqlQuery>
#include <QSqlError>
#include <algorithm>
#include <random>

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
    query.prepare("CREATE TABLE IF NOT exists words" 
                  "(id INTEGER PRIMARY KEY AUTOINCREMENT, word TEXT, translation TEXT, lasttemp INTEGER, errors INTEGER);");

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
    if (path.length() > 0)
    {
        this->path = path;
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
    return true;
}

const QString DatabaseService::getPath() const
{
    return path;
}

DatabaseService::~DatabaseService()
{
    if (wordsDatabase.isOpen())
    {
        wordsDatabase.close();
    }
}

bool DatabaseService::getWords(QList<WordInfo> &words, const GameSettings &gameSettings) const
{
    // STOPPED HERE
    QString order = "";
    if (gameSettings.selectLastWords && gameSettings.selectWordsWithMostErrors && gameSettings.selectUnusedForLongTimeWords)
    {
        order = " order by lasttemp asc, errors desc, id desc ";
    }
    if (gameSettings.selectLastWords && gameSettings.selectWordsWithMostErrors && !gameSettings.selectUnusedForLongTimeWords)
    {
        order = " order by errors desc, id desc ";
    }
    if (gameSettings.selectLastWords && !gameSettings.selectWordsWithMostErrors && !gameSettings.selectUnusedForLongTimeWords)
    {
        order = " order by id desc ";
    }
    if (!gameSettings.selectLastWords && gameSettings.selectWordsWithMostErrors && !gameSettings.selectUnusedForLongTimeWords)
    {
        order = " order by errors desc ";
    }
    if (!gameSettings.selectLastWords && !gameSettings.selectWordsWithMostErrors && gameSettings.selectUnusedForLongTimeWords)
    {
        order = " order by lasttemp asc ";
    }
    if (gameSettings.selectRandom)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        uint amount = 0;
        QSqlQuery querySelectWordsAmount;
        QString selectWordsAmount = QString("SELECT count(*) from words;");
        querySelectWordsAmount.prepare(selectWordsAmount);
        if (querySelectWordsAmount.exec())
        {
            while (querySelectWordsAmount.next()) 
            {
                amount = querySelectWordsAmount.value(0).toUInt();
            }
        }
        std::uniform_int_distribution<> dist(1, amount);
        order = order + ((gameSettings.words > 0) ? " WHERE " : "");
        for (int i =0; i < uint(gameSettings.words); i++) 
        {
            int random_number = dist(rng);
            order += "id = " + QString::number(random_number) + " or ";
        }
        order.chop(3);
        
    }

    QSqlQuery querySelectWords;
    QString selectWords = QString("SELECT word, translation, lasttemp, errors from words ") + order + 
                          QString("LIMIT ") + QString::number(gameSettings.words) + ";";
    querySelectWords.prepare(selectWords);
    if (querySelectWords.exec())
    {
        while (querySelectWords.next())
        {
            WordInfo word;
            word.word = querySelectWords.value(0).toString();
            word.translation = querySelectWords.value(1).toString();
            word.lasttemp = querySelectWords.value(2).toLongLong();
            word.errors = querySelectWords.value(3).toInt();
            words.insert(words.end(), word);
        }
        return true;
    }
    else
    {
        qDebug() << querySelectWords.lastError();
        return false;
    }
    return false;
}

// bool DatabaseService::getWordsAmount(ScoreInfo &score) const

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

bool DatabaseService::updateWords(const QList<WordInfo> &words)
{
    for (const auto &w : words)
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("UPDATE words set lasttemp = :lasttemp, errors = :errors where word = :word and translation = :translation");
        queryAdd.bindValue(":word", w.word);
        queryAdd.bindValue(":translation", w.translation);
        queryAdd.bindValue(":lasttemp", w.lasttemp);
        queryAdd.bindValue(":errors", w.errors);

        if (queryAdd.exec())
        {
            continue;
        }
        else
        {
            qDebug() << "update words failed: " << queryAdd.lastError();
            return false;
        }
    }
    return true;
}

bool DatabaseService::saveNewWords(const QList<WordInfo> &words) 
{
    for (const auto &w : words)
    {
        if (w.state)
        {
            QSqlQuery queryAdd;
            queryAdd.prepare("INSERT INTO words (word, translation, lasttemp, errors) VALUES (:word, :translation, :lasttemp, :errors)");
            queryAdd.bindValue(":word", w.word);
            queryAdd.bindValue(":translation", w.translation);
            queryAdd.bindValue(":lasttemp", w.lasttemp);
            queryAdd.bindValue(":errors", w.errors);

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