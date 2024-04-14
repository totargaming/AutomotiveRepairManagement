#ifndef STAFF_H
#define STAFF_H
#include "entitylist.h"
#include "addtostaff.h"
#include "removefromstaff.h"
class Staff : public EntityList
{
    Q_OBJECT
public:
    Staff(QWidget *parent = nullptr);
    void add() override;
    void remove() override;
    void showInfo(const QModelIndex &index) override;

    void loadList() override;
    void idSort() override;
    void nameSort() override;
    ~Staff();
private:
    AddToStaff* addToStaff_ptr;
    RemoveFromStaff* removeFromStaff_ptr;
};

#endif // STAFF_H
