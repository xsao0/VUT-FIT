//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Daniel Zalezak <xzalez01@stud.fit.vutbr.cz>
// $Date:       $2021-03-11
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Daniel Zalezak
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include <iostream>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };

        for(int i = 0; i < 14; ++i)
            tree.InsertNode(values[i]);
    }
    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };

        for(int i = 0; i < 14; ++i)
            tree.InsertNode(values[i]);
    }
    BinaryTree tree;
};

// **********************************TESTY***********************************************

// EMPTY TREE
TEST_F(EmptyTree, InsertNode){
    auto result = tree.InsertNode(100);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second->key, 100);
    auto result2 = tree.InsertNode(100);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result2.second, result.second);

}

TEST_F(EmptyTree, DeleteNode){
   EXPECT_FALSE(tree.DeleteNode(0));
    int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };
    for(int i = 0; i < 14; ++i){
        EXPECT_FALSE(tree.DeleteNode(values[i]));
    }
}

TEST_F(EmptyTree, FindNode){
  EXPECT_TRUE(tree.FindNode(0) == NULL);
    int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };
    for(int i = 0; i < 14; ++i){
        EXPECT_TRUE(tree.FindNode(values[i])== NULL);
    }
}

// NON EMPTY TREE
TEST_F(NonEmptyTree, InsertNode){
    auto result = tree.InsertNode(100);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second->key, 100);
    auto result2 = tree.InsertNode(100);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result2.second, result2.second);

}
    
TEST_F(NonEmptyTree, DeleteNode){
    EXPECT_FALSE(tree.DeleteNode(0));
    int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };
    for(int i = 0; i < 14; ++i){
        EXPECT_TRUE(tree.DeleteNode(values[i]));
    }
}

TEST_F(NonEmptyTree, FindNode){
    EXPECT_TRUE(tree.FindNode(0) == NULL);
    int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };
    for(int i = 0; i < 14; ++i){
        auto result = tree.FindNode(values[i]);
        EXPECT_EQ( result->key, values[i]); 
    }      
}

// AXIOMY
TEST_F(TreeAxioms, Axiom1){             // Testuje ci su vsetky listove uzly cierne 
    std::vector<Node_t *> leaf {};
    tree.GetLeafNodes(leaf);
    for(auto node : leaf){
        EXPECT_EQ(node->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2){             // Testuje ci su obaja potomkovia cierny ak je uzol cerveny
    std::vector<Node_t *> Nodes {};
    tree.GetAllNodes(Nodes);
    for(auto node : Nodes){
        if(node->color == RED){
            ASSERT_TRUE(node->pLeft != NULL);
            EXPECT_EQ(node->pLeft->color, BLACK);
            ASSERT_TRUE(node->pRight != NULL);
            EXPECT_EQ(node->pRight->color , BLACK);
        }    
    }
}

TEST_F(TreeAxioms, Axiom3){             // Testuje ci kazda cesta od listoveho po koren obsahuje rovnkay pocet ciernych uzlov
    std::vector<Node_t *> leaf {};
    tree.GetLeafNodes(leaf);
    Node_t *Nodes;
    int Bl_Nodes = 0;
    int Bl_Nodes2 = -5; // pociatocna hodnota premennej musi byt zaporna aby sa v prvom for cykle nespustila podmienka 
    for(auto node : leaf){
        Bl_Nodes = 0;
        Nodes = node;
        while(Nodes->pParent != NULL){
            if(Nodes->color == BLACK){
                Bl_Nodes ++;
            }
            Nodes = Nodes->pParent;
        }
        if(Bl_Nodes2 != -5){
            EXPECT_EQ(Bl_Nodes, Bl_Nodes2);
        }
        Bl_Nodes2 = Bl_Nodes;
    }
}

/*** Konec souboru black_box_tests.cpp ***/