#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve(char *start, char *end, char **dict, int n, int k);
int solveR(int pos, char **sol, int *mark, int len, char *start, char *end, char **dict, int count, int *cambiate, int *flag, int k, int n, int *len_sol);
int controllo_lettera(char **dict , int i, char *sol_prec, char *end, int *cambiate, int len, int k);
int check_end (char **sol, int pos, char* end,int *cambiate, int len, int k);

//to do
//segnalare start come preso e inserirlo nel primo posto della stampa
int main() {
    char **dict;
    char *start, *end;
    int len, n, i, k;
    FILE *fp;

    fp=fopen("dict.txt", "r");
    fscanf(fp, "%d %d\n", &n, &len);

    start=malloc(len*sizeof(char));
    end=malloc(len*sizeof(char));

    printf("inserire la parola con cui iniziare\n");
    fflush(stdin);
    gets(start);
    printf("inserire la parola con cui terminare\n");
    fflush(stdin);
    gets(end);
    printf("inserire il k desiderato\n");
    scanf("%d", &k);

    dict= (char**) malloc(n*sizeof(char*));
    for (i=0;i<n;i++)
        dict[i]=(char*)malloc(len*sizeof(char));

    i=0;
    while(fscanf(fp, "%s", dict[i])!=EOF)
        i++;

    fclose(fp);

    solve(start, end, dict, n, k);

}

void solve(char *start, char *end, char **dict, int n, int k){


    int len=(int) strlen(start);
    int *mark;
    int *cambiate;
    char **sol;
    int len_sol, i, count;
    int flag=0;
    //  int mark[n]={1};
    // int cambiate[len]={0}; ERRORE IMBARAZZANTE
    //char sol[n][len]; ERRORE IMBARAZZANTE?

    //alloco dinamicamente la memoria!
    mark=(int*) malloc(n*sizeof(int));
    cambiate=(int*) calloc(len, sizeof(int));
    sol=(char**) calloc (n, sizeof(char*));
    for(i=0; i<n; i++)
        sol[i]=(char*) calloc(len, sizeof(char));

    for(i=0;i<n;i++){
        if(!strcmp(dict[i], start))
            mark[i]=0;
        else
            mark[i]=1;

    }

    //aggiungo k, e chiamo ovviamente solveR
    count= solveR(0, sol, mark, len, start, end, dict, 0, cambiate, &flag, k, n, &len_sol);

    if (len_sol) {
        printf("è stata trovata una sequenza di %d parole\n", len_sol + 1);
        printf("\t%s\n", start);
        for (i = 0; i < len_sol; i++)
            printf("\t%s\n", sol[i]);
        printf("\n count è: %d", count+1);
    }
    else
        printf("non è stata trovata alcuna sequenza di parole\n");
}
//mancava k e dict, olte all'asterisco a cambiate
int solveR(int pos, char **sol, int *mark, int len, char *start, char *end, char **dict, int count, int *cambiate, int *flag, int k, int n, int *len_sol){
int i, indx;

    if (pos != 0 && check_end(sol, pos-1, end, cambiate, len, k)) {
        //ho torvato la soluzione;
        *flag = 1;
        *len_sol=pos;
        count=pos;
        return count;
    }
//mancava il backtracking
    for (i=0;i<n&&!(*flag);i++) {
        if (mark[i]) {
            if (pos == 0) {
                indx=controllo_lettera(dict, i, start, end, cambiate, len, k);
                if (indx!=-1){
                    sol[pos] = dict[i];
                    mark[i] = 0;
                    count = solveR(pos + 1, sol, mark, len, start, end, dict, count , cambiate, flag, k, n, len_sol);
                    mark[i]=1;
                    cambiate[indx]-=1;
                }
            } else {
                indx=controllo_lettera(dict, i, sol[pos - 1], end, cambiate, len, k);
                if (indx!=-1){
                    sol[pos] = dict[i];
                    mark[i] = 0;
                    count = solveR(pos + 1, sol, mark, len, start, end, dict, count, cambiate, flag, k, n, len_sol);
                    mark[i]=1;
                    cambiate[indx]-=1;
                }
            }
        }
        //return count;
    }
    if (flag)
        return count;
    return 0;
}

//avevo sbagliato:
//1. confrontavo sol[pos] ancora inesistente anzichè dict[i]
//2. non salvavo in indice la j corrispondente
//3. non passavo alla funzione ne dict, ne k, nel sol_prec
int controllo_lettera(char **dict , int i, char *sol_prec, char *end, int *cambiate, int len, int k){
    int j, flag=0, indice=0;

    for(j=0; j<len&&flag<2; j++){
        //diverso non uguale
        if(dict[i][j]!=sol_prec[j]){
            flag++;
            indice=j;
        }
    }

    if (flag==1){
        cambiate[indice]+=1;
        return indice;
    }
    return -1;
}

int check_end (char **sol, int pos, char* end,int *cambiate, int len, int k){
    int j;
    for (j=0;j<len;j++)
        if (cambiate[j]<k) return 0;
    if (!strcmp(sol[pos], end))
         return 1;

    return 0;
}