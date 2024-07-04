# Automotive Repair Management System

The Automotive Repair Management System is a robust application developed using the QT framework and SQLite. It is designed to optimize the management of a vehicle warehouse by providing a comprehensive suite of features.

## Features

**Vehicle Database**: This feature allows users to add, view, and remove vehicles from the database. Each vehicle record includes details such as model, brand, condition, and associated metadata for tracking the vehicle maintenance workflow.

**Maintenance Schedule**: Users can create and manage a maintenance schedule for each vehicle. This schedule aids in planning regular maintenance tasks, ensuring that all vehicles are kept in optimal condition.

**Parts Inventory**: This feature enables users to manage an inventory of all spare parts available in the warehouse. It helps in quickly identifying the availability of a part when a vehicle needs repair.

**Task Assignment**: Users can assign tasks to warehouse staff. For instance, if a vehicle needs to be moved or repaired, the user can assign this task to a staff member and track its progress.

**User and Staff Database**: The system uses SQLite to store and manipulate data, simplifying the process of adding, removing, or storing data about the vehicle owners and staff.

The primary goal of this application is to enhance the efficiency of vehicle management in the warehouse by providing a tool that aids in maintaining a well-organized and smoothly running vehicle warehouse.

## User Guide

To use the application, follow the steps below:

1. Open the QT terminal.
2. If there is no MakeFile yet and you want to generate one, use the following command:
```bash
C:\Qt\6.6.2\mingw_64\bin\qmake.exe D:\AutomotiveRepairManagement\AutomotiveRepairManagement.pro -spec win32-g++ "CONFIG+=debug"
```
3. If there is a MakeFile and some changes have been made, use the following command:
```bash
C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe -f D:/AutomotiveRepairManagement/Makefile qmake_all
```
4. To build the project, use the following command:
```bash
C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe -j12
```
Please note that the paths used in the commands should be replaced with the actual paths on your system. Enjoy using the Automotive Repair Management System!
