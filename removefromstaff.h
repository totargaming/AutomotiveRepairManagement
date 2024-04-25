#ifndef REMOVEFROMSTAFF_H
#define REMOVEFROMSTAFF_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>

namespace Ui {
class RemoveFromStaff;
}

class RemoveFromStaff : public QDialog, Validation
{
    Q_OBJECT

public:
    explicit RemoveFromStaff(QWidget *parent = nullptr);
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);

    ~RemoveFromStaff();
signals:
    void staffRemoved();
private slots:
    void on_removeBtn_clicked();

    void on_removeList_currentTextChanged(const QString &text);

private:
    Ui::RemoveFromStaff *ui;
    QSqlDatabase database;

};

#endif // REMOVEFROMSTAFF_H
