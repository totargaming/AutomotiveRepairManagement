#ifndef STAFF_H
#define STAFF_H
#include "entitylist.h"
#include "addtostaff.h"
#include "removefromstaff.h"
class Staff : public EntityList
{
public:
    Staff(QWidget *parent = nullptr);
    void add();
    void remove();
    void showInfo(const QModelIndex &index);

    void loadList();
    void idSort();
    void nameSort();
    ~Staff();
private:
    AddToStaff* addToStaff_ptr;
    RemoveFromStaff* removeFromStaff_ptr;
};

#endif // STAFF_H
