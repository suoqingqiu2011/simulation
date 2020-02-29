#include"stdio.h"
#include"stdlib.h"
#include "stdbool.h"
#include "errno.h"
#include "string.h"
#define amount 1000 //nombre d'arrivee:


struct Data
{
    int temps;
    int nb_green;
    int nb_red;
    int nb_cells;
    int treatment_cells;
}datas[amount];

int n=0;

void in_tab(struct Data* datas,int t_clock,int nb_green,int nb_red,int nb_cells,int cell_treated){
    datas[n].temps=t_clock;
    datas[n].nb_green=nb_green;
    datas[n].nb_red=nb_red;
    datas[n].nb_cells=nb_cells;
    datas[n].treatment_cells=cell_treated;
}

int stock_file(struct Data* datas)
{

    FILE * file=fopen("data.csv","wb+");

    if(file){
        fprintf(file,"%s,%s,%s,%s,%s\n","time","nombre des jetons verts","nombre des jetons rouges","nombre des cellules","traitement de cellules");
        for(n=0;n<amount;n++){
            if(datas[n].temps!=0){
                fprintf(stderr,"%d,%d,%d,%d,%d\n",datas[n].temps,datas[n].nb_green,datas[n].nb_red,datas[n].nb_cells,datas[n].treatment_cells==1?1:0);
                fprintf(file,"%d,%d,%d,%d,%d\n",datas[n].temps,datas[n].nb_green,datas[n].nb_red,datas[n].nb_cells,datas[n].treatment_cells==1?1:0);
                }
                else
                    break;
        }
    }else{
        fprintf(stderr,"erreur de cre¨¦r ce fichier\n");
		return errno;
    }
	free(datas);    
	fclose(file);
    return 0;

}
