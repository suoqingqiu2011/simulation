#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NMAX 10000


// Fonction qui renvoie une valeur aleatoire
// qui suit une loi uniforme sur [0,1[
double uniforme(){
  return rand()*1.0/RAND_MAX;
}

// Fonction qui renvoie une valeur aleatoire
// qui suit une loi exponentielle de parametre x
double expo(double x){
  return -log(uniforme()) / x;
}

//CdM en temps discret
int discret(double t[8]){
  double u=uniforme();
  int i=1;
  double cumule=t[0];
  while(u>cumule){
     cumule+=t[i];
     i++;
  }  
  return i;
}

//loi geometrique
int geometric1(double p){
   int i=1;
   double cumule=p;
   double e=1-p;
   double u=uniforme();
   while(u>cumule){
     i++;
     cumule+=e*p;
     e*=1-p;
   }  
   return i;
}

int geometric2(double p){
   int cmp=0;
   double u;
   do{
      u=uniforme();
      cmp++;
   }while(u>p);  
   return cmp;
}

int geometric3(double p){
   return -expo(1)/log(1-p);
}


int main(){
  int i;
  srand(7913741);
  for(i=0; i<NMAX; i++){
    printf("%f\n", expo(1.0));
  }

  
  //CdM en temps discret
  /*double t[8]={0.1,0.2,0.05,0.05,0.05,0.15,0.35,0.05};
  for(i=0; i<NMAX; i++){
    printf("%d\n", discret(t));
  }*/
  
  //loi geometrique
 /* for(i=0; i<NMAX; i++){
    printf("%d\n", geometric1(0.25));
  }
  for(i=0; i<NMAX; i++){
    printf("%d\n", geometric2(0.25));
  }
   for(i=0; i<NMAX; i++){
    printf("%d\n", geometric3(0.25));
  }	
*/

  
  exit(EXIT_SUCCESS);
}
