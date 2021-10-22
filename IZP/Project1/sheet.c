#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 
#define row_len 10243

void delimet(char *array, char *delimeter, char change );
void drow(char *argum[], int num_row, char *bufferr, int b);
void drows(char *argum[], int num_row, char *bufferr, int b);
void irow(char *argum[], int num_row, int b, int num_del1, char *del1);
void acol(char *bufferr, char *del1);
int delim_count(char*bufferr, char *del1);
void icol(char *argum[], char *bufferr, char *del1, int b);
void dcol(char *argum[], char *bufferr, char *del1, int b);
void dcols(char *argum[], char*bufferr, char *del1, int b);
void arow(int num_del1, char *del1);
void cset(char *argum[],char *bufferr, char *del1, int b);
void tolower_(char *argum[], char *bufferr,char *del1, int b);
void toupper_(char *argum[], char *bufferr,char *del1, int b);
void int_(char *argum[],char *bufferr, char *del1, int b);
void copy(char* argum[], char*bufferr, char *del1, int b);
void swap(char* argum[], char*bufferr, char *del1, int b);
void rows(char* argum[], char*bufferr, char*del1, int b, int k1);

int main(int argc, char *argv[]){
    char *delim = " ";
    if(argc>2){
        if(strcmp(argv[1], "-d")==0){
            delim = argv[2];
        }   
    } 

    char buffer[row_len];

    int k=0; //pocet riadkov
    int num_del;
    while (fgets(buffer,row_len, stdin)!= NULL){
        k++;
        
        delimet(buffer, delim, delim[0]);
        for(int a=1 ;a <argc;a++){
            num_del= delim_count(buffer,delim);
            if(!strcmp(argv[a],"acol")){
                acol(buffer,delim);
            }
            if(!strcmp(argv[a],"drow")){
                drow(argv,k,buffer,a); 
            }
            if(!strcmp(argv[a],"drows")){
                drows(argv,k,buffer,a);
            } 
             if(!strcmp(argv[a],"icol")){
                icol(argv,buffer,delim,a);
            }
            if(!strcmp(argv[a],"irow")){
                irow(argv,k,a,num_del,delim);
            } 
            if(!strcmp(argv[a],"dcol")){
                dcol(argv, buffer, delim, a);
            }
            if(!strcmp(argv[a],"dcols")){
                dcols(argv,buffer,delim,a);
            }
            if(!strcmp(argv[a],"rows")){
                rows(argv,buffer,delim,a,k);
            }
            /*if(!strcmp(argv[a],"cset")){                     funkcie su zahrnute vo funkcii rows
                cset(argv,buffer,delim,a);
            }
            if(!strcmp(argv[a],"tolower")){
                tolower_(argv,buffer,delim,a);
            }
            if(!strcmp(argv[a],"toupper")){
                toupper_(argv,buffer,delim,a);
            }
            if(!strcmp(argv[a],"int")){
                int_(argv,buffer,delim,a);
            }
            if(!strcmp(argv[a],"copy")){
                copy(argv,buffer,delim,a);
            }
            if(!strcmp(argv[a],"swap")){
                swap(argv,buffer,delim,a);
            }*/
        } 
        printf("%s",buffer);
    }
    for(int a=1 ;a <argc;a++){
        if(!strcmp(argv[a],"arow")){
            arow(num_del,delim);
        }
    }
    
    return 0;
} 

void drow(char *argum[], int num_row, char *bufferr, int b){
    char *trash;
    int n = strtol(argum[b+1], &trash, 10); 
        if(trash[0]!=0){
            fprintf(stderr, "Wrong argument\n");
        }
        else{
            if(num_row == n){
                char arr[1]="\0";
                strcpy(bufferr,arr);
            }
        }      
}

void drows(char *argum[], int num_row, char *bufferr, int b){
    char *trash;
    char *trash2;
    int n = strtol(argum[b+1],&trash, 10);
    int m = strtol(argum[b+2],&trash2, 10);
    if(trash[0]!=0 || trash2[0]!=0){
        fprintf(stderr, "Wrong argument\n");
    }
    else{
        while(n<=m){
            if(num_row==n){   
                char arr[1]="\0";
                strcpy(bufferr,arr); 
            }
            n++;
        }
    }     
}

