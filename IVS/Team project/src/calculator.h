/*==========================================================
 * Project Name: IVS-Projekt-
 * File Name: calculator.h
 * Date:  26.4.2021
 * Last update: 30.4.2021
 * Author:  xhusar11 Tomáš Husár
 *          xjesko01 Patrik Ješko
 *          xzalez01 Daniel Záležák
 *          xmakai00 Lucia Makaiová
 *
 * Description: header file for calculator.cpp
 *
============================================================*/
/**
 * @file calculator.h
 *
 * @brief header file for GUI file calculator.cpp
 * @author xhusar11 Tomáš Husár
 * @author xjesko01 Patrik Ješko
 * @author xzalez01 Daniel Záležák
 * @author xmakai00 Lucia Makaiová
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void NumButtonPressed();
    void MathButtonPressed();
    void EqButtonPressed();
    void NegationButtonPressed();
    void CEButtonPressed();
    void DelButtonPressed();
    void FloatingPointButtonPressed();
    void PiButtonPressed();
    void HelpButtonPressed();

};
#endif // CALCULATOR_H
