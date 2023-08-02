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
    StartWid(QWidget *parent, std::shared_ptr<DatabaseService> databaseService);
    ~StartWid();
    void setDatabase(std::shared_ptr<DatabaseService> databaseService);

private:
    QLabel *labelScore = new QLabel(this);
    QLabel *labelTime = new QLabel(this);
    QPushButton *startGame = new QPushButton(QString("Start Game"));
    QPushButton *uploadCSVFile = new QPushButton(QString("Upload CSV"));
    QVBoxLayout *startWidLayoutV = new QVBoxLayout;

    QLineEdit *databaseFile = new QLineEdit;
    QPushButton *chooseDbButton = new QPushButton(QString("Choose database"));
    QHBoxLayout *databaseLayoutH = new QHBoxLayout;

    std::shared_ptr<DatabaseService> databaseService;

private slots:
    void startGameSlot();
    void uploadFileSlot();
    void chooseDatabaseFile();

signals:
    void startGameSig();
    void uploadFileSig();
};



#endif //START_WID_H
