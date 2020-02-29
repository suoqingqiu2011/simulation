#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include <float.h>
#include <errno.h>
#include <fenv.h>
#pragma STDC FENV_ACCESS ON

float Poisson_next(float rate)
{
    return -logf(1.0f - (float)rand()/(RAND_MAX))/ rate;
}

float* proba(int nb){ //ressort le tableau contenant les probas déjà trié.
    float* a=malloc(sizeof(float)*nb);
    int i=0;
    float temp;
    float proba_total=1.;
    srand (0);
    while(i<nb-1){
        temp = (float)rand()/(float)RAND_MAX ;
        if(proba_total-temp>=0){
            a[i]=temp ;
            proba_total-=temp ;
            i++;
        }
    }
    a[nb-1]=proba_total ;
    return a;
}

void tri_array(float *a,int size){
    float cle;
    int i,j;
    for(i=0;i<size;i++){
        cle=a[i];
        j=i-1;
        while(j>=0&&a[j]<cle){
            a[j+1]=a[j];
            j=j-1;
        }
        a[j+1]=cle;
    }
}

float loi_hpexp(float *a,int size,int nb_excution){ //size = taille du tableau a
    int i;
    //float lamda[]={0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75}; //paramètres de ces lois exponentielles
    float lamda[]={40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0,40.0}; //paramètres de ces lois exponentielles
    float tirage=(float)rand()/(float)RAND_MAX;
    int indice;
    float tmp=0.;
    for(i=0;i<15;i++){
        if(tirage<=a[i]+tmp){
            indice=i;
        }else{
            tmp+=a[i];
        }
    }
     // on récupére l'indice de la loi de proba selectionnée.
   // printf("%.10f\n",lamda[0]);

    float nexttime = Poisson_next(lamda[nb_excution]);
    return nexttime;

}

void print(int nb,int nb_arriv,float *a){ //pour afficher les valeurs générées
    int i;
    for (i=0;i<nb;i++){
        printf("%.10f \n",a[i]);
        if(a[i]==0){
            nb_arriv--;
        }
    }
    printf("%d \n",nb_arriv);
}
/*
void loi_hpexp(int nb,float *a){ //nb sert à prévoir un nombre d'arrivées?
    int i;
    int lamda[]={1,2,3,4,5,6,7,8,9,10}; //paramètres de ces lois exponentielles
    int sum=0,x=0; //x - valeur d'axe horizontal des abscisses

    for (i=0;i<nb;i++){
        if(a[i]!=0){  //pourquoi?
        printf("%.10f %d\n",a[i],lamda[i]); //c'est lamda, pas lemda! mais ca ne change rien :)
        printf("%.10f \n",exp((-lamda[i])*x));
        sum+=a[i]*lamda[i]*exp((-lamda[i])*x); //ok non là il y a un problème je pense, la loi Hexp n'est pas une somme de loi exp, c'est une loi exp choisi parmis d'autres.
        x++;
        printf("%.10f \n",sum);
        }
    }
}*/
////////// Loi hyperexp /////////////


/////////// Generation de valeurs suivant un processus de poisson /////////////




/////////////
/*
int main(){

    int i=0;
    float* a=malloc(sizeof(float)*16);
    proba(15);

    tri_array(a,15);

    int nb_excution;
    float res;
    for(nb_excution=0;nb_excution<15;nb_excution++){
        res=loi_hpexp(a,15,nb_excution);
        printf("%.10f\n",res );
        printf("toto");

    }

    free(a);
    }
*/
