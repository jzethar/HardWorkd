#ifndef GAME_WID_H
#define GAME_WID_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
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

    int score = 0;

private slots:
    void stopGameSlot();

signals:
    void stopGameSig(const ScoreInfo& scoreInfo);
};



#endif //GAME_WID_H
