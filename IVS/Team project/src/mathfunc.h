/*==========================================================
 * Project Name: IVS-Projekt-
 * File Name: mathfunc.h
 * Date:  26.4.2021
 * Last update: 26.4.2021
 * Autor:   xjesko01 Patrik Ješko
            xzalez01 Daniel Záležák
            xmakai00 Lucia Makaiová
 *
 * Description: file mathfunc.h, contains header file with
 *              difininitions of functions from mathfunc.cpp
 *
============================================================*/


/**
 * @file mathfunc.h
 *
 * @brief contains difininitions of functions from mathfunc.cpp
 *
 */



#ifndef MATHFUNC_H
#define MATHFUNC_H
#include <math.h>
#include <stdexcept>


/**
 * @defgroup Math Math functions
 * @brief MathFunc class all the math functions
 */


class MathFunc
{
public:
    /**
    * @brief Function calculates addition of two numbers
    * @ingroup Math
    * @param a first number of addition
    * @param b second number of addition
    * @return addition a + b
    * Function addition adds b to a and returns result
    */
    double addition(double a, double b);
    
    /**
    * @brief Function calculates subtraction of two numbers
    * @ingroup Math
    * @param a first number of subtraction
    * @param b second number of subtraction
    * @return subtraction a - b
    * Function subtraction subtracts b from a and returns result
    */
    double subtraction(double a, double b);

    /**
    * @brief Function calculates multiplication of two numbers
    * @ingroup Math
    * @param a first number of multiplication
    * @param b second number of multiplication
    * @return multiplication a * b
    * Function multiplication multiplies a by b and returns result
    */
    double multiplication(double a, double b);
    
    /**
    * @brief Function calculates division of two numbers
    * @ingroup Math
    * @param a first number of division
    * @param b second number of division
    * @return division a / b
    * Function division divides a by b and returns result
    * If b is 0 returns std runtim error
    */
    double division(double a, double b);

    /**
    * @brief Function calculates percentage of number
    * @ingroup Math
    * @param a number for which we want percentage
    * @param b number of 100%
    * @return percentage of a in b
    * Function percantage finds percentage of a in b and returns result
    */
    double percentage(double a, double b);
    
    /**
    * @brief Function calculates fraction number
    * @ingroup Math
    * @param a number for fraction
    * @return fraction 1 / a
    * Function fraction makes fraction of a and returns result
    */
    double fraction(double a);
    
    /**
    * @brief Function calculates power of a number
    * @ingroup Math
    * @param a base
    * @param b power
    * @return power a raised to the power of b
    * Function power calculates a raised to the power of b and returns result
    */
    double power(double a, double b);
    
    /**
    * @brief Function calculates a th root of b 
    * @ingroup Math
    * @param a a th root
    * @param b radicant
    * @return root a th root of b
    * Function root calculates a th root of b and returns result
    */
    double root(double a, double b);
    
    /**
    * @brief Function calculates factorial of number
    * @ingroup Math
    * @param a number for factorial
    * @return factorial a!
    * Function factorial calculates factorial of a and returns result
    */
    unsigned long long int factorial(long long int a);
    };

#endif
