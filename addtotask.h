#ifndef ADDTOTASK_H
#define ADDTOTASK_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
#include <QDate>
namespace Ui {
class AddToTask;
}

class AddToTask : public QDialog, Validation
{
    Q_OBJECT

public:
    explicit AddToTask(QWidget *parent = nullptr);
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);
    ~AddToTask();
signals:
    void taskAdded();
private slots:
    void on_modelBox_currentTextChanged(const QString &arg1);

    void on_addBtn_clicked();

private:
    Ui::AddToTask *ui;
    QSqlDatabase database;

};

#endif // ADDTOTASK_H
