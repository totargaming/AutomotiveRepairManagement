#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <QWidget>
#include <QListWidget>
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
    virtual void showInfo() = 0;
    virtual void idSort() = 0;
    virtual void nameSort() = 0;

    virtual ~EntityList();

  private slots:


    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_idSortBtn_clicked();

    void on_nameSortBtn_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

protected:
    Ui::EntityList *ui;
    QSqlDatabase database;
};

#endif // ENTITYLIST_H
