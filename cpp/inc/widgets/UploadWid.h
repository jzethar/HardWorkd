//
// Created by julian on 5/13/21.
//

#ifndef LEARN_MAINWINDOW_H
#define LEARN_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTableView>

#include "TableModel.h"
#include "DatabaseService.h"
#include "WordInfo.h"


class UploadWid : public QWidget
{
    Q_OBJECT

public:
    explicit UploadWid(QWidget *parent = Q_NULLPTR);
    virtual ~UploadWid() {}
    void setDatabase(std::shared_ptr<DatabaseService> databaseService);


private:
    // QWidget *LearnViewerWid = new QWidget;
    QVBoxLayout *LearnLayoutV = new QVBoxLayout;

    QLineEdit *nmFile = new QLineEdit;
    QHBoxLayout *nmNchsLayoutH = new QHBoxLayout;
    QPushButton *chsFile = new QPushButton(QString("Choose CSV"));
    QPushButton *saveFile = new QPushButton(QString("Save words"));
    QPushButton *saveWordsInDb = new QPushButton(QString("Save in database"));

    TableModel *table ;
    QTableView *CSVTable = new QTableView;
    QVBoxLayout *CSVLayoutV = new QVBoxLayout;

    std::vector<WordInfo> fileInfoVec;
    std::shared_ptr<DatabaseService> databaseService;

private slots:
    void readCSVWords(QString fileName);
    void writeCSVFile(QString fileName);
    void chooseCSVFile();
    // void saveNewFile();
    // void chooseDatabaseFile();
    void saveInDatabase();

signals:
    void uploadDoneSig();

};


#endif //LEARN_MAINWINDOW_H