#ifndef DATABASE_SERVICE_H
#define DATABASE_SERVICE_H

#include <QSqlDatabase>
#include "WordInfo.h"

class DatabaseService {
    public:
    DatabaseService(const QString& path);
    DatabaseService();

    ~DatabaseService();

    bool isOpen() const;
    bool createDatabase(const QString &path);
    
    bool saveNewWords(const QList<WordInfo> &words);
    bool saveScore(const ScoreInfo& score);

    bool getWords(QList<WordInfo> &words, int amountOfWords, bool getLastWords = false) const;
    bool getLastScore(ScoreInfo &score) const;

    // tables
    bool createTableWords();
    bool createTableScore();

private:
    QSqlDatabase wordsDatabase;
};

#endif // DATABASE_SERVICE_H

