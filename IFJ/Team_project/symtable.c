/**
 * Projekt : Implementace prekladace imperativniho jazyka IFJ21
 * @file symtable.c
 * @author Juraj Hatala (xhatal01)
 * @brief implementacia tabulky symbolov
 *
 */

#include "symtable.h"
#include <stdio.h>
#include <stdbool.h>
void bst_insert(TreeItem **tree, char* key, TreeItem *new){ 
  if ((*tree) == NULL){
    new->key = key;
    (*tree) = new;
  }
  else{
    if (strcmp(key, (*tree)->key)<0){
      bst_insert(&((*tree)->lptr), key, new);
    }
    else{
      if (strcmp(key, (*tree)->key)>0){
        bst_insert(&((*tree)->rptr), key, new);
      }
    }  
  }
}
void TreeItemInit(TreeItem *treeitem){
  treeitem->key = NULL;
  treeitem->lptr = NULL;
  treeitem->rptr = NULL;
  treeitem->subtree = NULL;
  if (treeitem->type==function){
    treeitem->ForV.Fdata = (funData*)malloc(sizeof(funData));
  }
  else if (treeitem->type==variable){
    treeitem->ForV.VData = (varData*)malloc(sizeof(varData));;
  }  
}
bool sym_search(TreeItem *tree, char* key) {
  if (tree == NULL){
    return false;
  }
  else{
    if (strcmp(key, tree->key)==0){
      return true;
    }
    else{
      if (strcmp(key, tree->key)<0){
        return sym_search(tree->lptr, key);
      }
      else{
        return sym_search(tree->rptr, key);
      }
    }
  }
  return false;
}
int sym_searchVarType(TreeItem *tree, char* key) {
  if (tree == NULL){
    return -1;
  }
  else{
    if (strcmp(key, tree->key)==0){
      return tree->ForV.VData->varType;
    }
    else{
      if (strcmp(key, tree->key)<0){
        return sym_searchVarType(tree->lptr, key);
      }
      else{
        return sym_searchVarType(tree->rptr, key);
      }
    }
  }
  return -1;
}
void symStackPop(SymStack *myStack){
    SymStackElement* tmp;
    if (myStack->head!=NULL){
        tmp=myStack->head;
        myStack->head=tmp->next;
        free(tmp);
    }
}
int symStackPush(SymStack* myStack, SymTreeRoot* tree){
    SymStackElement* newSymbol=(SymStackElement*)malloc(sizeof(SymStackElement));
    if (newSymbol==NULL) return INTERNAL_ERROR;
    
    newSymbol->root=tree;
    newSymbol->next=NULL;
    if (myStack->head!=NULL){
        newSymbol->next=myStack->head;
        myStack->head=newSymbol;
    }
    else{
        myStack->head=newSymbol;
    }
    return 0;
}
void printStack(SymStack *myStack){
  SymStackElement *tmp=myStack->head;
  printf("Stack:");
  while (tmp!=NULL)
  {
    if(tmp->root->tree!=NULL) printf(" %s |",tmp->root->tree->key);
    tmp=tmp->next;
  }
  printf("\n");
}
void symStackTop(SymStack* myStack, SymTreeRoot* tree){
    if (myStack->head!=NULL){
        tree=myStack->head->root;
    }
}
void symStackInit(SymStack* myStack){
  myStack->head=NULL;
}
TreeItem* treeCreate(){
    TreeItem* newTree=(TreeItem*)malloc(sizeof(TreeItem));
    if(newTree==NULL){
        return NULL;
    }
    sym_treeInit(newTree);
    return newTree;
}
SymTreeRoot* treeCreateRoot(){
    SymTreeRoot* newRoot=(SymTreeRoot*)malloc(sizeof(SymTreeRoot));
    if(newRoot==NULL){
        return NULL;
    }
    newRoot->tree=NULL;
    newRoot->lowerTree=NULL;
    return newRoot;
}
void sym_treeInit(TreeItem *newTree){
    newTree=NULL;
}
int sym_saveFun(TreeItem **sym_globalTree, SymTreeRoot **sym_subTree, SymStack* myStack, char* key){
  funData* data=(funData*)malloc(sizeof(funData));                    //vytvor data
  data->varType=0;
  
  TreeItem *newItem = (TreeItem*)malloc(sizeof(TreeItem));          //vytvor novy item
  if(newItem==NULL) return INTERNAL_ERROR;
  TreeItemInit(newItem);
  
  newItem->subtree=treeCreateRoot();                                //vytvor na newitem vetvu pre subtree
  if (newItem->subtree==NULL) return INTERNAL_ERROR;
  //newItem->subtree->tree==NULL;                                     //koren musi ukazovat na null
  
  *sym_subTree=newItem->subtree;                                    //vonkajsi ukazatel ukazuje na posledno vytvoreny subtree 
  symStackPush(myStack, newItem->subtree);                          //pushni na symstack
  
  *newItem->ForV.Fdata=*data;                                       //neviem ci treba kopirovat 
  bst_insert(sym_globalTree, key, newItem);                       //vloz item do global tree
  return 0;
}
int sym_saveVar(TreeItem **sym_subtree,char* key, TreeItem** currentVar){
  varData* data=(varData*)malloc(sizeof(varData));                    //vytvor data
  data->varType=1;
  
  TreeItem *newItem = (TreeItem*)malloc(sizeof(TreeItem));          //vytvor novy item
  if(newItem==NULL) return INTERNAL_ERROR;
  TreeItemInit(newItem);
  *newItem->ForV.VData=*data;
  *currentVar=newItem;

  bst_insert(sym_subtree, key, newItem);                   //vloz do current subtree
  return 0;
}
void sym_saveVarType(TreeItem* data, char* type){
  if(strcmp(type,"string")==0){
    data->ForV.VData->varType=string;
  }
  else if(strcmp(type,"integer")==0){
    data->ForV.VData->varType=integer;
  } 
  else if(strcmp(type,"number")==0){
    data->ForV.VData->varType=number;
  }
  else if(strcmp(type,"nil")==0){
    data->ForV.VData->varType=nil;
  }
}
/**
 * @brief Vypise zadany strom inorder na stdout
 *  
 * @param tree 
 */
