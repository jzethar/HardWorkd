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

    bool getWords(QList<WordInfo> &words, const GameSettings &gameSettings) const;
    bool getLastScore(ScoreInfo &score) const;

    bool updateWords(const QList<WordInfo> &words);

    // tables
    bool createTableWords();
    bool createTableScore();

    const QString getPath() const;

private:
    QSqlDatabase wordsDatabase;

    QString path;
};

#endif // DATABASE_SERVICE_H

