#ifndef START_WIN_H
#define START_WIN_H

#include <QSqlDatabase>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "widgets/GameWid.h"
#include "widgets/StartWid.h"
#include "DatabaseService.h"

class StartWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWin(QWidget *parent = Q_NULLPTR);
    virtual ~StartWin() {}

private:
    StartWid *startWid = new StartWid(this);
    GameWid *gameWid = new GameWid(this);
    DatabaseService databaseService = DatabaseService();

private slots:
    void startGameWid();
    void stopGameWid(const ScoreInfo& score);
};

#endif // START_WIN_H