void sym_inorder(TreeItem *tree) {
  if (tree != NULL){
    sym_inorder(tree->lptr);
    printf("    %s :", tree->key);
    if (tree->ForV.VData->varType==0){
      printf(" string\n");
    }
    else if (tree->ForV.VData->varType==1){
      printf(" integer\n");
    }
    else if (tree->ForV.VData->varType==2){
      printf(" number\n");
    }
    else if (tree->ForV.VData->varType==3){
      printf(" nil\n");
    }
    
    sym_inorder(tree->rptr);
  }
}
void sym_inorderGlobal(TreeItem *tree){
  if (tree != NULL){
    sym_inorderGlobal(tree->lptr);

    if (tree->subtree!=NULL){
      SymTreeRoot* tmp=tree->subtree;
      printf("%s\n", tree->key);
      int nb=0;
      while (tmp!=NULL)
      {
        nb++;
        printf("  %d Block:\n",nb);
        sym_inorder(tmp->tree);
        tmp=tmp->lowerTree;
      }
    }

    sym_inorderGlobal(tree->rptr);
  }
}
bool isFunDeclared(char* key, TreeItem* globalTree, ASTtree* abstractTree){
  if(sym_search(globalTree, key) || ASTisInbuildFunSave(key, abstractTree)){
    return true;
  }
  return false;
}
bool isVarDeclared(SymStack* myStack, char* key){
  SymStackElement* tmp=myStack->head;
  while(tmp!=NULL){
    if(sym_search(tmp->root->tree, key)) return true;
    tmp=tmp->next;
  }
  return false;
}
int sym_varType(SymStack* myStack, char* key){
  SymStackElement* tmp=myStack->head;
  int Milan=-1;
  while(tmp!=NULL){
    Milan=sym_searchVarType(tmp->root->tree, key);
    if(Milan!=-1) return Milan;
    tmp=tmp->next;
  }
  return -1;
}
int symNewStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree){
  SymTreeRoot* newRoot = treeCreateRoot();
  if(newRoot==NULL) return INTERNAL_ERROR;
  if (symSatckIsEmpty){                    //uloz do predosleho subtree ako ukazatel na dalsii subtree
    myStack->head->root->lowerTree=newRoot;
  }
  
  symStackPush(myStack, newRoot);           //uloz na vrch stacku a
  *sym_subTree= newRoot;                    //zmen current subTree na novy tree
  return 0;
}
int symDisposeStackBlock(SymStack* myStack, SymTreeRoot **sym_subTree){ //odstran vrch stacku a zmen ukazatel na subtree
  if (myStack->head!=NULL){
    SymStackElement* tmp=myStack->head;
    myStack->head=myStack->head->next;
    if(myStack->head!=NULL) *sym_subTree=myStack->head->root;//myStack->head->root;
  }
  return 0;  
} 
int symtableInit(symtable* sym){
  SymStack *symstack=(SymStack*)malloc(sizeof(SymStack));
  if(symstack==NULL) return INTERNAL_ERROR;
  symStackInit(symstack);
  sym->sym_stack=symstack;
  sym->sym_globalTree=NULL;
  sym->currentVar=NULL;
  return 0;
}
bool ASTisInbuildFunSave(char* str, ASTtree* abstractTree){
  if(strcmp(str,"write")==0) {ASTinBuildUsed(abstractTree, write); return true;}
  else if(strcmp(str,"readi")==0){ASTinBuildUsed(abstractTree, readi); return true;}
  else if(strcmp(str,"reads")==0){ASTinBuildUsed(abstractTree, reads); return true;}
  else if(strcmp(str,"readn")==0){ASTinBuildUsed(abstractTree, readn); return true;}
  else if(strcmp(str,"tointeger")==0){ASTinBuildUsed(abstractTree, tointeger); return true;}
  else if(strcmp(str,"substr")==0){ASTinBuildUsed(abstractTree, substr); return true;}
  else if(strcmp(str,"ord")==0){ASTinBuildUsed(abstractTree, ord); return true;}
  else if(strcmp(str,"chr")==0){ASTinBuildUsed(abstractTree, chr); return true;}
  else return false;
}
bool isInbuildFun(char* str){
  if ((strcmp(str,"write")==0) || (strcmp(str,"readi")==0) || (strcmp(str,"reads")==0) || \
      (strcmp(str,"readn")==0) || (strcmp(str,"tointeger")==0) || (strcmp(str,"substr")==0) || \
      (strcmp(str,"ord")==0) || (strcmp(str,"chr")==0)) return true;
  else return false;
}
bool symSatckIsEmpty(SymStack* myStack){
  if(myStack->head==NULL) return true;
  else return false;
}