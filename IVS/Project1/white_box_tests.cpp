//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Daniel Zalezak <xzalez01@stud.fit.vutbr.cz>
// $Date:       $2021-03-11
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Daniel Zalezak
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class Matrix_1x1 : public ::testing::Test
{
protected:
    Matrix m{};
};

TEST(MatrixTests, MatrixConstructor){
    Matrix x{};
    EXPECT_EQ(x.get(0, 0), 0);
    Matrix x2{3, 3};
    EXPECT_ANY_THROW(Matrix(0,1));
    EXPECT_ANY_THROW(Matrix(1,0));
    
}

TEST(MatrixTests, MatrixSet_MatrixGet){
    Matrix x {3,3};
    Matrix v {3,3};
    EXPECT_TRUE(x.set(3,3,5));
    EXPECT_FALSE(x.set(4,3,5));
    EXPECT_FALSE(x.set(3,4,5));
    EXPECT_ANY_THROW(x.get(4,3));
    EXPECT_ANY_THROW(x.get(3,4));
    EXPECT_TRUE(x.set({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}));
    EXPECT_FALSE(x.set({{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}));
    
}

TEST(MatrixTests, MatrixOperators){
    Matrix x1{};
    Matrix x2{};
    Matrix x3{3,3};
    Matrix x4{3,3};
    x1.set(0,0,2);
    // +
    Matrix x = x1 + x2;
    ASSERT_EQ(x.get(0, 0), 2);
    EXPECT_ANY_THROW(x = x1 + x3);
    // =
    EXPECT_ANY_THROW(x1 == x3);
    EXPECT_TRUE(x1 == x2);
    EXPECT_TRUE(x1 == x1);
    // *
    EXPECT_TRUE(x1*x2 == x2);
    EXPECT_ANY_THROW(x1*x3 == x1);
    EXPECT_EQ(x1*2, x1);
}

TEST(MatrixTests, OtherTests){
    Matrix x1{3,3};
    Matrix x2{4,4};
    Matrix x3{4,3};
    std::vector<double> v1 = {1,2,3};
    std::vector<double> v2 = {};
    std::vector<double> v3 = {8,9,10,11};
    std::vector<double> result1 = {4,5,6};
    std::vector<double> result2 = {};
    std::vector<double> result3 = {4,5,6,7};
    EXPECT_TRUE(x1.solveEquation(v1) == result1 );
    
    
}



/*** Konec souboru white_box_tests.cpp ***/
