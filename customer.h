#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "entitylist.h"
#include "removefromcustomer.h"
class Customer : public EntityList
{
public:
    Customer(QWidget *parent = nullptr);

    void add();
    void remove();
    void showInfo(const QModelIndex &index);

    void loadList();
    void idSort();
    void nameSort();
    ~Customer();
private:
    RemoveFromCustomer* removeFromCustomer_ptr;
};

#endif // CUSTOMER_H