void irow(char *argum[], int num_row, int b, int num_del1, char *del1){
    char *trash;
    int n = strtol(argum[b+1], &trash,10);
    if(trash[0]!=0){
        fprintf(stderr, "Wrong argument\n");    
    }
    else{
        if(num_row==n){
            int i=1;
            while(i<num_del1){
                printf("%s", del1);
                i++;
            }
            if(i==num_del1){
                printf("%s\n", del1);
            }
        }    
    }
    
}

void acol(char *bufferr, char *del1){
    int last_ch = strlen(bufferr)-3;
    int new_last_ch = last_ch+1;
    memmove(bufferr + new_last_ch, bufferr+last_ch, 4);
    bufferr[new_last_ch] = del1[0];
    
}

void icol(char *argum[], char *bufferr, char *del1, int b){
    char *trash;
    int c = strtol(argum[b+1], &trash, 10);
    int p = c-1;
    int num_del1 = 0;
    int x;
    if(trash[0]!=0){
        fprintf(stderr, "Wrong argument\n");
    }
    else{
        for(int i=0; bufferr[i]!='\0';i++){
            if(bufferr[i]== del1[0]){
                if(num_del1 <p){
                    num_del1++;
                    x=i;     
                } 
            }
        }
        int o = x+1;
        int r = x;
        int q = strlen(bufferr)-r-2;
        memmove(bufferr+o, bufferr+r, q);
        bufferr[r]= del1[0];
    }
       
}   

void dcol(char *argum[], char *bufferr, char *del1, int b){
    char *trash;
    int c = strtol(argum[b+1],&trash,10);
    int num_del1 =0;
    int x;
    int y;
    int num_del2 = delim_count(bufferr, del1);
    if(trash[0]!=0){
        fprintf(stderr, "Wrong argument\n");    
    }
    else{
        for(int i =0; bufferr[i]!='\0';i++){
            if(bufferr[i]==del1[0]){
                if(num_del1 < c ){
                    x=i;
                    num_del1++;

                    if(num_del1== c-1 ){
                        y = i;
                    }
                }
            } 
        }
        if(c==1){
            y= -1;
        }
        if(c>num_del2){
            x=strlen(bufferr)-2;
            y=y-1; 
        } 
        int r = x+1;
        int o = y+1;
        int q =strlen(bufferr)-r;
        int n=strlen(bufferr) - (r-o);
        memmove(bufferr+o, bufferr+r, abs(q));
        bufferr[n]='\0';
    }
      
}

void dcols(char *argum[], char*bufferr, char *del1, int b){
    char *trash;
    char *trash2;
    int m = strtol(argum[b+1],&trash, 10);
    int n = strtol(argum[b+2],&trash2, 10);
    int x,y;
    int num_del1=0;
    int num_del2 = delim_count(bufferr, del1);
    if(trash[0]!=0 || trash2[0]!=0){
        fprintf(stderr, "Wrong argument\n");
    }
    else{
        if(m<=n){
            for(int i =0; bufferr[i]!='\0';i++){
                if(bufferr[i]==del1[0]){
                    if(num_del1<n){
                        num_del1++;
                        x=i;
                        if(num_del1==m-1){
                            y=i;
                        }
                    }
                }    
            }
        }
        if(m==1){
            y=-1;
        }
        if(n>num_del2){
            x=strlen(bufferr)-2;
        }
        int r = x+1;
        int o = y+1;
        int q =strlen(bufferr)-r;
        int v=strlen(bufferr) - (r-o);
        memmove(bufferr+o, bufferr+r, abs(q));
        bufferr[v]='\0';
    }
    
}

void arow(int num_del1, char *del1){
    int x=1;
    if(x < num_del1){
        printf("%s",del1);
        x++;
    }
    if(x==num_del1){
        printf("%s\n",del1);
    }
}

void cset(char *argum[],char *bufferr, char *del1, int b){
    char *trash;
    int c = strtol(argum[b+1],&trash,10);
    char *str = argum[b+2];
    int x,y;
    int num_del1=0;
    int num_del2 = delim_count(bufferr, del1);
    if(trash[0]!=0){
        fprintf(stderr, "Wrong argument\n");
    }
    else{
        for(int i =0; bufferr[i]!='\0';i++){
            if(bufferr[i]==del1[0]){
                if(num_del1 < c){
                    num_del1++;
                    x=i;
                }
                if(num_del1==c-1){
                    y=i;
                }
            }
        }
        if(c==1){
            y=-1;
        }
        if(c>num_del2){
            x=strlen(bufferr)-2;
        }
        int o = strlen(str)+y+1;
        int q =strlen(bufferr)-x+2;
        int v = strlen(str);
        memmove(bufferr+o, bufferr+x, abs(q)); 
        int u = 0;
        while(u < v){
            bufferr[y+1+u]=str[u];
            u++;
        }
    } 
}

