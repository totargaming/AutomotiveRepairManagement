#ifndef TASKLIST_H
#define TASKLIST_H
#include "entitylist.h"
#include "addtotask.h"

#include <QDate>
class TaskList : public EntityList
{
    Q_OBJECT
public:
    TaskList(QWidget *parent = nullptr);

    void showInfo(const QModelIndex &index) override;
    void add() override;
    void loadList() override;
    void idSort() override;
    void nameSort() override;

    virtual QString taskType();
    void idSort(QString taskType);
    void nameSort(QString taskType);
    void loadList(QString taskType);

    virtual ~TaskList();

protected:
    AddToTask *addToTask_ptr;
};

#endif // TASKLIST_H
