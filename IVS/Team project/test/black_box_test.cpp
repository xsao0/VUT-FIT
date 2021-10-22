/*==========================================================
 * Project Name: IVS-Projekt-
 * File Name: black_box_test.cpp
 * Date:  26.4.2021
 * Last update: 29.4.2021
 * Autor:   xjesko01 Patrik Ješko 
 *      
 * Description: file black_box_test.cpp, contains tests of
 *              functions in mathfunc.cpp
 * 
============================================================*/


/**
 * @file black_box_test.cpp
 * 
 * @brief contains tests of functions in mathfunc.cpp
 * 
 */


#include "gtest/gtest.h"
#include "mathfunc.h"

class CalculatorTest: public ::testing::Test
{
    protected:
        MathFunc calc;
};


TEST_F(CalculatorTest, Addition)        //Addition (+) 
{
    EXPECT_EQ(calc.addition(10.8, 5.3), 16.1);
    EXPECT_EQ(calc.addition(10050, 10000), 20050);
    EXPECT_EQ(calc.addition(2500, 50000), 52500);
    EXPECT_EQ(calc.addition(50, -50), 0);
    EXPECT_EQ(calc.addition(-50, 150), 100);
    EXPECT_EQ(calc.addition(-984, -4247), -5231);
}

TEST_F(CalculatorTest, Subtraction)     //Subtraction (-)
{
    EXPECT_EQ(calc.subtraction(10.8, 5.3), 10.8-5.3);
    EXPECT_EQ(calc.subtraction(10050, 10000), 50);
    EXPECT_EQ(calc.subtraction(2500, 50000), -47500);
    EXPECT_EQ(calc.subtraction(50, -50), 100);
    EXPECT_EQ(calc.subtraction(-50, 150), -200);
    EXPECT_EQ(calc.subtraction(-984, -4247), 3263);
}

TEST_F(CalculatorTest, Multiplication)  //Multiplication (*)
{
    EXPECT_EQ(calc.multiplication(10.8, 5.3), 57.24);
    EXPECT_EQ(calc.multiplication(10050, 0), 0);
    EXPECT_EQ(calc.multiplication(0, 50000), 0);
    EXPECT_EQ(calc.multiplication(50, -50), -2500);
    EXPECT_EQ(calc.multiplication(-100, 35), -3500);
    EXPECT_EQ(calc.multiplication(-43, -25.3), 1087.9);
    EXPECT_EQ(calc.multiplication(10, 5), 50);

}

TEST_F(CalculatorTest, Division)        //Division (/)
{
    EXPECT_EQ(calc.division(154, 7), 22);
    EXPECT_EQ(calc.division(-64, 5), -12.8);
    EXPECT_EQ(calc.division(643, -8), -80.375);
    EXPECT_EQ(calc.division(-553, -7), 79);
    EXPECT_EQ(calc.division(0, 43), 0);

    for(int i = -1000; i < 1000; i++)
    {
        EXPECT_ANY_THROW(calc.division(i, 0));
    }
}

TEST_F(CalculatorTest, Power)          //Power
{
    for(int i = 1; i < 101; ++i)
    {
        EXPECT_EQ(calc.power(i, 0), 1);
        EXPECT_EQ(calc.power(0, i), 0);    
    }

    EXPECT_EQ(calc.power(-154, 7), pow(-154, 7));
    EXPECT_EQ(calc.power(-11, 2), pow(-11, 2));
    EXPECT_EQ(calc.power(-3, 10), pow(-3, 10));

    EXPECT_EQ(calc.power(114, -7), pow(114, -7));
    EXPECT_EQ(calc.power(5, -3), pow(5, -3));

    EXPECT_EQ(calc.power(154, 7), pow(154, 7));

    EXPECT_ANY_THROW(calc.power(0, 0));
}

TEST_F(CalculatorTest, Root)           //Root
{
    //EXPECT_EQ(calc.root(10, 584), 1.89078);
    EXPECT_EQ(calc.root(2.5, 34), pow(34, 1/2.5));
    EXPECT_EQ(calc.root(3, 8), 2);
    EXPECT_EQ(calc.root(2, 9), 3);

    EXPECT_ANY_THROW(calc.root(-5, 4));
    EXPECT_ANY_THROW(calc.root(0, 0));
}

TEST_F(CalculatorTest, Percentage)          //Percentage (%)
{
    EXPECT_EQ(calc.percentage(10, 100), 10);
    EXPECT_EQ(calc.percentage(2.5, 80), 3.125);
}

TEST_F(CalculatorTest, Fraction)          //Fraction (1/x)
{
    for (int i = 1; i < 100; ++i)
    {
        EXPECT_EQ(calc.fraction(i), 1/double(i));
    }
    EXPECT_ANY_THROW(calc.fraction(0));
}

TEST_F(CalculatorTest, Factorial)       //Factorial (!)
{
    for (int i = 1; i < 100; i++)
    {
        long long int x = 1;
        for (int j = i; j >= 1; j--)
        {
            x *= j;
        }
        EXPECT_EQ(calc.factorial(i), x);
    }

    EXPECT_EQ(calc.factorial(0), 1);

    for(int i = -100; i < 0; i++)
    {
        EXPECT_ANY_THROW(calc.factorial(i));
    }

    EXPECT_EQ(calc.factorial(2.5), 2);
    EXPECT_EQ(calc.factorial(5.9), 120);
}
