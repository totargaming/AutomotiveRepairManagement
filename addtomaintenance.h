#ifndef ADDTOMAINTENANCE_H
#define ADDTOMAINTENANCE_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
#include <QDateEdit>

namespace Ui {
class AddToMaintenance;
}

class AddToMaintenance : public QDialog, Validation
{
    Q_OBJECT

public:
    explicit AddToMaintenance(QWidget *parent = nullptr);
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);
    ~AddToMaintenance();
signals:
    void assigned();
private slots:
    void on_addBtn_clicked();

private:
    Ui::AddToMaintenance *ui;
    QSqlDatabase database;

};

#endif // ADDTOMAINTENANCE_H
