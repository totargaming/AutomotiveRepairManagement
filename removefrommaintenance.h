#ifndef REMOVEFROMMAINTENANCE_H
#define REMOVEFROMMAINTENANCE_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
#include <QDate>
namespace Ui {
class RemoveFromMaintenance;
}

class RemoveFromMaintenance : public QDialog, Validation
{
    Q_OBJECT

public:
    explicit RemoveFromMaintenance(QWidget *parent = nullptr);
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);

    ~RemoveFromMaintenance();
signals:
    void maintenanceRemoved();
private slots:
    void on_removeBtn_clicked();

    void on_removeList_currentTextChanged(const QString &arg1);

private:
    Ui::RemoveFromMaintenance *ui;
    QSqlDatabase database;

};

#endif // REMOVEFROMMAINTENANCE_H
