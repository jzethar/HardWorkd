#ifndef DATABASE_SERVICE_H
#define DATABASE_SERVICE_H

#include <QSqlDatabase>
#include "WordInfo.h"

class DatabaseService {
    public:
    DatabaseService(const QString& path);
    // DatabaseService(const DatabaseService& service);
    DatabaseService();

    ~DatabaseService();

    bool isOpen() const;
    bool createDatabase(const QString &path);

    bool selectScore() 
    {
        return true;
    }
    
    bool saveNewWords(const QList<WordInfo> &words);
    bool saveScore(const ScoreInfo& score);
    bool getLastScore(ScoreInfo &score) const;

    // tables
    bool createTableWords();
    bool createTableScore();

private:
    QSqlDatabase wordsDatabase;
};

#endif // DATABASE_SERVICE_H

