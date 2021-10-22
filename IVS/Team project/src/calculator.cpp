/*==========================================================
 * Project Name: IVS-Projekt-
 * File Name: calculator.cpp
 * Date:  26.4.2021
 * Last update: 29.4.2021
 * Author:  xhusar11 Tomáš Husár
 *          xjesko01 Patrik Ješko
 *          xzalez01 Daniel Záležák
 *          xmakai00 Lucia Makaiová
 *
 * Description: file calculator.cpp, contains  GUI made
 *              in Qt
 *
============================================================*/
/**
 * @file calculator.cpp
 *
 * @brief contains GUI for application Calculator
 * @author xhusar11 Tomáš Husár
 * @author xjesko01 Patrik Ješko
 * @author xzalez01 Daniel Záležák
 * @author xmakai00 Lucia Makaiová
 */

#include "calculator.h"
#include "./ui_calculator.h"
#include "mathfunc.h"
#include <QMessageBox>



double CalcVal = 0.0;
bool DivCheck = false;
bool MulCheck = false;
bool SubCheck = false;
bool AddCheck = false;
bool PerCheck = false;
bool FraCheck = false;
bool PowCheck = false;
bool FacCheck = false;
bool RooCheck = false;

bool FloatingPointCheck = false;

MathFunc Mathf;

double pi = 3.14159;

/**
 * @defgroup Qt Qt functions
 * @brief All functions in calculator.cpp
 */

/**
   * @brief Function handles pressed buttons.
   * @ingroup Qt
   * @param QWidget *parent
   * Function handles pressed buttons and calls specific
   * function to process the signal.
*/

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    //Chcem aby sa na displeji najprv zobrazovalo 0.0
    ui->Display->setText(QString::number(CalcVal));

    QPushButton *NumButtons[10];
    for(int i = 0; i < 10; ++i){
        QString buttonName = "Button" + QString::number(i);
        NumButtons[i] = Calculator::findChild<QPushButton *>(buttonName);

        //ked sa releasne button -> zavolam funkciu NumButtonPressed definovanu v headeri
        connect(NumButtons[i], SIGNAL(released()), this,
                SLOT(NumButtonPressed()));
    }
    connect(ui->ButtonPi, SIGNAL(released()), this,
            SLOT(NumButtonPressed()));
    connect(ui->ButtonAddition, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonSubtraction, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonDivision, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonMultiplication, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonPercent, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->pushButton_20, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->pushButton_22, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->pushButton_21, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonFactorial, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonEquals, SIGNAL(released()), this,
            SLOT(EqButtonPressed()));


    connect(ui->ButtonNegation, SIGNAL(released()), this,
            SLOT(NegationButtonPressed()));

    connect(ui->ButtonCE, SIGNAL(released()), this,
            SLOT(CEButtonPressed()));

    connect(ui->ButtonDel, SIGNAL(released()), this,
            SLOT(DelButtonPressed()));

    connect(ui->ButtonFloatingPoint, SIGNAL(released()), this,
            SLOT(FloatingPointButtonPressed()));

    connect(ui->ButtonPi, SIGNAL(released()), this,
                SLOT(PiButtonPressed()));

    connect(ui->ButtonHelp, SIGNAL(released()), this,
                SLOT(HelpButtonPressed()));

}
/**
   * @brief Calculator destructor
   * @ingroup Qt
   * @return void
*/
Calculator::~Calculator()
{
    delete ui;
}
/**
   * @brief Function handles numeric Buttons
   * @ingroup Qt
   * @return void
   * Function handles numeric butttons and displays
   * appropriate value on display.
*/
void Calculator::NumButtonPressed(){
    //sender returnne pointer na button ktory bol stlaceny
    QPushButton *button = (QPushButton *)sender();
    QString ButtonVal = button->text();
    QString DisplayVal = ui->Display->text();
    if(DisplayVal == "0"){
        ui->Display->setText(ButtonVal);
    } else {
        DisplayVal.append(ButtonVal);

        ui->Display->setText(DisplayVal);
    }
}
/**
   * @brief Function handles math Buttons
   * @ingroup Qt
   * @return void
   * Function sets math control bools, depending on
   * math Button pressed.
*/
void Calculator::MathButtonPressed(){
    DivCheck = false;
    MulCheck = false;
    SubCheck = false;
    AddCheck = false;
    PerCheck = false;
    FraCheck = false;
    PowCheck = false;
    FacCheck = false;
    RooCheck = false;
    FloatingPointCheck = false;

    QString DisplayVal = ui->Display->text();
    CalcVal = DisplayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString ButtonVal = button->text();
    if(QString::compare(ButtonVal, "÷", Qt::CaseInsensitive) == 0){
        DivCheck = true;
        ui->Display->setText("÷");
    } else if(QString::compare(ButtonVal, "×", Qt::CaseInsensitive) == 0){
        MulCheck = true;
        ui->Display->setText("×");
    }else if(QString::compare(ButtonVal, "−", Qt::CaseInsensitive) == 0){
        SubCheck = true;
        ui->Display->setText("−");
    }else if(QString::compare(ButtonVal, "+", Qt::CaseInsensitive) == 0){
        AddCheck = true;
        ui->Display->setText("+");
    }else if(QString::compare(ButtonVal, "%", Qt::CaseInsensitive) == 0){
        PerCheck = true;
        ui->Display->setText("%");
    }else if(QString::compare(ButtonVal, "1/x", Qt::CaseInsensitive) == 0){
        FraCheck = true;
        ui->Display->setText("1/x");
    }else if(QString::compare(ButtonVal, "^", Qt::CaseInsensitive) == 0){
        PowCheck = true;
        ui->Display->setText("^");
    }else if(QString::compare(ButtonVal, "!", Qt::CaseInsensitive) == 0){
        FacCheck = true;
        ui->Display->setText("!");
    }else if(QString::compare(ButtonVal, "√", Qt::CaseInsensitive) == 0){
        RooCheck = true;
        ui->Display->setText("√");
    }else if(QString::compare(ButtonVal, ".", Qt::CaseInsensitive) == 0){
        FloatingPointCheck = true;
    }

    ui->Display->setText("");
}

