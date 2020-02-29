#include <stdio.h>
#include "Cellule.h"
#include "loi_hpexp.c"
#include "depot_excel.c"

/////////////// Initialisation des param¨¨tres des buffers //////////////////
int t_clock=0;
int K; // repr¨¦sente le param¨¨tre de d¨¦cision pour les jetons rouge sur le nombre de membres de CellBuffer
int V; // Taille du buffer de jetons verts
int R; // taille du buffer de jetons rouge
int B; // taille du buffer de cellules
int nb_cells=0;

//////////// Declaration des buffers de jetons ////////////////
int nb_green=0;
int nb_red=0;

////////////// Fonction de cr¨¦ation de cellules ///////////////////

cell* create_cell(){
    cell *c=malloc(sizeof(cell));
    c->jeton=0; //la cellule n'a pas mang¨¦ de jetons par d¨¦faut.
    return c;
    }

void free_cell(cell* c){
   // free(c);
}
/////////// Simulation de l'arriv¨¦e d'une cellule ///////////////



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


    if(next_treat == 1) {
        if((nb_green>0)||((nb_red>0)&&(nb_cells>K))){
        //t_clock=t_clock+1;
        return -1 ;
        }// cas o¨´ une cellule est trait¨¦e et va ¨ºtre expuls¨¦e du systeme au prochain tick d'horloge

    }

    if((next_cell<next_red)&&(next_cell<next_green)){
    //t_clock=t_clock+to_sort[0];
    return 0;  // event = next cell arrive
    }
    if((next_green<next_red)&&(next_green<next_cell)){
    //t_clock=t_clock+to_sort[2];
    return 1;  // event = next jeton vert arrive
    }
    if((next_red<next_cell)&&(next_red<next_green)){
    //t_clock=t_clock+to_sort[1];
    return 2;  // event = next jeton rouge arrive
    }
    if((next_red<next_cell)&&(next_red==next_green)){
    //t_clock=t_clock+to_sort[1];
    return 3;  // event = jeton rouge et vert arrive
    }
    if((next_cell==next_red)&&(next_cell==next_green)){
    //t_clock=t_clock+to_sort[0];
    return 4; // event = jetons arrivent + cellule
    }
    if((next_cell==next_red)&&(next_cell<next_green)){
    //t_clock=t_clock+to_sort[0];
        return 5; // event = cell+red
    }
    if((next_cell<next_red)&&(next_cell==next_green)){
    //t_clock=t_clock+to_sort[0];
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

printf("init system\n\n--------------------\n\n");
int previous_time=t_clock;
int cell_treated=0; //indique si une cellule est actuellement trait¨¦e
float freq_green=0.2; // a mettre en param
float freq_red=0.7; // a mettre en param

cell cell_file[B]; // repr¨¦sente le buffer de cellules
void cell_arrive(){
        if(nb_cells<B-1){
        cell* c=create_cell();
        cell_file[nb_cells+1]=*c;
        nb_cells++;
    }
}
int next_green=floor(1/freq_green);
int next_red=floor(1/freq_red);
int next_cell=floor(loi_hpexp()); //convert time to "sec"  // ca est multiplie par 100 ou 60?
int event = next_event(next_cell,next_green,next_red,cell_treated);


//////////stats/////////
int nb_cells_eaten=0;
int nb_jetons_red_eaten=0;
int nb_jetons_green_eaten=0;
int new_cell=0;
while(t_clock<50){  //amount=10000 est defini a la tete ds 'depot_excel.c'
    printf("\n--------------\n");
    printf("t_clock value = %d \n",t_clock);
    printf("event value = %d\n",event);
    printf("nextgreen = %d,\n nextred=%d,\nnextcell=%d\n\n",next_green,next_red,next_cell);
    if(cell_treated==1){
        if(nb_green>0){
        eat_jet(&cell_file[nb_cells-1],1); // au debut, t'as defini nb_cells=0 => tu ne peux pas rentrer dans ce iff si nb_cells=0
        nb_cells--;

        free(&cell_file[nb_cells-1]);
        cell_treated=0;
        printf("a cell left eating a green jeton!\n");
        nb_jetons_green_eaten++;
        goto cell_treated;
        }else if((nb_red>0)&&(nb_cells>K)){
        eat_jet(&cell_file[nb_cells-1],2);
        nb_cells--;
       free(&cell_file[nb_cells-1]);
        cell_treated=0;

        printf("a cell left eating a red jeton!\n");
        nb_jetons_red_eaten++;
        goto cell_treated;
        }
    }
    printf("reach switch line \n");
   switch(event) {
    default :

    goto end;

   case 0  :
      cell_arrive();
      printf("case 0\n");

      //printf("%.10f",temp);
      next_cell=floor(loi_hpexp());
      //printf("next_cell=%d\n", next_cell);
      next_red--;  // 'previous_time' signifie quoi?
      next_green--;
      t_clock++;
      goto there;

    case 1 :
      nb_green++;
      next_green=floor(1/freq_green);
      next_red--;
      next_cell--;
      printf("case 1\n");
      t_clock++;
      goto there;

    case 2 :
      nb_red++;
      next_red=floor(1/freq_red);
      next_green--;
      next_cell--;
      printf("case 2\n");
      t_clock++;
      goto there;

    case 3 :
      nb_green++;
      nb_red++;
      next_cell--;
      next_red=floor(1/freq_red);
      next_green=floor(1/freq_green);
      printf("case 3\n");
      t_clock++;
      goto there;

    case 4 :
      cell_arrive();
      nb_green++;
      nb_red++;
      next_red=floor(1/freq_red);
      next_green=floor(1/freq_green);
      next_cell=floor(loi_hpexp());
      printf("case 4\n");
      t_clock++;
      goto there;

    case 5 :
      cell_arrive();
      nb_red++;
      next_red=floor(1/freq_red);
      next_green--;
      next_cell=floor(loi_hpexp());  //1000? => pour transformer en un "temps" ¨¤ l'echelle de la clock (en int positif quoi)
      printf("case 5\n");
      t_clock++;
      goto there;

    case 6 :
      cell_arrive();
      nb_green++;
      next_green=floor(1/freq_green);
      next_red--;
      next_cell=floor(loi_hpexp());
      printf("case 6\n");
      t_clock++;
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

    //pr¨¦vision du prochain event
cell_treated: ;
event = next_event(next_cell,next_red,next_green,cell_treated);
printf("next_event value = %d\n",event);
printf("nb_cell=%d\nnb_green=%d\nnb_red=%d\n",nb_cells,nb_green,nb_red);

in_tab(datas,t_clock,nb_green,nb_red,nb_cells,cell_treated);
n++;

}//end while

printf("\n");
stock_file(datas);

end: ;
    printf("\n\n---------------`\n\n");
    printf("nombre de jetons rouges mang¨¦s : %d\nnombre de jetons verts mang¨¦s : %d\n",nb_jetons_red_eaten,nb_jetons_green_eaten);
    printf("\n\nend of simulation! Goodbye!\n\n");
//free(datas);
return 0;
}




