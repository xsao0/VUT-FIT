/**
 * Projekt : Implementace prekladace imperativniho jazyka IFJ21
 * @file Parser.c
 * @author Juraj Hatala (xhatal01)
 * @brief Implementacia LL gramatiky
 *  
 */

#include "Parser.h"

#define PRINT_ON false //ak chces printovat priebeh nastav true ak nie nastav false

int Parse(ASTtree* abstractTree, symtable* mySymtable){
    int status = 0;
    
    Token* MyToken=(Token*)malloc(sizeof(Token));
    if (MyToken == NULL) return INTERNAL_ERROR;
    
    
    if (status != 0) return status;
    

    status = tokenScan(stdin, MyToken);
    if (status == LEXICAL_ERROR) return status; 

    RETURN_ON_ERROR(fc_program);
    return PARC_TRUE;
}
bool first(Token* MyToken, NonTerminal MyNonTerminal){
    if (MyNonTerminal==program){
        if(first(MyToken, code)){
            return true;
        }
    }
    else if (MyNonTerminal==code){
        if(first(MyToken, functionDec)){
            return true;
        }
        else if (first(MyToken,functionCall)){
            return true;
        }
        
    }
    else if (MyNonTerminal==functionDec){
        if (first(MyToken,global_scope)){
            return true;
        }
        else if(MyToken->type==Keyword){
            if(strcmp(MyToken->data.string, "function")==0){
                return true;
            }
        }
    }
    else if(MyNonTerminal==global_scope){
        if(MyToken->type==Keyword){
            if(strcmp(MyToken->data.string, "global")==0){
                return true;
            }
        }
    }
    else if(MyNonTerminal==function_iden){
        if(MyToken->type==Identifier){
            return true;
        }
    }
    else if(MyNonTerminal==params){
        if(first(MyToken, param)){
            return true;
        }
    }
    else if(MyNonTerminal==returnTypes){
        if (MyToken->type==Colon){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==nextType){
        if (MyToken->type==Comma){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==param){
        if (MyToken->type==Identifier){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==nextParam){
        if (MyToken->type==Comma){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==statement){
        if (first(MyToken, condition)){
            return true;
        }
        else if (first(MyToken, loop)){
            return true;
        }
        else if(first(MyToken, define)){
            return true;
        }
        else if (first(MyToken, assigneOrFunctioCall)){
            return true;
        }
        else if(first(MyToken, FCreturn)){
            return true;
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==condition){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"if")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else if(MyNonTerminal==loop){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"while")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
        
    }
    else if (MyNonTerminal==define){
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"local")==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else if (MyNonTerminal==assigneOrFunctioCall){
        if (first(MyToken,var)){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==varlist){
        if (first(MyToken,var)){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==var){
        if(MyToken->type==Identifier){
            return true;
        }
        else return false;
        
    }
    else if (MyNonTerminal == nextVar){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==expression)                             
    {
        if(MyToken->type==Identifier){
            return true;
        }
        else if(MyToken->type==Number){
            return true;
        }
        else if(MyToken->type==Integer){
            return true;
        }
        else if(MyToken->type==String){
            return true;
        }
        else if(MyToken->type==Sizeof){
            return true;
        }
        else if(MyToken->type==L_bracket){
            return true;
        }
        else if(MyToken->type==Keyword){
            if(strcmp(MyToken->data.string,"nil")==0) return true; 
            else return false;
        }
        else return false;
    }
    else if (MyNonTerminal == nextExpression){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal==functionCall)
    {
        if(MyToken->type==Identifier){
            return true;
        }
        else return false;
    }
    else if (MyNonTerminal == elseCondition)
    {
        if (MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"else")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if (MyNonTerminal == prolog)
    {
        if(MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"require")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if (MyNonTerminal == initialize)
    {
        if(first(MyToken, expression)){
            return true;
        }
    }
    else if(MyNonTerminal == FCallparams){
        if (first(MyToken,FCallparam)){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == FCallparam){
        if (first(MyToken, expression)){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == FCallnextParam){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;        
    }
    else if(MyNonTerminal == FCreturn){
        if(MyToken->type==Keyword){
            if (strcmp(MyToken->data.string,"return")==0){
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if(MyNonTerminal == returnParams){
        if (first(MyToken,FCallparam)){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == returnParam){
        if (first(MyToken, expression)){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == returnNextParam){
        if (MyToken->type==Comma){
            return true;
        }
        else return false;        
    }
    else if(MyNonTerminal == statementOutOfFc){
        if(first(MyToken, functionCall)){
            return true;
        }
        else if (first(MyToken,functionDec)){
            return true;
        }
        else return false;
    }
    else if(MyNonTerminal == defineEquals){
        if (MyToken->type == Assign){
            return true;
        }
    }

    return false;
}

int fc_program(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                  //program: <prolog><code>
    int status = 0;
    if(first(MyToken, prolog)){
        RETURN_ON_ERROR(fc_prolog);
    }
    if(first(MyToken, code)){
        RETURN_ON_ERROR(fc_code);
    }
    else return PARC_FALSE;
    
    return PARC_TRUE;
}
int fc_code(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                     //code: <functionDec><code><statement>
    int status = 0;
    if (first(MyToken, functionDec)){
        RETURN_ON_ERROR(fc_functionDec);
    }
    else if (MyToken->type==Identifier){
        RETURN_ON_ERROR_FCCALL(false);
    }
    else PARC_FALSE;

    if (first(MyToken, statementOutOfFc)){
        RETURN_ON_ERROR(fc_statementOutOfFc); 
    }
    
    return PARC_TRUE;
}
int fc_statementOutOfFc(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){        //statementOutOfFc: <functionDec>||<functionCall>(bez ids) <statementOutOfFc>
    int status = 0;
    if (first(MyToken, functionDec)){
        RETURN_ON_ERROR(fc_functionDec);
    }
    else if (MyToken->type==Identifier){
        RETURN_ON_ERROR_FCCALL(false);
    }
    else PARC_FALSE;

    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statementOutOfFc); 
    }
    
    return PARC_TRUE;
}
int fc_functionDec(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){              //functionDec: <global_scope>function<function_iden>(<params><returntypes>)<statement>end
    int status = 0;
    //vytvaranie AST
    status = ASTaddFCToTree(abstractTree->ASTStack);
    if (status != 0) return status;

    if (first(MyToken,global_scope)){
        RETURN_ON_ERROR(fc_global_scope);
    }

    if (chackStr(MyToken, "function")){
        parcerPrint("function" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if(first(MyToken, function_iden)){
        RETURN_ON_ERROR(fc_functionIden);
    }
    else return PARC_FALSE;

    if (MyToken->type==L_bracket){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, params)){
       RETURN_ON_ERROR(fc_params);
    }

    if (MyToken->type==R_bracket){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
      
    if(first(MyToken, returnTypes)){
        RETURN_ON_ERROR(fc_returnTypes);
    }
    
    if(first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }
    
    if (chackStr(MyToken, "end")){
        parcerPrint("function_def" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);

    return PARC_TRUE;
}
int fc_global_scope(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                   //global_scope: global
    int status = 0;
    if(chackStr(MyToken, "global")){
        parcerPrint("global" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    
    return PARC_TRUE;
}
int fc_functionIden(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                   //functionIden: <functionIden>
    int status = 0;
    if (MyToken->type==Identifier){
        status = ASTsaveToken(abstractTree->ASTStack, MyToken, functionID);//vytvaranie AST
        if(status != 0) return status;

        parcerPrint("function_Iden" ,MyToken ,PRINT_ON);
        status = sym_saveFun(&mySymtable->sym_globalTree,&mySymtable->sym_subTree, mySymtable->sym_stack,MyToken->data.string);//vytvaranie symtable
        if (status == INTERNAL_ERROR) return status;

        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }
    return PARC_TRUE;
}
int fc_params(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                         //params: <param><nextParam>
    int status = 0;
    if(first(MyToken, param)){
        RETURN_ON_ERROR(fc_param);
    }
    else{
        return PARC_FALSE;
    }

    if(first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_nextParam);
    }

    return PARC_TRUE;
}
int fc_param(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                          //param: <identifier>:<type>
    int status = 0;
    if(MyToken->type==Identifier){
        //uloz premennu do symtable
        sym_saveVar(&mySymtable->sym_subTree->tree, MyToken->data.string, &mySymtable->currentVar);
        //vytvaranie AST
        ASTsaveToken(abstractTree->ASTStack, MyToken, functionParams);
        parcerPrint("identifier" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }   
    else{
        return PARC_FALSE;
    }

    if (chackStr(MyToken,  ":")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    } 

    if(isTokenDataType(MyToken)){
        int status;
        sym_saveVarType(mySymtable->currentVar,MyToken->data.string);
        parcerPrint("param" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }

    return PARC_TRUE;
}
int fc_nextParam(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                      //nextparam: ,<param><nextparam>
    int status = 0;
    if (chackStr(MyToken, ",")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }     

    if (first(MyToken, param)){
        RETURN_ON_ERROR(fc_param);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_nextParam);
    }

    return PARC_TRUE;
}
int fc_returnTypes(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                      //returnTypes: :type<nextType>
    int status = 0;
    if (MyToken->type==Colon){
        parcerPrint("return_types start" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;     
    }
    else{
        return PARC_FALSE;
    } 

    if (isTokenDataType(MyToken)){
        status = ASTsaveToken(abstractTree->ASTStack, MyToken, functionReturnTypes);
        if (status != 0) return status;
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextType)){
        RETURN_ON_ERROR(fc_nextType);
    }
    
    return PARC_TRUE;
}
int fc_nextType(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                            //nextType: ,Type<nextType>
    int status = 0;
    if (chackStr(MyToken, ",")){
        parcerPrint("next_type" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (isTokenDataType(MyToken)){
        parcerPrint("type" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    
    }
    if (first(MyToken, nextType)){
        RETURN_ON_ERROR(fc_nextType);
    }

    return PARC_TRUE;
}
int fc_statement(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                              //statemnet: <<loop>||<condition>||<assigne>||<define>> <statment> 
    int status = 0;

    if (first(MyToken, loop)){
        RETURN_ON_ERROR(fc_loop);
    }
    else if (first(MyToken, condition)){
        RETURN_ON_ERROR(fc_condition);
        
    }
    else if (first(MyToken, assigneOrFunctioCall)){ 
        //ak je funkcia ries function call ak nie ries assigne
        if (isFunDeclared(MyToken->data.string, mySymtable->sym_globalTree, abstractTree)){   
            RETURN_ON_ERROR_FCCALL(false); 
        }
        else{ 
            RETURN_ON_ERROR(fc_assigne); 
        }
    }
    else if (first(MyToken, define)){
        RETURN_ON_ERROR(fc_define);
    }
    else if (first(MyToken, FCreturn)){
        RETURN_ON_ERROR(fc_FCreturn);
    }
    else return PARC_FALSE; 
    
    if (first(MyToken, statement)){
       RETURN_ON_ERROR(fc_statement);  
    }
    
    return PARC_TRUE;
}
int fc_loop(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                                    //loop: while<expression>do<statement>end
    int status = 0;

    //vytvaranie symtable
    symNewStackBlock(mySymtable->sym_stack,&mySymtable->sym_subTree); 
    //vytavaranie AST
    status = ASTaddCycleToTree(abstractTree->ASTStack);
    if (status != 0) return status;

    if (chackStr(MyToken, "while")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, "do")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }

    if (chackStr(MyToken, "end")){
        parcerPrint("loop" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);

    return PARC_TRUE;
}
int fc_condition(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                               //condition: if<expresion>then<statement><elseCondition>end
    int status = 0;
    
    //vytvaranie symtable
    symNewStackBlock(mySymtable->sym_stack,&mySymtable->sym_subTree); 
    //vytvaranie AST
    status = ASTaddConditionToTree(abstractTree->ASTStack);
    if (status != 0) return status;

    if (chackStr(MyToken, "if")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, "then")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }
        
    if(first(MyToken,elseCondition)){
        RETURN_ON_ERROR(fc_elseCondition);
    }

    if (chackStr(MyToken, "end")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);
    return PARC_TRUE;
}
int fc_elseCondition(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                               //else<statement>
    int status = 0;
    //vytvaranie symtable
    symNewStackBlock(mySymtable->sym_stack,&mySymtable->sym_subTree); 
    //vytvaranie AST
    status = ASTaddElseToCondition(abstractTree->ASTStack);

    if(status != 0) return status;

    if (chackStr(MyToken, "else")){
        parcerPrint("condition" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (first(MyToken, statement)){
        RETURN_ON_ERROR(fc_statement);
    }
    //vytvaranie symtable
    symDisposeStackBlock(mySymtable->sym_stack, &mySymtable->sym_subTree);
    return PARC_TRUE;
}
    
int fc_assigne(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                                      //<var><nextVar>=<expresion><nextExpresion>||<functionCall>
    int status = 0;
    bool assigneOrFCcall=0;//0 - asigne, 1 - FCcall
    
    //vytvaranie AST
    status = ASTaddAssigmentToTree(abstractTree->ASTStack);
    if(status != 0) return status;

    if (first(MyToken, var)){
        RETURN_ON_ERROR(fc_var);
    }
    else return PARC_FALSE;

    if (first(MyToken, nextVar)){
        RETURN_ON_ERROR(fc_nextVar);
    }
    
    if (MyToken->type==Assign){
        parcerPrint("assign" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;    
    }
    else return PARC_FALSE;

    if (first(MyToken, expression)){// or fccall + cash(Token** cash)ked sa rozhodne ci assigne alebo funkcia prida do vytvorenej struktury 
        if(MyToken->type==Identifier){
            if (isFunDeclared(MyToken->data.string, mySymtable->sym_globalTree, abstractTree)){   //ak je funkcia ries function call ak nie ries assigne
                
                ASTdeleteLastFromTree(abstractTree->ASTStack);//odstranim assigneLeaf zo stromu
                
                status = ASTswitchAssigneFCcall(abstractTree->ASTStack);//odstranim assigneLeaf zo stacku. Switch vytvori FCCall na stacku takze do fcCall posielam true aby dvakrat nevytvoril FCCall
                if (status != 0) return status;

                RETURN_ON_ERROR_FCCALL(true);
                assigneOrFCcall=1; 
            }
            else{
                RETURN_ON_ERROR(fc_expression);
            }
        }
        else{
            RETURN_ON_ERROR(fc_expression);
        }
    }
    else return PARC_FALSE;

    if (first(MyToken, nextExpression)){
        RETURN_ON_ERROR(fc_nextExpression);
    }
    
    //ak sa zavolal fccall tak ten sa sam odstrani zo zasobniku vo funkcii fc_functionCall
    if(!assigneOrFCcall) ASTendStatement(abstractTree->ASTStack);
    return PARC_TRUE;
}
int fc_var(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                                         //identifier
    int status = 0;
    if(MyToken->type==Identifier){
        if (!isVarDeclared(mySymtable->sym_stack, MyToken->data.string)) return SEMANTICAL_NODEFINITION_REDEFINITION_ERROR;//ak nie je premenna deklarovana vrat 3
        status = ASTaddToTokenArray(&(abstractTree->ASTStack->head->statement->TStatement.assignment->IDs), \
        abstractTree->ASTStack->head->statement->TStatement.assignment->nbID, MyToken);
        if (status != 0) return status;

        parcerPrint("var" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}
int fc_nextVar(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                                     //,<var><nextVar>
    int status = 0;
    if (chackStr(MyToken, ",")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,var)){
        RETURN_ON_ERROR(fc_var);
    }
    else return PARC_FALSE;
    
    if (first(MyToken,nextVar)){
        RETURN_ON_ERROR(fc_nextVar);
    }
    
    return PARC_TRUE;
}
int fc_expression(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                                  //expression: identifier||number||integer||string||sizeof||L_bracet
    int status = 0;
    
    //vyvor novy expression pre zapis do AST 
    Tree* newExpression=(Tree*)malloc(sizeof(Tree));
    if (newExpression == NULL) return INTERNAL_ERROR;

    parcerPrint("expression" ,MyToken ,PRINT_ON);
    //skontroluj expresion precedencnou analizov
    status=expressionCheck(MyToken, newExpression);
    if (status!=0) return status;

    status = isExpresionright(newExpression, mySymtable);
    if(status != 0) return status;

    //vloz expression do AST
    //musim rozlisovat aky typ statementu je na vrchu zasobniku
    if (abstractTree->ASTStack->head->statement->type==ASTcycle){
        *abstractTree->ASTStack->head->statement->TStatement.while_loop->expression=*newExpression;
    }
    else if (abstractTree->ASTStack->head->statement->type==ASTassigne){
        status = ASTaddToExpressions(&(abstractTree->ASTStack->head->statement->TStatement.assignment->expressions), \
                            abstractTree->ASTStack->head->statement->TStatement.assignment->nbexpressions, newExpression);
        if(status != 0) return status;
    }
    else if(abstractTree->ASTStack->head->statement->type==ASTcondition){
        *abstractTree->ASTStack->head->statement->TStatement.if_loop->expression=*newExpression;
    }
    else if (abstractTree->ASTStack->head->statement->type==ASTdefine){
        abstractTree->ASTStack->head->statement->TStatement.definiton->ExFc.expression=(Tree*)malloc(sizeof(Tree));//vo ExFc allokujem pamat pre expression
        if(abstractTree->ASTStack->head->statement->TStatement.definiton->ExFc.expression==NULL) return INTERNAL_ERROR;
        *abstractTree->ASTStack->head->statement->TStatement.definiton->state=Expression;//uloz info o tom ze define obsahuje espression
        *abstractTree->ASTStack->head->statement->TStatement.definiton->ExFc.expression=*newExpression;//uloz nove expression
    }
    else if(abstractTree->ASTStack->head->statement->type==ASTreturn){
        status = ASTaddToExpressions(&(abstractTree->ASTStack->head->statement->TStatement.FCreturn->expressions), \
                            abstractTree->ASTStack->head->statement->TStatement.FCreturn->nbexpressions, newExpression);
        if(status != 0) return status;
    }
    else if(abstractTree->ASTStack->head->statement->type==ASTfunctionCall){
        status = ASTaddToExpressions(&(abstractTree->ASTStack->head->statement->TStatement.functioncall->parameters), \
                            abstractTree->ASTStack->head->statement->TStatement.functioncall->nbParameters, newExpression);
        if(status != 0) return status;
    }

    return PARC_TRUE;
}
int fc_nextExpression(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                              //,<expresion><nextExpression>
    int status = 0;
    if (chackStr(MyToken, ",")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,expression)){
        RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;

    if (first(MyToken,nextExpression)){
        RETURN_ON_ERROR(fc_nextExpression);
    }
    
    return PARC_TRUE;
}
int fc_define(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                                        //define: local|identifier:type<inicialize>
    int status = 0;
    //vytvaranie AST
    status = ASTaddDefineToTree(abstractTree->ASTStack);//vytvaranie AST
    if(status != 0) return status;

    if (chackStr(MyToken, "local")){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (MyToken->type==Identifier){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        sym_saveVar(&mySymtable->sym_subTree->tree, MyToken->data.string, &mySymtable->currentVar);
        

        status = ASTsaveToken(abstractTree->ASTStack, MyToken, definitionID);
        if(status != 0) return status;

        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    if (chackStr(MyToken, ":")){
        parcerPrint("define" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }

    if(isTokenDataType(MyToken)){
        sym_saveVarType(mySymtable->currentVar, MyToken->data.string);
        parcerPrint("define" ,MyToken ,PRINT_ON);
        status = ASTsaveToken(abstractTree->ASTStack, MyToken, definitionDataType);
        if (status != 0)return status;
        
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,defineEquals)){
        RETURN_ON_ERROR(fc_defineEquals);
    }

    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    return PARC_TRUE;
}
int fc_defineEquals(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){
    int status = 0;
    if (chackStr(MyToken, "=")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,initialize)){
        RETURN_ON_ERROR(fc_initialize);
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}
int fc_functionCall(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree, bool withIDs){                                 //functionCall: identifier(<FCparams>)
    int status = 0;
    
    if (!withIDs){
        status = ASTaddFCcallToTree(abstractTree->ASTStack);
        if (status != 0) return status; 
    }
    if (MyToken->type==Identifier){
        abstractTree->ASTStack->head->statement->TStatement.functioncall->functionName->data.string = MyToken->data.string;
        parcerPrint("functionCall" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    
    if (chackStr(MyToken, "(")){
        
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;

    if (first(MyToken,FCallparams)){
        RETURN_ON_ERROR(fc_FCallparams);
    }
    
    if (chackStr(MyToken, ")")){
        parcerPrint("String" ,MyToken ,PRINT_ON);
        SCAN_TOKEN;
    }
    else return PARC_FALSE;
    
    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    return PARC_TRUE;
}
int fc_FCallparams(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                         //FCallparams: <FCallparam><FCallnextParam>
    int status = 0;
    if(first(MyToken, FCallparam)){
        RETURN_ON_ERROR(fc_FCallparam);
    }
    else{
        return PARC_FALSE;
    }
    if(first(MyToken, FCallnextParam)){
        RETURN_ON_ERROR(fc_FCallnextParam);
    }

    return PARC_TRUE;
}
int fc_FCallparam(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                          //FCallparam: <expression>
    int status = 0;
    if(first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }   
    else return PARC_FALSE;
    
    return PARC_TRUE;
}
int fc_FCallnextParam(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                      //FCallnextParam: ,<FCallparam><FCallnextparam>
    int status = 0;
    if (chackStr(MyToken, ",")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }     
    if (first(MyToken, FCallparam)){
        RETURN_ON_ERROR(fc_FCallparam);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_FCallnextParam);
    }

    return PARC_TRUE;
}
int fc_initialize(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                                  //initialize: =<expresion>||<functionCall>
    int status = 0;
    if (first(MyToken, expression)){                                               
        if(MyToken->type==Identifier){
            if(isFunDeclared(MyToken->data.string,mySymtable->sym_globalTree, abstractTree)){
                RETURN_ON_ERROR_FCCALL(false);
            }
            else RETURN_ON_ERROR(fc_expression);
        }
        else RETURN_ON_ERROR(fc_expression);
    }
    else return PARC_FALSE;
  
    return PARC_TRUE;
}

int fc_prolog(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){
    int status = 0;
    if (MyToken->type==Keyword){
        if (chackStr(MyToken, "require")){
            parcerPrint("Prolog" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    if (MyToken->type==String){
        if (chackStr(MyToken, "ifj21")){
            parcerPrint("Prolog" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    return PARC_TRUE;
}
int fc_FCreturn(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){          //FCreturn: return (<FCparams>)
    int status = 0;
    //vytvaranie AST
    status = ASTaddReturnToTree(abstractTree->ASTStack);

    if (MyToken->type==Keyword){
        if (chackStr(MyToken, "return")){
            parcerPrint("Return" ,MyToken ,PRINT_ON);
            SCAN_TOKEN;
        }
        else return PARC_FALSE;
    }
    else return PARC_FALSE;

    if (first(MyToken,returnParams)){
        RETURN_ON_ERROR(fc_returnParams);
    }

    //vytvaranie AST
    ASTendStatement(abstractTree->ASTStack);
    return PARC_TRUE;
}
int fc_returnParams(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                         //returnParams: <returnParam><returnNextParam>
    int status = 0;
    if(first(MyToken, returnParam)){
        RETURN_ON_ERROR(fc_returnParam);
    }
    else{
        return PARC_FALSE;
    }
    if(first(MyToken, returnNextParam)){
        RETURN_ON_ERROR(fc_returnNextParam);
    }

    return PARC_TRUE;
}
int fc_returnParam(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                          //returnParam: <expression>
    int status = 0;
    if(first(MyToken, expression)){
        RETURN_ON_ERROR(fc_expression);
    }   
    else return PARC_FALSE;
    
    return PARC_TRUE;
}
int fc_returnNextParam(Token* MyToken, symtable* mySymtable, ASTtree* abstractTree){                      //returnNextParam: ,<returnParam><returnNextParam>
    int status = 0;
    if (chackStr(MyToken, ",")){
        SCAN_TOKEN;
    }
    else{
        return PARC_FALSE;
    }     
    if (first(MyToken, FCallparam)){
        RETURN_ON_ERROR(fc_returnParam);
    }
    else{
        return PARC_FALSE;
    }

    if (first(MyToken, nextParam)){
        RETURN_ON_ERROR(fc_returnNextParam);
    }

    return PARC_TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chackType(Token* MyToken, Token_type checkType){    
    if (MyToken->type==checkType){
        int status = 0;
        SCAN_TOKEN;
        return PARC_TRUE;
    }
    else{
        return PARC_FALSE;
    }
}

bool compareTokenStr(Token* MyToken, char* Str){
    if((MyToken->type != Number) && (MyToken->type != Integer)){
        if(strcmp(MyToken->data.string, Str)==0){
            return true;
        }
    }
    return false;
}
bool chackStr(Token* MyToken, char* Str){
    if ((MyToken->type != Number) && (MyToken->type != Integer)){
        
        if (compareTokenStr(MyToken, Str)){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
bool isTokenDataType(Token* MyToken){
    if(compareTokenStr(MyToken, "integer")){
        return true;
    }
    else if(compareTokenStr(MyToken, "number")){
        return true;
    }
    else if(compareTokenStr(MyToken, "string")){
        return true;
    }
    else if(compareTokenStr(MyToken, "nil")){
        return true;
    }
    else
    {
        return false;
    }
}
void parcerPrint(char* state ,Token* MyToken ,bool on){
    if (on){
        if ( MyToken->type==Integer){
            printf("%s: %d\n",state,MyToken->data.integer);
        }
        else if (MyToken->type==Number){
            printf("%s: %f\n",state,MyToken->data.number);
        }
        else{
            if (strcmp(state,"loop")==0)
            {
                printf("\033[1;33m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"condition")==0){
                printf("\033[0;32m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"assign")==0){
                printf("\033[0;31m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else if (strcmp(state,"define")==0){
                printf("\033[0;34m");
                printf("%s: %s\n",state,MyToken->data.string);
                printf("\033[0m");
            }
            else
            {
                printf("%s: %s\n",state,MyToken->data.string);
            }
        }
    }
}
void printGlobalTree(symtable* mySymtable){
   printf("\nglobal tree:\n");
    sym_inorder(mySymtable->sym_globalTree); 
}
    
int global_level_function(Tstate *global){
    TFunction_tree *new_global = (TFunction_tree*)malloc(sizeof(TFunction_tree));
    if (new_global == NULL){
        return INTERNAL_ERROR;
    }
    global->TStatement.function = new_global;
    return PROGRAM_OK;
}
