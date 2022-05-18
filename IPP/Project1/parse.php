<?php
ini_set('display_errors','stderr');
echo('<?xml version="1.0" encoding="UTF-8"?>')."\n";
$header = false;


if($argc > 1){
    if($argv[2] == "--help"){
        echo("Usage:");
        exit(0);
    }
    else{
        //TODO
    }
}
$inst_counter = 0;
while($line = fgets(STDIN)){
    $head = ".IPPcode22";
    $line = preg_replace('!\s+!', ' ', trim($line, "\n"));
    $singleword = explode(' ', trim($line, "\n"));
    $num_of_strings = count($singleword);
    for($i = 0; $i < $num_of_strings; $i++){
        $hashtag = '#';
        if(strpos($singleword[$i], $hashtag) !== false){
            $new_singleword = explode('#', $singleword[$i]);
            $singleword[$i] = $new_singleword[0];
            if($singleword[$i]===''){
                array_splice($singleword, $i);
            }
            else{
                array_splice($singleword, $i+1);
            }
            break;
        }
    }
    if(count($singleword) == 0){
        continue;
    }
    if(!$header){
        $line = str_replace(' ','', $line);
        $line = preg_replace("/#[a-zA-Z_%!?&*$0-9\-@\/]*/",'', $line);
        if(strcmp(trim($line, "\n"), $head) == 0){
            $header = true;
            echo('<program language="IPPcode22">')."\n";
            continue;
        }
        else if($line == "\n" || $line[0] === '#'){
            continue;
        }
        else{
            fwrite(STDERR, 'Error: Missing header'."\n");
            exit(21);
        };
    }
    if($header && strcmp($line, $head) == 0 ){
        fwrite(STDERR, 'Error: Unknown or incorrect code'."\n");
        exit(22);
    }
    
    $singleword[0] = strtoupper($singleword[0]);
    switch($singleword[0]){
        case 'CREATEFRAME':
        case 'PUSHFRAME':
        case 'POPFRAME':
        case 'RETURN':
        case 'BREAK':
            $inst_counter++;
            
            if(count($singleword) != 1){
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23);
            }
            else{
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n"."\t"."</instruction>"."\n");
            }
            
            
            break;
        case 'DEFVAR':
        case 'POPS':
            if(count($singleword) == 2){
                $inst_counter++;
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n");
                if(preg_match("/^(LF|GF|TF)@[a-zA-Z_%!?&*$\-][a-zA-Z_%!?&*$0-9\-]*/", $singleword[1])){
                    $singleword[1] = str_replace("&", "&amp;", $singleword[1]);
                    $singleword[1] = str_replace("<", "&lt;", $singleword[1]);
                    $singleword[1] = str_replace(">", "&gt;", $singleword[1]);
                    echo("\t\t".'<arg1 type="var">'.$singleword[1]."</arg1>"."\n"."\t"."</instruction>"."\n");
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
            }
            else{
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23);
            }
            break;
        case 'CALL':
        case 'LABEL':
        case 'JUMP':
            $inst_counter++;
            if(count($singleword) == 2){
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n");
                if(preg_match("/^[a-zA-Z_%!?&*$\-][a-zA-Z_%!?&*$0-9\-]*/", $singleword[1]) && strpos($singleword[1], '@') === false){
                    $singleword[1] = str_replace("&", "&amp;", $singleword[1]);
                    $singleword[1] = str_replace("<", "&lt;", $singleword[1]);
                    $singleword[1] = str_replace(">", "&gt;", $singleword[1]);
                    echo("\t\t".'<arg1 type="label">'.$singleword[1]."</arg1>"."\n"."\t"."</instruction>"."\n");
                } 
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
            }
            else{
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23); 
            }
            
            break;
        case 'PUSHS':
        case 'DPRINT':
        case 'WRITE':
        case 'EXIT':
            $inst_counter++;
            if(count($singleword) == 2){
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n");
                $symb = explode('@', $singleword[1]);
                if(preg_match("/^[a-zA-Z]*/", $symb[0])){
                    switch($symb[0]){
                        case 'string':
                            $symb[1] = str_replace("&", "&amp;", $symb[1]);
                            $symb[1] = str_replace("<", "&lt;", $symb[1]);
                            $symb[1] = str_replace(">", "&gt;", $symb[1]);
                            if(preg_match("/\\\\$|\\\\\d$|\\\\\d\d$|\\\\\D+|\\\\\d\D+|\\\\\d\d\D+/", $symb[1])){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23); 
                            }
                            else{
                                echo("\t\t"."<arg1 type=\"".$symb[0]."\">".$symb[1]."</arg1>"."\n"."\t"."</instruction>"."\n");
                            }
                            break;
                        case 'int':
                            if(strcmp($symb[1], '')==0){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);  
                            }
                            else{
                                echo("\t\t"."<arg1 type=\"".$symb[0]."\">".$symb[1]."</arg1>"."\n"."\t"."</instruction>"."\n");  
                            }
                            break;
                        case 'bool':
                            if($symb[1]!== 'false' && $symb[1]!== 'true'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg1 type=\"".$symb[0]."\">".$symb[1]."</arg1>"."\n"."\t"."</instruction>"."\n");
                            }
                            
                            break;
                        case 'nil':
                            if($symb[1]!== 'nil'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg1 type=\"".$symb[0]."\">".$symb[1]."</arg1>"."\n"."\t"."</instruction>"."\n");
                            }
                            
                            break;
                        case 'GF':
                        case 'LF':
                        case 'TF':
                            $singleword[1] = str_replace("&", "&amp;", $singleword[1]);
                            $singleword[1] = str_replace("<", "&lt;", $singleword[1]);
                            $singleword[1] = str_replace(">", "&gt;", $singleword[1]);
                            echo("\t\t".'<arg1 type="var">'.$singleword[1]."</arg1>"."\n"."\t"."</instruction>"."\n");
                            break;
                        default:
                            fwrite(STDERR, 'Syntax Error'."\n");
                            exit(23);
                    }
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
            }
            else{
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23);
            }
            break;
        
        case 'STRLEN':
        case 'MOVE':
        case 'TYPE':
        case 'INT2CHAR':
        case 'NOT':
            if(count($singleword) == 3){
                $inst_counter++;
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n");
                if(preg_match("/^(LF|GF|TF)@[a-zA-Z_%!?&*$\-][a-zA-Z_%!?&*$0-9\-]*/", $singleword[1])){
                    $singleword[1] = str_replace("&", "&amp;", $singleword[1]);
                    $singleword[1] = str_replace("<", "&lt;", $singleword[1]);
                    $singleword[1] = str_replace(">", "&gt;", $singleword[1]);
                    echo("\t\t".'<arg1 type="var">'.$singleword[1]."</arg1>"."\n");
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
                $symb = explode('@', $singleword[2]);
                if(preg_match("/^[a-zA-Z]*/", $symb[0])){
                    switch($symb[0]){
                        case 'string':
                            $symb[1] = str_replace("&", "&amp", $symb[1]);
                            $symb[1] = str_replace("<", "&lt", $symb[1]);
                            $symb[1] = str_replace(">", "&gt", $symb[1]);
                            if(preg_match("/\\\\$|\\\\\d$|\\\\\d\d$|\\\\\D+|\\\\\d\D+|\\\\\d\d\D+/", $symb[1])){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23); 
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n"."\t"."</instruction>"."\n");
                            }
                            break;
                        case 'int':
                            if(strcmp($symb[1], '')==0){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);  
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n"."\t"."</instruction>"."\n");  
                            }
                            break;
                        case 'bool':
                            if($symb[1]!== 'false' && $symb[1]!== 'true'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n"."\t"."</instruction>"."\n");
                            }
                            break;
                        case 'nil':
                            if($symb[1]!== 'nil'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n"."\t"."</instruction>"."\n");
                            }
                            
                            break;
                        case 'GF':
                        case 'LF':
                        case 'TF':
                            $singleword[2] = str_replace("&", "&amp;", $singleword[2]);
                            $singleword[2] = str_replace("<", "&lt;", $singleword[2]);
                            $singleword[2] = str_replace(">", "&gt;", $singleword[2]);
                            echo("\t\t".'<arg2 type="var">'.$singleword[2]."</arg2>"."\n"."\t"."</instruction>"."\n");
                            break;
                        default:
                            fwrite(STDERR, 'Syntax Error'."\n");
                            exit(23);
                    }
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
            }
            else{
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23); 
            }
            break;
        
        case 'READ':
            if(count($singleword) == 3){
                $inst_counter++;
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n");
                if(preg_match("/^(LF|GF|TF)@[a-zA-Z_%!?&*$\-][a-zA-Z_%!?&*$0-9\-]*/", $singleword[1])){
                    $singleword[1] = str_replace("&", "&amp;", $singleword[1]);
                    $singleword[1] = str_replace("<", "&lt;", $singleword[1]);
                    $singleword[1] = str_replace(">", "&gt;", $singleword[1]);
                    echo("\t\t".'<arg1 type="var">'.$singleword[1]."</arg1>"."\n");
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
                
                if(preg_match("/^[a-zA-Z]*/", $singleword[2]) && strpos($singleword[2], '@') === false){
                    switch($singleword[2]){
                        case 'string':
                        case 'int':
                        case 'bool':
                            echo("\t\t".'<arg2 type="type">'.$singleword[2]."</arg2>"."\n"."\t"."</instruction>"."\n");
                        break;
                        default:
                            fwrite(STDERR, 'Syntax Error'."\n");
                            exit(23);
                    }
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
            }
            else{
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23);
            }
            break;
        case 'ADD':
        case 'SUB':
        case 'MUL':
        case 'IDIV':
        case 'LT':
        case 'GT':
        case 'EQ':
        case 'AND':
        case 'OR':
        case 'STRI2INT':
        case 'CONCAT':
        case 'GETCHAR':
        case 'SETCHAR':
            $inst_counter++;
            if(count($singleword) == 4){
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n");
                if(preg_match("/^(LF|GF|TF)@[a-zA-Z_%!?&*$\-][a-zA-Z_%!?&*$0-9\-]*/", $singleword[1])){
                    $singleword[1] = str_replace("&", "&amp;", $singleword[1]);
                    $singleword[1] = str_replace("<", "&lt;", $singleword[1]);
                    $singleword[1] = str_replace(">", "&gt;", $singleword[1]);
                    echo("\t\t".'<arg1 type="var">'.$singleword[1]."</arg1>"."\n");
                }
                else{
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
                $symb = explode('@', $singleword[2]);
                if(preg_match("/^[a-zA-Z]*/", $symb[0]) && $symb[1] !== ''){
                    switch($symb[0]){
                        case 'string':
                            $symb[1] = str_replace("&", "&amp", $symb[1]);
                            $symb[1] = str_replace("<", "&lt", $symb[1]);
                            $symb[1] = str_replace(">", "&gt", $symb[1]);
                            if(preg_match("/\\\\$|\\\\\d$|\\\\\d\d$|\\\\\D+|\\\\\d\D+|\\\\\d\d\D+/", $symb[1])){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23); 
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");
                            }
                            break;
                        case 'int':
                            if(strcmp($symb[1], '')==0){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);  
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");  
                            }
                            break;    
                        case 'bool':
                            if($symb[1]!== 'false' && $symb[1]!== 'true'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");
                            }
                            break;
                        case 'nil':
                            if($symb[1]!== 'nil'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");
                            }
                            
                            break;
                        case 'GF':
                        case 'LF':
                        case 'TF':
                            echo("\t\t".'<arg2 type="var">'.$singleword[2]."</arg2>"."\n");
                            break;
                        default:
                            fwrite(STDERR, 'Syntax Error'."\n");
                            exit(23);
                    }
                }
                else  {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
                $symb2 = explode('@', $singleword[3]);
                if(preg_match("/^[a-zA-Z]*/", $symb2[0]) && $symb[1] !== ''){
                    switch($symb2[0]){
                        case 'string':
                            $symb2[1] = str_replace("&", "&amp", $symb2[1]);
                            $symb2[1] = str_replace("<", "&lt", $symb2[1]);
                            $symb2[1] = str_replace(">", "&gt", $symb2[1]);
                            if(preg_match("/\\\\$|\\\\\d$|\\\\\d\d$|\\\\\D+|\\\\\d\D+|\\\\\d\d\D+/", $symb2[1])){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23); 
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            }
                            break;
                        case 'int':
                            if(strcmp($symb2[1], '')==0){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);  
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");  
                            }
                            break;
                        case 'bool':
                            if($symb2[1]!== 'false' && $symb2[1]!== 'true'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            }
                            break;
                        case 'nil':
                            if($symb2[1]!== 'nil'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            }
                            
                            break;
                        case 'GF':
                        case 'LF':
                        case 'TF':
                            $singleword[3] = str_replace("&", "&amp;", $singleword[3]);
                            $singleword[3] = str_replace("<", "&lt;", $singleword[3]);
                            $singleword[3] = str_replace(">", "&gt;", $singleword[3]);
                            echo("\t\t".'<arg3 type="var">'.$singleword[3]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            break;
                        default:
                            fwrite(STDERR, 'Syntax Error'."\n");
                            exit(23);
                    }
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
            }
            else{
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23);
            }
            break;
 
        case 'JUMPIFEQ':
        case 'JUMPIFNEQ':
            $inst_counter++;
            if(count($singleword) == 4){
                echo("\t".'<instruction order="'.$inst_counter.'" opcode="'.$singleword[0].'">'."\n");
                if(preg_match("/^[a-zA-Z_%!?&*$\-][a-zA-Z_%!?&*$0-9\-]*/", $singleword[1])  && strpos($singleword[1], '@') === false){
                    $singleword[1] = str_replace("&", "&amp;", $singleword[1]);
                    $singleword[1] = str_replace("<", "&lt;", $singleword[1]);
                    $singleword[1] = str_replace(">", "&gt;", $singleword[1]);
                    echo("\t\t".'<arg1 type="label">'.$singleword[1]."</arg1>"."\n");
                } 
                
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
                $symb = explode('@', $singleword[2]);
                if(preg_match("/^[a-zA-Z]*/", $symb[0]) && $symb[1] !== ''){
                    switch($symb[0]){
                        case 'string':
                            $symb[1] = str_replace("&", "&amp", $symb[1]);
                            $symb[1] = str_replace("<", "&lt", $symb[1]);
                            $symb[1] = str_replace(">", "&gt", $symb[1]);
                            if(preg_match("/\\\\$|\\\\\d$|\\\\\d\d$|\\\\\D+|\\\\\d\D+|\\\\\d\d\D+/", $symb[1])){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23); 
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");
                            }
                            break;
                        case 'int':
                            if(strcmp($symb[1], '')==0){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);  
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");  
                            }
                            break;
                        case 'bool':
                            if($symb[1]!== 'false' && $symb[1]!== 'true'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");
                            }
                            break;
                        case 'nil':
                            if($symb[1]!== 'nil'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg2 type=\"".$symb[0]."\">".$symb[1]."</arg2>"."\n");
                            }
                            
                            break;
                        case 'GF':
                        case 'LF':
                        case 'TF':
                            $singleword[2] = str_replace("&", "&amp;", $singleword[2]);
                            $singleword[2] = str_replace("<", "&lt;", $singleword[2]);
                            $singleword[2] = str_replace(">", "&gt;", $singleword[2]);
                            echo("\t\t".'<arg2 type="var">'.$singleword[2]."</arg2>"."\n");
                            break;
                        default:
                            fwrite(STDERR, 'Syntax Error'."\n");
                            exit(23);
                    }
                }
                else  {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                }
                $symb2 = explode('@', $singleword[3]);
                if(preg_match("/^[a-zA-Z]*/", $symb2[0]) && $symb[1] !== ''){
                    switch($symb2[0]){
                        case 'string':
                            $symb2[1] = str_replace("&", "&amp", $symb2[1]);
                            $symb2[1] = str_replace("<", "&lt", $symb2[1]);
                            $symb2[1] = str_replace(">", "&gt", $symb2[1]);
                            if(preg_match("/\\\\$|\\\\\d$|\\\\\d\d$|\\\\\D+|\\\\\d\D+|\\\\\d\d\D+/", $symb2[1])){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23); 
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            }
                            break;
                        case 'int':
                            if(strcmp($symb2[1], '')==0){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);  
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");  
                            }
                            break;
                        case 'bool':
                            if($symb2[1]!== 'false' && $symb2[1]!== 'true'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            }
                            break;
                        case 'nil':
                            if($symb2[1]!== 'nil'){
                                fwrite(STDERR, 'Syntax Error'."\n");
                                exit(23);
                            }
                            else{
                                echo("\t\t"."<arg3 type=\"".$symb2[0]."\">".$symb2[1]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            }
                            
                            break;
                        case 'GF':
                        case 'LF':
                        case 'TF':
                            $singleword[3] = str_replace("&", "&amp;", $singleword[3]);
                            $singleword[3] = str_replace("<", "&lt;", $singleword[3]);
                            $singleword[3] = str_replace(">", "&gt;", $singleword[3]);
                            echo("\t\t".'<arg3 type="var">'.$singleword[3]."</arg3>"."\n"."\t"."</instruction>"."\n");
                            break;
                        default:
                            fwrite(STDERR, 'Syntax Error'."\n");
                            exit(23);
                    }
                }
                else {
                    fwrite(STDERR, 'Syntax Error'."\n");
                    exit(23);
                } 
            }
            else{
                fwrite(STDERR, 'Syntax Error'."\n");
                exit(23); 
            }
            break;
        case '':
            break;
        default:
            fwrite(STDERR, 'Error: Unknown or incorrect code'."\n");
            exit(22);
    }
    
}
echo("</program>"."\n");
?> 