#ifndef WORD_INFO_H
#define WORD_INFO_H

#include <QString>
#include <QDateTime>

typedef struct WordInfo
{
    QString word;
    QString translation;
    bool state = true;
    bool correctness = true;

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
    bool wordToTranslation = true; // here if we have true we need to translate "word" to "translation" if false viceversa
    bool selectLastWords = false;

    GameSettings(unsigned char words, unsigned char timer, bool playWithTimer, bool wordToTranslation, bool selectLastWords)
    {
        this->words = words;
        this->timer = timer;
        this->playWithTimer = playWithTimer;
        this->wordToTranslation = wordToTranslation;
        this->selectLastWords = selectLastWords;
    }

    GameSettings(unsigned char words, unsigned char timer, bool wordToTranslation)
    {
        this->timer = timer;
        this->words = words;
        this->wordToTranslation = wordToTranslation;
    }

    GameSettings(unsigned char words, bool wordToTranslation)
    {
        this->timer = 0;
        this->words = words;
        this->playWithTimer = false;
        this->wordToTranslation = wordToTranslation;
    }

    GameSettings()
    {
        words = 0;
        timer = 0;
    }

} GameSettings;

#endif