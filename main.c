//
// Created by Manuel Fissore on 18/02/2021.
// FATTO ALL'ESAME
void solve(char *start, char *end, char **dict, int n, int k){
    int mark[n]={1};
    int len=strlen(start);
    int cambiate[len]={0};
    char sol[n][len];
    int len_sol;

    len_sol= solve(0, sol, mark, len, start, end, 0, cambiate, 0);

    if (len_sol)
        printf("sono stata trovata una sequenza di %d parole", len_sol+1);
    else
        printf("non è stata trovata alcuna sequenzaz di parole");
}

int solveR(int pos, char **sol, int *mark, int len, char *start, char *end, int count, int cambiate, int flag) {

    if (pos!=0&&check_end (sol, pos, end, cambiate, len, k)){
        //ho torvato la soluzione;
        flag=1;
        return count;
    }
    for (i=0; i<n; i++){ if (mark[i]){
            if (pos==0){
                if (controllo_lettera(start, pos-1, end, cambiate, len)){
                    sol[pos]=dict[i];
                    mark[i]= 0;
                    count=solveR(pos+1, sol, mark, len, start, end, count+1, cambiate, flag);
                }
            }else{
                if(controllo_lettera(sol, pos-1, end,cambiate, len)){
                    sol[pos]=dict[i];
                    mark[i]=0;
                    count=solveR(pos+1, sol, mark, len, start, end, count+1, cambiate, flag);
                }
            }
            return count;
        }
        if(flag)
            return count;
        return 0;
    }

    int controllo_lettera(char **sol, int precedente, char *end, int *cambiate, int len){
        int j, flag=0;

        for(j=0; j<len; j++){
            if(sol[pos][j]==sol[pos-1][j]){
                flag++;
                indice=j;
            }
        }

        //se cambiano più lettere o più di k-1 volte non accetto
        if (flag==1){
            if (cambiate[j]<k-1){
                cambiate[j]+1;
                return 1;
            }

            //se sta cambiando per la k-esima volta controllo che sia ugaule alla soluzione finale
            if (cambiate[j]==(k-1){
                if (sol[pos][j]==end[j])
                    return 1;

            }
        }
        return 0;
    }

    int check_end (char **sol, int pos, char* end,int *cambiate, int len, int k){
        int j;
        for (j=0;j<len;j++)
            if (cambiate[j]!=k) return 0;
        if (sol[pos]==end) return 1;

        return 0;
    }