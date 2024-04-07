#ifndef CAR_H
#define CAR_H
#include "entitylist.h"

class Car : public EntityList
{
public:
     Car(QWidget *parent = nullptr);
    void add();
    void remove();
    void showInfo();
    void idSort();
    void nameSort();
     ~Car();
private:
};

#endif // CAR_H