void tolower_(char *argum[], char *bufferr,char *del1, int b){
    char *trash;
    int c = strtol(argum[b+1],&trash,10);
    int num_del1 =0;
    int x;
    int y;
    int num_del2 = delim_count(bufferr, del1);
    if(trash[0]!=0){
        fprintf(stderr, "Wrong argument\n");
    }
    else{
        for(int i =0; bufferr[i]!='\0';i++){
            if(bufferr[i]==del1[0]){
                if(num_del1 < c){
                    num_del1++;
                    x=i;
                }
                if(num_del1==c-1){
                    y=i;
                }
            }        
        }
        if(c==1){
            y=-1;
        }
        if(c>num_del2){
            x=strlen(bufferr)-2;
        }
        int o= y+1;
        int u=0;
        int v= x-o;
        while(u<v){
            if(bufferr[o+u]>='A' && bufferr[o+u]<='Z'){
                bufferr[o+u]=bufferr[o+u]+32;
            }
            u++;
        }
    }    
}

void toupper_(char *argum[], char *bufferr,char *del1, int b){
    char *trash;
    int c = strtol(argum[b+1],&trash,10);
    int num_del1 =0;
    int x;
    int y;
    int num_del2 = delim_count(bufferr, del1);
    if(trash[0]!=0){
        fprintf(stderr, "Wrong argument\n");    
    }
    else{
        for(int i =0; bufferr[i]!='\0';i++){
            if(bufferr[i]==del1[0]){
                if(num_del1 < c){
                    num_del1++;
                    x=i;
                }
                if(num_del1==c-1){
                y=i;
                }
            }        
        }
        if(c==1){
            y=-1;
        }
        if(c>num_del2){
            x=strlen(bufferr)-2;
        }
        int o= y+1;
        int u=0;
        int v= x-o;
        while(u<v){
            if(bufferr[o+u]>='a' && bufferr[o+u]<='z'){
                bufferr[o+u]=bufferr[o+u]-32;
            }
            u++;
        }
    }    
}

void int_(char *argum[],char *bufferr, char *del1, int b){
char *trash;
    int c = strtol(argum[b+1],&trash,10);
    int num_del1 =0;
    int x;
    int y;
    int num_del2 = delim_count(bufferr, del1);
    if(trash[0]!=0){
        fprintf(stderr, "Wrong argument\n");    
    }
    else{
        for(int i =0; bufferr[i]!='\0';i++){
            if(bufferr[i]==del1[0]){
                if(num_del1 < c){
                    num_del1++;
                    x=i;
                }
                if(num_del1==c-1){
                    y=i;
                }
            }        
        }
        if(c==1){
            y=-1;
        }
        if(c>num_del2){
            x=strlen(bufferr)-2;
        }
        int o= y+1;
        int v=x-o;
        int q= strlen(bufferr)-2;
        int u=0;
        while(u<v){
            if(bufferr[o+u]>='.'){
                if(bufferr[o+u-1]>='0' && bufferr[o+u-1]<= '9' && bufferr[o+u+1]>='0' && bufferr[o+u+1]<='9'){
                    int dot=o+u;
                    memmove(bufferr+dot,bufferr+x, q);
                }
            }
            u++;
        }
    }   
}

