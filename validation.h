// Use an include guard to prevent multiple inclusions of this header file
#ifndef VALIDATION_H
#define VALIDATION_H

// Include the QDebug header file for debugging output
#include <QDebug>

// Declare the Validation class
class Validation
{
public:
    // Constructor for the Validation class
    Validation();

    // Declare a pure virtual function for validating user input
    // This makes Validation an abstract base class, which cannot be instantiated
    // Derived classes must override this function
    virtual bool validateUserInput() = 0;
};

// End of the include guard
#endif // VALIDATION_H