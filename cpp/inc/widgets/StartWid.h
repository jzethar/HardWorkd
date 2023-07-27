#ifndef START_WID_H
#define START_WID_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "DatabaseService.h"

class StartWid : public QWidget
{
    Q_OBJECT
    
public:
    StartWid(QWidget *parent = nullptr);
    StartWid(QWidget *parent, const DatabaseService& dataService);
    ~StartWid();
    void setDatabase(const DatabaseService& dataService);

private:
    QLabel *labelScore = new QLabel(this);
    QLabel *labelTime = new QLabel(this);
    QPushButton *startGame = new QPushButton(QString("Start Game"));
    QVBoxLayout *startWidLayoutV = new QVBoxLayout;

    DatabaseService databaseService;

private slots:
    void startGameSlot();

signals:
    void startGameSig();
};



#endif //START_WID_H
