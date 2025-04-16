#ifndef GAME_SETTINGS_WID_H
#define GAME_SETTINGS_WID_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include "WordInfo.h"
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>

class GameSettingsWid : public QDialog
{
    Q_OBJECT

public:
    GameSettingsWid(QWidget *parent = nullptr, bool lite = false);
    ~GameSettingsWid();

private:
    QPushButton *startGame = new QPushButton(QString("Start Game"));
    QVBoxLayout *settingsWidLayoutV = new QVBoxLayout;
    QSpinBox *wordsAmount = new QSpinBox;
    QSpinBox *secondsAmount = new QSpinBox;
    QLabel *wordsLabel = new QLabel("Enter amount of words");
    QLabel *timerLabel = new QLabel("Enter time for a word (s)");

    QCheckBox *checkPlayWithoutTimer = new QCheckBox("Play without timer");
    QCheckBox *checkGetLastWords = new QCheckBox("Take from the end");
    QCheckBox *checkCorrectErrors = new QCheckBox("Error correction after game");

    QLabel *toLabel = new QLabel("Word");
    QLabel *fromLabel  = new QLabel("Translation");
    QPushButton *changeFromToButton = new QPushButton("Change");
    QHBoxLayout *changeLayout = new QHBoxLayout;

    QCheckBox *selectWordsWithMostErrorsCheck = new QCheckBox("Select words with a most errors");
    QCheckBox *selectUnusedForLongTimeCheck = new QCheckBox("Select words that hadn't been repeated for a long time");
    QCheckBox *selectRandomCheck = new QCheckBox("Select in random");

    bool gameWasStarted = false; // to not duplicate emit of signal
    bool wordToTranslateSetting = false;

    bool lite = false;

    inline void setupWordsSpinBox();
    inline void setupTimerSpinBox();
    inline void setupChangeBox();
    inline void setView();

    void closeEvent(QCloseEvent *event);

private slots:
    void startGameWithSettings();
    void checkedPlayWithoutTimer(int state);
    // void checkedPlayLastWords(int state);
    void changeEvent();

signals:
    void startGameWithSettingsSig(GameSettings settings);
};

#endif // GAME_WID_H
