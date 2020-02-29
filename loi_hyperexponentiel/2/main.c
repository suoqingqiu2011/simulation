#include <stdio.h>
#include "Cellule.h"
#include "loi_hpexp.c"
#define bug printf("i'am here %d \n",__LINE__);

/////////////// Initialisation des paramètres des buffers //////////////////
int t_clock=0;
int K; // représente le paramètre de décision pour les jetons rouge sur le nombre de membres de CellBuffer
int V; // Taille du buffer de jetons verts
int R; // taille du buffer de jetons rouge
int B; // taille du buffer de cellules
int nb_cells=0;

//////////// Declaration des buffers de jetons ////////////////
int nb_green=0;
int nb_red=0;

////////////// Fonction de création de cellules ///////////////////

cell* create_cell(){
    cell *c=malloc(sizeof(cell));
    c->jeton=0; //la cellule n'a pas mangé de jetons par défaut.
    return c;
    }

void free_cell(cell* c){
    free(c);
}
/////////// Simulation de l'arrivée d'une cellule ///////////////



///////////// Fonction permettant a une cellule de manger un jeton /////////////
void eat_jet(cell* c,int color){
    c->jeton=&color;
    if(color==1){
        nb_green--;
    }else if(color==2){
        nb_red--;
    }
}


int next_event(int next_cell, int next_red, int next_green,int next_treat){
    printf("calling next event\n");
    int to_sort[2];
    to_sort[0] = next_cell;
    to_sort[1] = next_red;
    to_sort[2] = next_green;

	bug
    if(next_treat == 1) { 
        if((nb_green>0)||(nb_red>0)&&(nb_cells>K)){
        t_clock=t_clock+1;
        return -1 ;
        }// cas où une cellule est traitée et va être expulsée du systeme au prochain tick d'horloge

    }

    if((next_cell<next_red)&&(next_cell<next_green)){
    t_clock=t_clock+to_sort[0];
    return 0;  // event = next cell arrive
    }
    if((next_green<next_red)&&(next_green<next_cell)){
    t_clock=t_clock+to_sort[2];
    return 1;  // event = next jeton vert arrive
    }
    if((next_red<next_cell)&&(next_red<next_green)){
    t_clock=t_clock+to_sort[1];
    return 2;  // event = next jeton rouge arrive
    }
    if((next_red<next_cell)&&(next_red==next_green)){
    t_clock=t_clock+to_sort[1];
    return 3;  // event = jeton rouge et vert arrive
    }
    if((next_cell==next_red)&&(next_cell==next_green)){
    t_clock=t_clock+to_sort[0];
    return 4; // event = jetons arrivent + cellule
    }
    if((next_cell==next_red)&&(next_cell<next_green)){
    t_clock=t_clock+to_sort[0];
        return 5; // event = cell+red
    }
    if((next_cell<next_red)&&(next_cell==next_green)){
    t_clock=t_clock+to_sort[0];
        return 6; //event=cell+green
    }
    printf("wrong return from next_event\n");
    return -99; //big bug!
}


///////////////// Fonction principale //////////////////

int main(int args, char** argv) {
    /*
    param 0 : function name.
    param 1-4 : K,V,R,B
    */
/// init ///
printf("hi, welcome here! \n");
printf("init srand\n");
    srand (0);
    if(args<=4){
        printf("error\n");
        return -1;
    }
    printf("init param\n");
    K=atoi(argv[1]);
    V=atoi(argv[2]);
    R=atoi(argv[3]);
    B=atoi(argv[4]);

printf("init system\n");
int previous_time=t_clock;
int cell_treated=0; //indique si une cellule est actuellement traitée
float freq_green=0.2; // a mettre en param
float freq_red=0.7; // a mettre en param
float* a=proba(15); ///a changer
cell cell_file[B]; // représente le buffer de cellules
void cell_arrive(){
        if(nb_cells<B-1){
        cell* c=create_cell();
        cell_file[nb_cells+1]=*c;
        nb_cells++;
    }
}
int next_green=floor(1/freq_green);
int next_red=floor(1/freq_red);
int next_cell=floor(loi_hpexp(a,15,1))*1000; //convert time to "sec"  // ca est multiplie par 100 ou 60?
int event = next_event(next_cell,next_green,next_red,cell_treated);

while(t_clock<10){
    printf("t_clock value = %d \n",t_clock);
    if(cell_treated==1){
        if(nb_green>0){
        eat_jet(&cell_file[nb_cells-1],1); // au debut, t'as defini nb_cells=0
        nb_cells--;
        free(&cell_file[nb_cells-1]);
        cell_treated=0;
        }else if((nb_red>0)&&(nb_cells>K)){
        eat_jet(&cell_file[nb_cells-1],2);
        nb_cells--;
        free(&cell_file[nb_cells-1]);
        cell_treated=0;
        }
    }
    printf("reach switch line \n");
   switch(event) {
    default :
    printf("rerror!\n");
    goto there;
   case 0  :
      cell_arrive();
      printf("case 0\n");
      float temp=loi_hpexp(a,15,1);
      printf("%.10f",temp);
      next_cell=floor(loi_hpexp(a,15,1)*1000);
      printf("next_cell=%d\n", next_cell);
      next_red-=t_clock-previous_time;  // 'previous_time' signifie quoi?
      next_green-=t_clock-previous_time;
      goto there;

    case 1 :
      nb_green++;
      next_green=t_clock+floor(1/freq_green);
      next_red-=t_clock-previous_time;
      next_cell-=t_clock-previous_time;
      printf("case 1\n");
      goto there;

    case 2 :
      nb_red++;
      next_red=t_clock+floor(1/freq_red);
      next_green-=t_clock-previous_time;
      next_cell-=t_clock-previous_time;
      printf("case 2\n");
      goto there;

    case 3 :
      nb_green++;
      nb_red++;
      next_cell-=t_clock-previous_time;
      next_red=t_clock+floor(1/freq_red);
      next_green=t_clock+floor(1/freq_green);
      printf("case 3\n");
      goto there;

    case 4 :
      cell_arrive();
      nb_green++;
      nb_red++;
      next_red=t_clock+floor(1/freq_red);
      next_green=t_clock+floor(1/freq_green);
      next_cell=floor(loi_hpexp(a,15,1)*1000);
      printf("case 4\n");
      goto there;

    case 5 :
      cell_arrive();
      nb_red++;
      next_red=t_clock+floor(1/freq_red);
      next_green-=t_clock-previous_time;
      next_cell=floor(loi_hpexp(a,15,1)*1000);  //1000? => pour transformer en un "temps" à l'echelle de la clock (en int positif quoi)
      printf("case 5\n");
      goto there;

    case 6 :
      cell_arrive();
      nb_green++;
      next_green=t_clock+floor(1/freq_green);
      next_red-=t_clock-previous_time;
      next_cell=floor(loi_hpexp(a,15,1)*1000);
      printf("case 6\n");
      goto there;
}

there: ;
//nettoyage des overflow (un peu sale, mais c'est economique)
    if(nb_green>V){
        nb_green--; //nb_green=V;
    }
    if(nb_red>R){
        nb_red--; //nb_red=R;
    }

    //traitement des cellules
    if(nb_cells>0){
        if(cell_treated==0){
            cell_treated=1;
        }
    }

    //prévision du prochain event
previous_time=t_clock;
event = next_event(next_cell,next_green,next_red,cell_treated);

printf("event value = %d\n",event);



}//end while
return 0;
}




