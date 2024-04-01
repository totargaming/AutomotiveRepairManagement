#ifndef STORAGE_H
#define STORAGE_H

#include <QDialog>
#include "SQLheader.h"
#include "addtostorage.h"
namespace Ui {
class Storage;
}

class Storage : public QDialog
{
    Q_OBJECT

public:
    explicit Storage(QWidget *parent = nullptr);
    void loadAll();
    ~Storage();

private slots:
    void on_searchBtn_clicked();

    void on_refreshBtn_clicked();

    void on_addBtn_clicked();

private:
    Ui::Storage *ui;
    QSqlQueryModel* model;
    addToStorage* addToStorage_ptr;
};

#endif // STORAGE_H
