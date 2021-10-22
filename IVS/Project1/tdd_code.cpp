//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Daniel Zalezak <xzalez01@stud.fit.vutbr.cz>
// $Date:       $2021-03-11
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Daniel Zalezak
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Element_t *e = GetHead();
    while( e != NULL){
        Element_t *x = e;
        e = e->pNext;
        delete x;
    }
}

void PriorityQueue::Insert(int value)
{ 
    bool f = false; // f - pomocna premenna , sluzi na to ak sa splni 1 podmienka aby sa dalsie nesplnili
    // prida prvok do prazdnej fronty
    if(m_pHead == NULL && f == false){
        m_pHead = new Element_t{
           .pNext = NULL,
           .pPrev = NULL,
           .value = value
        };
        f = true;
    }
    // prida prvok na zaciatok fronty
    if(m_pHead != NULL && m_pHead->value < value && f == false){  
        Element_t *x;   //x - pomocna premenna
        x = m_pHead; 
        m_pHead = new Element_t{
            .pNext = x,
            .pPrev = NULL,
            .value = value
        };
        m_pHead->pNext->pPrev = m_pHead;
        f = true; 
    }

    // prida prvok na koniec fronty
    if(m_pHead != NULL && f == false){
        Element_t *e = m_pHead; //pomocna premenna
        while(e->pNext != NULL){
            e = e->pNext;
        }
        if(e->value > value){
            e->pNext = new Element_t{
                .pNext = NULL,
                .pPrev = e,
                .value = value
            }; 
            f = true;
        }
    }
    //prida prvok medzi prvok s vacsou hodnotou a prvok s mensou hodnotou
    if(m_pHead->pNext != NULL && f == false ){
        for(Element_t *e= m_pHead; e != NULL; e = e->pNext){ // e - pomocna premenna
            if(e->value > value && e->pNext->value <= value){
                Element_t *p;   // p - pomocna premenna
                p = new Element_t{
                    .pNext = e->pNext,
                    .pPrev = e,
                    .value = value    
                };
                e->pNext->pPrev= p;
                e->pNext = p; 
                f = true;
            }
        }
    }
}


bool PriorityQueue::Remove(int value)
{
    Element_t *eFind = Find(value);
    if(eFind != NULL){
        if(eFind->pPrev == NULL && eFind->pNext != NULL){
            eFind->pNext->pPrev = NULL;
            m_pHead = eFind->pNext;
        }
        else if(eFind->pPrev != NULL && eFind->pNext == NULL){
            eFind->pPrev->pNext = NULL;
        }
        else if(eFind->pPrev != NULL && eFind->pNext != NULL){
            eFind->pPrev->pNext = eFind->pNext;
            eFind->pNext->pPrev = eFind->pPrev;
        }
        else if(eFind->pPrev == NULL && eFind->pNext == NULL){
            m_pHead = NULL;
        }
        return true;
    }
    else{
        return false;
    }
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{   
    if(m_pHead != NULL){
        for(Element_t*e = m_pHead; e != NULL; e = e->pNext){  // e - pomocna premenna
            if(e->value == value){
                return e;
            }
        }  
    }
    return NULL;
}

size_t PriorityQueue::Length()
{   
    if(m_pHead != NULL){
        int a = 0;
        for(Element_t*e = m_pHead; e != NULL; e = e->pNext){    // e - pomocna premenna
            a++;     
        }  
        return a;
    }
    else{
        return 0;
    }
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead; // vracia ukazatel na prvu polozku fronty
}

/*** Konec souboru tdd_code.cpp ***/
