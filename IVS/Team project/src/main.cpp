/*==========================================================
 * Project Name: IVS-Projekt-
 * File Name: main.cpp
 * Date:  26.4.2021
 * Last update: 28.4.2021
 * Author:  xhusar11 Tomáš Husár
 *          xjesko01 Patrik Ješko
 *          xzalez01 Daniel Záležák
 *          xmakai00 Lucia Makaiová
 *
 * Description: file main.cpp conects GUI and math
 *              functions and runs application Calculator
 *
============================================================*/
/**
 * @file main.cpp
 *
 * @brief runs application Calculator
 * @author xhusar11 Tomáš Husár
 * @author xjesko01 Patrik Ješko
 * @author xzalez01 Daniel Záležák
 * @author xmakai00 Lucia Makaiová
 */

#include "calculator.h"

#include <QApplication>

#include "mathfunc.h"

#include <Windows.h>

void HideConsole()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

int main(int argc, char *argv[])
{
    HideConsole();
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    return a.exec();
}
