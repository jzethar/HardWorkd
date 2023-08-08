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
#include <QEvent>

class GameWid : public QWidget
{
    Q_OBJECT

public:
    GameWid(QWidget *parent = nullptr);
    ~GameWid();

    void setDatabase(std::shared_ptr<DatabaseService> databaseService);

private:

    QLabel *wordLabel = new QLabel;
    QLabel *secondsLabel = new QLabel;
    QLineEdit *wordEnterEdit = new QLineEdit;
    QPushButton *stopGame = new QPushButton(QString("Stop Game"));
    QVBoxLayout *gameWidLayoutV = new QVBoxLayout;

    QFont wordsFont;

    GameSettingsWid *gameSettingsWid;
    QTimer *timerForWord = new QTimer;

    int score = 0;
    int timeForWord = 0;
    GameSettings settings;

    QList<WordInfo> words;
    std::shared_ptr<DatabaseService> databaseService;
    int whatTheWordIsNow = 0;

    void endGame();
    bool eventFilter(QObject *target, QEvent *event);
    bool eventKeyPress(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void nextWord();

    inline void makeLabels();
    // QString 

private slots:
    void stopGameSlot();
    void startGameWid(GameSettings gameSettings);
    void updateTime();
    void checkWord();

signals:
    void stopGameSig(const ScoreInfo &scoreInfo);
    void checkWordSig();
};

#endif // GAME_WID_H
