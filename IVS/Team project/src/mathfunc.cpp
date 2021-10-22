/*==========================================================
 * Project Name: IVS-Projekt-
 * File Name: mathfunc.cpp
 * Date:  26.4.2021
 * Last update: 26.4.2021
 * Author:  xjesko01 Patrik Ješko
            xzalez01 Daniel Záležák
            xmakai00 Lucia Makaiová
 *
 * Description: file mathfunc.cpp, contains functions for
 *              application Calculator
 *
============================================================*/


/**
 * @file mathfunc.cpp
 *
 * @brief contains functions for application Calculator
 * @author xjesko01 Patrik Ješko
 * @author xzalez01 Daniel Záležák
 * @author xmakai00 Lucia Makaiová
 */

#include "mathfunc.h"
#include <iostream>
#include <windows.h>

double MathFunc::addition(double a, double b){
    return a + b;
}

double MathFunc::subtraction(double a, double b){
    return a - b;
}

double MathFunc::multiplication(double a, double b){
    return a * b;
}

double MathFunc::division(double a, double b){
    try{
        if(b != 0)
            return a / b;
        else
            throw std::runtime_error("Undefined\nCannot divide by 0");
    }
    catch(std::runtime_error e){
        std::cout << e.what() << std::endl;
        MessageBoxA(NULL, e.what(), "Error",MB_ICONWARNING );
        return 0;
    }

}

double MathFunc::percentage(double a, double b){
    if(b != 0)
        return a / b * 100;
    else
        return 0;
}

double MathFunc::fraction(double a){
    try{
        if(a != 0)
            return 1 / a;
        else
           throw std::runtime_error("Undefined\nCannot create unit fraction (division by 0)");
    }
    catch(std::runtime_error e){
        std::cout << e.what() << std::endl;
        MessageBoxA(NULL, e.what(), "Error",MB_ICONWARNING );
        return 0;
    }
}

double MathFunc::power(double a, double b){
    try{
        if(a == 0 && b == 0){
            throw std::runtime_error("Undefined\n");
        }
        if(b != 0)
            return pow(a,b);
        else
            return 1;
    }
    catch(std::runtime_error e){
        std::cout << e.what() << std::endl;
        MessageBoxA(NULL, e.what(), "Error",MB_ICONWARNING );
        return 0;
    }
}

double MathFunc::root(double a, double b){
    try{
        if(a == 0 && b == 0){
            throw std::runtime_error("Undefined\n");
        }
        if(a > 0 && b >= 0)
            return pow(b, 1/a);
        else
            throw std::runtime_error("Undefined\n");
    }
    catch(std::runtime_error e){
        std::cout << e.what() << std::endl;
        MessageBoxA(NULL, e.what(), "Error",MB_ICONWARNING );
        return 0;
    }

}

unsigned long long int MathFunc::factorial(long long int a){
    unsigned long long int ffactorial=0;
    try{
        if(a < 0){
            throw std::runtime_error("Undefined\nNumber cannot be negative");
        }
        else if(a == 0){
            return 1;
        }
        else{
            for(ffactorial = 1; a >= 1; a--){
                ffactorial *= a;
            }
            return ffactorial;
        }
    }
    catch(std::runtime_error e){
        std::cout << e.what() << std::endl;
        MessageBoxA(NULL, e.what(), "Error",MB_ICONWARNING );
        return 0;
    }
}

