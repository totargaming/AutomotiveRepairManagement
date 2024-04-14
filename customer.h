#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "entitylist.h"
#include "removefromcustomer.h"
class Customer : public EntityList
{
    Q_OBJECT
public:
    Customer(QWidget *parent = nullptr);

    void add() override;
    void remove() override;
    void showInfo(const QModelIndex &index) override;

    void loadList() override;
    void idSort() override;
    void nameSort() override;
    ~Customer();
private:
    RemoveFromCustomer* removeFromCustomer_ptr;
};

#endif // CUSTOMER_H