/**
   * @brief Function handles equals button.
   * @ingroup Qt
   * @return void
   * Function calls appropriate math function, based
   * on math button control bools configuration.
   */

void Calculator::EqButtonPressed(){
    double solution = 0.0;
    QString DisplayVal = ui->Display->text();
    double dblDisplayVal = DisplayVal.toDouble();
    if(AddCheck || SubCheck || MulCheck || DivCheck || PerCheck || FraCheck || PowCheck || FacCheck || RooCheck){
        if(AddCheck){
            solution = Mathf.addition(CalcVal, dblDisplayVal);
        } else if(SubCheck){
            solution = Mathf.subtraction(CalcVal, dblDisplayVal);
        } else if(MulCheck){
            solution = Mathf.multiplication(CalcVal, dblDisplayVal);
        } else if(DivCheck){
            solution = Mathf.division(CalcVal, dblDisplayVal);
        }else if(PerCheck){
            solution = Mathf.percentage(CalcVal, dblDisplayVal);
        }else if(FraCheck){
            solution = Mathf.fraction(CalcVal);
        }else if(PowCheck){
            solution = Mathf.power(CalcVal, dblDisplayVal);
        }else if(FacCheck){
            solution = Mathf.factorial(CalcVal);
        }else if(RooCheck){
            solution = Mathf.root(CalcVal, dblDisplayVal);
        }
        ui->Display->setText(QString::number(solution, 'g', 16));
        DivCheck = false;
        MulCheck = false;
        SubCheck = false;
        AddCheck = false;
    }
}
/**
   * @brief Function handles negation button.
   * @ingroup Qt
   * @return void
   * Function switches sign of a number.
   */
void Calculator::NegationButtonPressed(){
        QString DisplayVal = ui->Display->text();
        ui->Display->setText(QString::number(-DisplayVal.toDouble()));

}
/**
   * @brief Function handles CE button.
   * @ingroup Qt
   * @return void
   * Function erases whole input on display.
   */
void Calculator::CEButtonPressed(){
    CalcVal = 0.0;
    ui->Display->setText(QString::number(CalcVal));

}
/**
   * @brief Function handles Del button.
   * @ingroup Qt
   * @return void
   * Function deletes last input from display.
   */

void Calculator::DelButtonPressed(){

    QString DisplayVal = ui->Display->text();

    if(DisplayVal.size() > 0)  DisplayVal.resize(DisplayVal.size() - 1);

    ui->Display->setText(QString::number(DisplayVal.toDouble(),'g',40));

}
/**
   * @brief Function handles floating point button.
   * @ingroup Qt
   * @return void
   * Function processes string to floating point number
   * if it contains "."
   */

void Calculator::FloatingPointButtonPressed(){

    FloatingPointCheck = false;

    QString DisplayVal = ui->Display->text();

    //for na zistenie, ci sa nachadza floating point v stringu
    for(int i = 0; i < DisplayVal.size(); i++) {
        if( DisplayVal[i] == '.'){
            FloatingPointCheck = true;
        }
    }
    if(FloatingPointCheck != true){
       DisplayVal.append('.') ;

        ui->Display->setText(DisplayVal);
    } else{
        ui->Display->setText(QString::number(DisplayVal.toDouble()));
    }

}
/**
   * @brief Function handles pi button.
   * @ingroup Qt
   * @return void
   */

void Calculator::PiButtonPressed(){

        ui->Display->setText("");

        ui->Display->setText(QString::number(pi));
}
/**
   * @brief Function displays help.
   * @ingroup Qt
   * @return void
   * Function displays help dialog after help button is pressed.
   */

void Calculator::HelpButtonPressed(){
        QMessageBox::information(this,tr("Usage"),tr("Manual:\n\n"
    "-  ''0-9''   to input numbers on display\n"
    "-  ''.''        to input floating point\n"
    "-  ''CE''    to reset the value on the display\n"
    "-  ''Del''   to delete the last input\n"
    "-  ''%''     to get the y percentage value from x\n"
    "-  ''+''      to calculate addition (x+y)\n"
    "-  ''-''       to calculate substraction (x-y)\n"
    "-  ''*''       to calculate multiplication (x*y)\n"
    "-  ''/''       to calculate division (x/y)\n"
    "-  ''1/x''   to calculate unit fraction of a number\n"
    "-  ''√''      to calculate square root of (x^(1/y))\n"
    "-  ''^''      to calculate square of (x^y)\n"
    "-  ''!''       to calculate the factorial\n"
    "-  ''pi''     to input pi constant on the display\n"
    "-  ''=''      to calculate the result\n"
    "-  ''+/-''   to switch sign on the display\n"));
}
