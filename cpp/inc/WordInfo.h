#ifndef WORD_INFO_H
#define WORD_INFO_H

#include <QString>
#include <QDateTime>

typedef struct WordInfo
{
    QString word;
    QString translation;
    bool state = true;

    WordInfo(QString word, QString translation)
    {
        this->word = std::move(word);
        this->translation = translation;
    }
    void set()
    {
        this->state = true;
    }
    void unset()
    {
        this->state = false;
    }
    WordInfo() {}
} WordInfo;

typedef struct ScoreInfo
{
    long long timestamp;
    int score;

    ScoreInfo(long long timestamp, int score)
    {
        this->score = score;
        this->timestamp = timestamp;
    }

    ScoreInfo()
    {
        this->score = 0;
        this->timestamp = 0;
    }

    QString serializeScoreInfo() const
    {
        QDateTime time;
        time.setMSecsSinceEpoch(timestamp);
        QString outInfo = "Time: " + time.toString() + QString(" Score: ") + QString::number(score);
        return outInfo;
    }

    QString serializeScore() const
    {
        return QString(" Score: ") + QString::number(score);
    }
    QString serializeTime() const
    {
        QDateTime dateTime;
        dateTime.setMSecsSinceEpoch(timestamp);
        return QString("Time: ") + dateTime.toString();
    }

} ScoreInfo;

typedef struct GameSettings
{
    unsigned char words;
    unsigned char timer;
    bool playWithTimer = true;

    GameSettings(unsigned char words, unsigned char timer)
    {
        this->timer = timer;
        this->words = words;
    }

    GameSettings(unsigned char words)
    {
        this->timer = 0;
        this->words = words;
        this->playWithTimer = false;
    }

    GameSettings()
    {
        words = 0;
        timer = 0;
    }

} GameSettings;

#endif