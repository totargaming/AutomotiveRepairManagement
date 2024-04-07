#ifndef PARTUPDATE_H
#define PARTUPDATE_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
namespace Ui {
class PartUpdate;
}

class PartUpdate : public QDialog, public Validation
{
    Q_OBJECT

public:
    explicit PartUpdate(QWidget *parent = nullptr);
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);
    ~PartUpdate();

signals:
    void partUpdated();

private slots:
    void on_deleteBtn_clicked();

    void on_updateBtn_clicked();


    void on_removeList_currentTextChanged(const QString &text);

private:
    Ui::PartUpdate *ui;
    QSqlDatabase database;

};

#endif // PARTUPDATE_H
