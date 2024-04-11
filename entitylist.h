#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <QWidget>
#include <QTableWidget>
#include <SQLheader.h>
namespace Ui {
class EntityList;
}

class EntityList : public QWidget
{
    Q_OBJECT

public:
    explicit EntityList(QWidget *parent = nullptr);
    virtual void add() = 0 ;
    virtual void remove() = 0;
    virtual void showInfo(const QModelIndex &index) = 0;
    virtual void loadList() = 0;
    virtual void idSort() = 0;
    virtual void nameSort() = 0;
    virtual ~EntityList();

  private slots:


    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_idSortBtn_clicked();

    void on_nameSortBtn_clicked();


    void on_tableView_clicked(const QModelIndex &index);

protected:
    Ui::EntityList *ui;
    QSqlQueryModel* model;
};

#endif // ENTITYLIST_H