void copy(char* argum[], char*bufferr, char *del1, int b){
    char *trash;
    char *trash2;
    int n = strtol(argum[b+1],&trash,10);
    int m = strtol(argum[b+2],&trash2,10);
    int x1, x2;
    int y1, y2;
    int num_del2 = delim_count(bufferr, del1);
    int num_del1 =0;
    if(trash[0]!=0 || trash2[0]!=0){
        fprintf(stderr, "Wrong argument\n");    
    }
    else{
        for(int i =0; bufferr[i]!='\0';i++){
            if(bufferr[i]==del1[0]){
                if(num_del1 < n){
                    num_del1++;
                    x1=i;
                }
                if(num_del1==n-1){
                    y1=i;
                }
            }        
        }
        num_del1 =0;
        for(int i =0; bufferr[i]!='\0';i++){
            if(bufferr[i]==del1[0]){
                if(num_del1 < m){
                    num_del1++;
                    x2=i;
                }
                if(num_del1==m-1){
                    y2=i;
                }
            }        
        }
        if(n==1){
            y1=-1;
        }
        if(n>num_del2){
            x1=strlen(bufferr)-2;
        }
        if(m==1){
            y2=-1;
        }
        if(m>num_del2){
            x2=strlen(bufferr)-2;
        }
        if(n>m){
            int q= strlen(bufferr)-x2+1;
            int r1= strlen(bufferr);
            memmove(bufferr + (y2+x1-y1), bufferr + x2, q);
            int r2= strlen(bufferr)-r1;
            memmove(bufferr + (y2+1), bufferr + (y1+r2+1), (x1-y1-1)); 
        }
        if(n<m){
            int q= strlen(bufferr)-x2+1;
            memmove(bufferr+ (y2+1+x1-y1-1), bufferr + x2, q);
            memmove(bufferr + (y2+1), bufferr + (y1+1), (x1-(y1+1)));    
        }
    }
}

void swap(char* argum[], char*bufferr, char *del1, int b){
    char *trash;
    char *trash2;
    int n = strtol(argum[b+1],&trash,10);
    int m = strtol(argum[b+2],&trash2,10);
    int x1, x2;
    int y1, y2;
    int num_del2 = delim_count(bufferr, del1);
    int num_del1 =0;
    for(int i =0; bufferr[i]!='\0';i++){
        if(bufferr[i]==del1[0]){
            if(num_del1 < n){
                num_del1++;
                x1=i;
            }
            if(num_del1==n-1){
                y1=i;
            }
        }        
    }
    num_del1 =0;
     for(int i =0; bufferr[i]!='\0';i++){
        if(bufferr[i]==del1[0]){
            if(num_del1 < m){
                num_del1++;
                x2=i;
            }
            if(num_del1==m-1){
                y2=i;
            }
        }        
    }
    if(n==1){
        y1=-1;
    }
    if(n>num_del2){
        x1=strlen(bufferr)-2;
    }
    if(m==1){
        y2=-1;
    }
    if(m>num_del2){
        x2=strlen(bufferr)-2;
    }
    int r1=strlen(bufferr)-x2+1;
    memmove(bufferr+(x2+x1+1), bufferr+ x2, r1);
    memmove(bufferr+(x2+1), bufferr+(y1+1), x1);
    int r2= strlen(bufferr)-(y2-2);
    memmove(bufferr+(y1+1), bufferr+(y2+1), r2);
}

void rows(char* argum[], char*bufferr, char*del1, int b, int k1){
    char *trash;
    char *trash2;
    int n = strtol(argum[b+1],&trash,10);
    int m = strtol(argum[b+2],&trash2,10);
    if(trash[0]!=0 || trash2[0]!=0){
        fprintf(stderr, "Wrong argument\n");
    }
    else{
        if(n<=m){
            if(k1>=n && k1<=m){
            
                if(!strcmp(argum[b+3],"cset")){
                    cset(argum,bufferr,del1,b+3);
                }
                if(!strcmp(argum[b],"tolower")){
                    tolower_(argum,bufferr,del1,b+3);
                }
                if(!strcmp(argum[b+3],"toupper")){
                    toupper_(argum,bufferr,del1,b+3);
                }
                if(!strcmp(argum[b+3],"int")){
                    int_(argum,bufferr,del1,b+3);
                }
                if(!strcmp(argum[b+3],"copy")){
                    copy(argum,bufferr,del1,b+3);
                }
                if(!strcmp(argum[b+3],"swap")){
                    swap(argum,bufferr,del1,b+3);
                } 
            }
        }
        else{
        fprintf(stderr, "Wrong argument\n");
        }
    }
}

int delim_count(char*bufferr, char *del1){
    int num_dell=0;
    for(int d=0; bufferr[d]!='\0';d++){
        if(bufferr[d]==del1[0]){
            num_dell++;
        }
    }
    return num_dell;
}

void delimet(char *array, char *delimeter, char change ){
    int len = strlen(array);
    int delim_num = strlen(delimeter);
    for (int i = 0; i < len; i++){
        for(int j = 0; j < delim_num; j++){
            if(array[i] == delimeter[j]){
                array[i] = change; 
            }
        }
    }
    
}    
