
/**
 * Projekt : Implementace prekladace imperativniho jazyka IFJ21
 * @file symtable.h
 * @author Juraj Hatala (xhatal01)
 * @brief hlavickovy subor tabulky symbolov
 *  
 */


#ifndef symtable_h
#define symtable_h
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "AST.h"

typedef enum{
    function,
    variable
}leafType;

typedef enum{
    string,
    integer,
    number,
    nil
}DataType;

typedef struct {
    DataType varType;
}varData;

typedef struct {
    int varType;
    
}funData;

typedef struct tableItem {
    char* key;
    leafType type;
    struct tableItem *lptr;
    struct tableItem *rptr;
    struct sym_treeRoot *subtree;
    union{
        varData *VData;
        funData *Fdata;
    }ForV;
        
}TreeItem;

typedef struct sym_treeRoot{
    struct tableItem *tree;
    struct sym_treeRoot *lowerTree;
}SymTreeRoot;

typedef struct sym_stackElement{
    
    struct sym_stackElement *next;
    struct sym_treeRoot *root;
}SymStackElement;

typedef struct sym_stack{
    struct sym_stackElement* head;
}SymStack;

typedef struct sym_symtable{
    TreeItem *sym_globalTree;
    SymTreeRoot *sym_subTree;
    SymStack *sym_stack;
    TreeItem *currentVar;
}symtable;


// typedef struct tSymbolTable {
//     struct tableItem *root;
// } tSymbolTable;

//void tableInit(tSymbolTable *T);
/**
 * @brief vlozi item do zadaneho binarneho stromu podla kluca
 * 
 * @param tree 
 * @param key 
 * @param new 
 */
void bst_insert(TreeItem **tree, char* key, TreeItem *new);
/**
 * @brief inicializuje ukazatele v treeitem na NULL
 * 
 * @param treeitem 
 */
void TreeItemInit(TreeItem *treeitem);
/**
 * @brief zisti ci sa v strome nachadza prvok so zadanym klucom
 * 
 * @param tree 
 * @param key 
 * @return true 
 * @return false 
 */
bool sym_search(TreeItem *tree, char* key);
/**
 * @brief zahodi vrch zasobnika
 * 
 * @param myStack 
 */
void symStackPop(SymStack *myStack);  
/**
 * @brief vytvori novy element stacku a vlozi do neho zadany strom
 * 
 * @param myStack 
 * @param tree 
 * @return int
 *  
 */
int symStackPush(SymStack* myStack, SymTreeRoot* tree);
/**
 * @brief do zadaneho stromu vlozi vrch stacku
 * 
 * @param myStack 
 * @param tree 
 */
void symStackTop(SymStack* myStack, SymTreeRoot* tree);
/**
 * @brief inicializue head stacku na NULL
 * 
 * @param myStack 
 */
void symStackInit(SymStack* myStack);
/**
 * @brief allokuje pamet pre treeItem, treba kontrolovat chybu pri malloc 
 * 
 * @return TreeItem* 
 */
TreeItem* treeCreate();

/**
 * @brief ??!!
 * 
 * @param newTree 
 */
void sym_treeInit(TreeItem *newTree);

/**
 * @brief Vytvori novy item v global tree s kluco key a v novom iteme vytvori novy subtree a pushne ho na stack. Vonkajsi hlavny ukazatel subtree nastavi na novy subtree
 * 
 * @param sym_globalTree 
 * @param sym_subTree 
 * @param myStack 
 * @param key 
 * @return int 
 */
int sym_saveFun(TreeItem **sym_globalTree, SymTreeRoot **sym_subTree,SymStack* myStack, char* key);

/**
 * @brief Zisti ci sa v globalTree nachadza item s klucom key 
 * 
 * @param key 
 * @param globalTree 
 * @return true 
 * @return false 
 */
bool isFunDeclared(char* key, TreeItem* globalTree, ASTtree* abstractTree);

/**
 * @brief Vytvori novy item s klucom key a vlozi ho do current subtree
 * 
 * @param sym_subtree 
 * @param key 
 * @return int 
 */
int sym_saveVar(TreeItem **sym_subtree,char* key, TreeItem** currentVar);

/**
 * @brief ulozi do zadanej uzlu stomu typ danej premennej
 * 
 * @param data 
 * @param type 
 */
void sym_saveVarType(TreeItem* data, char* type);

/**
 * @brief zisti ci sa na stacku nachadza item s klucom key
 * 
 * @param myStack 
 * @param key 
 * @return true 
 * @return false 
 */
bool isVarDeclared(SymStack* myStack, char* key);

void sym_inorder(TreeItem *tree);

/**
 * @brief Vytvora novy block na stacku. Pri volani cyklov condition...
 * 
 * @param myStack 
 * @param sym_subTree 
 * @return int 
 */
int symNewStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree);

/**
 * @brief allokuje pamat pre treeRoot, treba kontrolovat chybu pri malloc
 * 
 * @return SymTreeRoot* 
 */
SymTreeRoot* treeCreateRoot();

/**
 * @brief ??!!!
 * 
 * @param myStack 
 * @param sym_subTree 
 * @return int 
 */
int symDisposeStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree);

/**
 * @brief Inicializuje symtable vytvori v nej stack, zvysne ukazatele nastavi na NULL 
 * 
 * @param sym 
 * @return int 
 */
int symtableInit(symtable* sym);

/**
 * @brief Zistuje ci je str jedna z inbuild funkcii
 * 
 * @param str 
 * @return true 
 * @return false 
 */
bool isInbuildFun(char* str);

/**
 * @brief Zist?? ??i je zadan?? identifik??tor inbuild funkcia ak ??no zaznamen?? do AST ze bola t??to funkcia v programe pou??it??
 * 
 * @param str 
 * @param abstractTree 
 * @return true 
 * @return false 
 */
bool ASTisInbuildFunSave(char* str, ASTtree* abstractTree);

/**
 * @brief ak je stack prazny vracia NULL;
 * 
 * @param myStack 
 * @return true 
 * @return false 
 */
bool symSatckIsEmpty(SymStack* myStack);

/**
 * @brief zisti ci sa premenna s klucom key nach??dza v nejakom stome na zasobn??ku ak nie vr??ti -1, ak ??no vracia enum DataType 
 * 
 * @param tree 
 * @param key 
 * @return int 
 */
int sym_searchVarType(TreeItem *tree, char* key);

/**
 * @brief prech??dza cel?? symtable a vypisuje na stdout
 * 
 * @param tree 
 */
void sym_inorderGlobal(TreeItem *tree);

/**
 * @brief vypisuje obsah z??sobn??ka na stdout
 * 
 * @param myStack 
 */
void printStack(SymStack *myStack);

/** 
 * @brief vracia typ premennej(enum) ak je ulozen?? na z??sobn??ku. Ak nie vracia -1. Vyu????va sym_searchVarType
 * 
 * @param myStack 
 * @param key 
 * @return int 
 */
int sym_varType(SymStack* myStack, char* key);

#endif