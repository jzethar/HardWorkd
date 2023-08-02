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
    GameSettingsWid(QWidget *parent = nullptr);
    ~GameSettingsWid();

private:
    QPushButton *startGame = new QPushButton(QString("Start Game"));
    QVBoxLayout *settingsWidLayoutV = new QVBoxLayout;
    QSpinBox *wordsAmount = new QSpinBox;
    QSpinBox *secondsAmount = new QSpinBox;
    QLabel *wordsLabel = new QLabel("Enter amount of words");
    QLabel *timerLabel = new QLabel("Enter time for a word (s)");

    QCheckBox *checkPlayWithTimer = new QCheckBox("Case sensitive");

    bool gameWasStarted = false; // to not duplicate emit of signal

    void setupWordsSpinBox();
    void setupTimerSpinBox();
    void setView();

    void closeEvent(QCloseEvent *event);

private slots:
    void startGameWithSettings();
    void checkedPlayedWithTimer(int state);

signals:
    void startGameWithSettingsSig(GameSettings settings);
};

#endif // GAME_WID_H
