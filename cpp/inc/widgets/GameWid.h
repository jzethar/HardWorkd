#ifndef GAME_WID_H
#define GAME_WID_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include "widgets/GameSettingsWid.h"
#include "WordInfo.h"

class GameWid : public QWidget
{
    Q_OBJECT

public:
    GameWid(QWidget *parent = nullptr);
    ~GameWid();

private:
    QLineEdit *nmFile = new QLineEdit;
    QPushButton *stopGame = new QPushButton(QString("Stop Game"));
    QVBoxLayout *gameWidLayoutV = new QVBoxLayout;

    GameSettingsWid *gameSettingsWid;

    int score = 0;
    GameSettings settings;

private slots:
    void stopGameSlot();
    void startGameWid(GameSettings gameSettings);

signals:
    void stopGameSig(const ScoreInfo &scoreInfo);
};

#endif // GAME_WID_H
