#include"stdio.h"
#include"stdlib.h"
#include "stdbool.h"
#include "errno.h"
#include "string.h"

struct Data
{
    int time;
    int nb_green;
    int nb_red;
    int nb_cells;
    bool treatment_cells;
};

int main()
{
    int amount=5; //nombre d'arriv¨¦e:
    FILE * file=fopen("data.csv","wb+");
/*
    for(i=0;i<amount;i++){
        datas[i].time=t_clock;
        datas[i].nb_green=nb_green;
        datas[i].nb_red=nb_red;
        datas[i].nb_cells=nb_cells;
        datas[i].treatment_cells=treatment_cells;
    }
*/
    struct Data datas[]=
    {
        {1,1,1,3,true},
        {2,0,1,2,true},
        {3,1,0,1,true},
        {4,0,1,0,true},
        {5,0,1,0,false},
    };
    int i;
    if(file){
        fprintf(file,"%s,%s,%s,%s,%s\n","time","nombre des jetons verts","nombre des jetons rouges","nombre des cellules","traitement de cellules");
        for(i=0;i<amount;i++){
        fprintf(file,"%d,%d,%d,%d,%s\n",datas[i].time,datas[i].nb_green,datas[i].nb_red,datas[i].nb_cells,datas[i].treatment_cells==true?"true":"false");
        }
    }else{
        fprintf(stderr,"erreur de cre¨¦r ce fichier\n");
		return errno;
    }
    fclose(file);
    return 0;
}

