#include"stdio.h"
#include"stdlib.h"


float uniform(){
	return (float)rand()/(float)RAND_MAX;
}

int nb_arr(float p0,float p1,float p2){
	float x=uniform();
	if(x<p0) return 0;
	if(x<p0+p1) return 1;
	return 2;
}

float mon_abs(float a){
	if(a>0) return a;
	else return -a;
}

void simul(float who){
	int N;
	long long int S=0;
	N=0;
	float p0,p1,p2;
	p0=1/(2*(1+who));
	p1=0.5;
	p2=1-p0-p1;
	long long int cpt=0;
	float h=1e-3;
	int l=1000;
	int dans_rectangle=0;
	float debut_rectangle=0.0;
	float moyen;
	while((cpt<1e6)&&(dans_rectangle<l)){
		N=N+nb_arr(p0,p1,p2);
		if(N>0) N=N-1;
		S=S+N;		
		cpt++;
		moyen=((float)S/(float)cpt);
		if(mon_abs(moyen-debut_rectangle)<debut_rectangle*h/2){
			dans_rectangle++;}
		else{
			debut_rectangle=moyen;
			dans_rectangle=0; }
		//printf("%d %lld %f \n",dans_rectangle>=l,cpt,moyen);
	if(dans_rectangle>=l)
		printf("%f %f\n",p2/p0,moyen);
	else
		printf("%f -1\n",p2/p0);		
	}
}

int main(){
	float who;
	for(who=0;who<0.8;who+=0.01)
		simul(who);
	for(who=0.8;who<1;who+=0.01)
		simul(who);
}

/*
void simul(float p0,float p1){
	int N;
	long long int S=0;
	N=0;
	float p2=1-p0-p1;
	long long int cpt=0;
	float h=1e-3;
	int l=1000;
	int dans_rectangle=0;
	float debut_rectangle=0.0;
	float moyen;
	while((cpt<1e6)&&(dans_rectangle<l)){
		N=N+nb_arr(p0,p1,p2);
		if(N>0) N=N-1;
		S=S+N;		
		cpt++;
		moyen=((float)S/(float)cpt);
		if(mon_abs(moyen-debut_rectangle)<debut_rectangle*h/2){
			dans_rectangle++;}
		else{
			debut_rectangle=moyen;
			dans_rectangle=0; }
		//printf("%d %lld %f \n",dans_rectangle>=l,cpt,moyen);
	if(dans_rectangle>=l)
		printf("%f %f\n",p2/p0,moyen);
	else
		printf("%f -1\n",p2/p0);		
	}		
}

int main(){
	float p0;
	for(p0=0.49;p0>0;p0-=0.01)
		simul(p0,0.5);
}
*/

/*
int main(){
	int N,S;
	N=0;
	float p0=0.3,p1=0.5,P2=0.2;
	int cpt=0;
	while(cpt<100000){
		N=N+nb_arr(p0,p1,P2);
		if(N>0) N=N-1;
		//printf("%5d \n",N);
		S=S+N;		
		cpt++;
		printf("%lf\n",(float)S/(float)cpt);
	}
}*/

/*
int main(){
	int i;
	for(i=0;i<10;i++)
		printf("%f\n",uniform());
	exit(0);

}

*/
