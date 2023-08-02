#ifndef GAME_WID_H
#define GAME_WID_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include "widgets/GameSettingsWid.h"
#include "WordInfo.h"
#include "DatabaseService.h"
#include <QTimer>

class GameWid : public QWidget
{
    Q_OBJECT

public:
    GameWid(QWidget *parent = nullptr);
    ~GameWid();

    void setDatabase(std::shared_ptr<DatabaseService> databaseService);

private:

    const QString wordTIME = "Time: ";

    QLabel *timerLabel = new QLabel("Time: ");
    QLineEdit *nmFile = new QLineEdit;
    QPushButton *stopGame = new QPushButton(QString("Stop Game"));
    QVBoxLayout *gameWidLayoutV = new QVBoxLayout;

    GameSettingsWid *gameSettingsWid;
    QTimer *timerForWord = new QTimer;

    int score = 0;
    int timeForWord = 0;
    GameSettings settings;

    QList<WordInfo> words;
    std::shared_ptr<DatabaseService> databaseService;

private slots:
    void stopGameSlot();
    void startGameWid(GameSettings gameSettings);
    void updateTime();

signals:
    void stopGameSig(const ScoreInfo &scoreInfo);
};

#endif // GAME_WID_H
