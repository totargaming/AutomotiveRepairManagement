#ifndef VALIDATION_H
#define VALIDATION_H
#include <QDebug>
class Validation
{
public:
    Validation();
    virtual bool validateUserInput() = 0;
};

#endif // VALIDATION_H
