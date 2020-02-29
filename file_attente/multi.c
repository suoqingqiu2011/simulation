#include"stdio.h"
#include"math.h"

void init(float p[][3],float *pi,float *pip);
void mult(float p[][3],float *pi,float *pip);
void aff(float *pi);

int main(){
	float p[3][3],pi[3],pip[3];
	init(p,pi,pip);
	aff(pi);
	int i;
	for(i=0;i<3;i++){
		mult(p,pi,pip);
		aff(pi);
	}
	return 0;
}
	
void init(float p[][3],float *pi,float *pip){
	p[0][0]=0.2;
	p[0][1]=0.0;
	p[0][2]=0.8;
	p[1][0]=0.4;
	p[1][1]=0.4;
	p[1][2]=0.2;
	p[2][0]=0.5;
	p[2][1]=0.5;
	p[2][2]=0.0;
	
	pi[0]=1.0;
	pi[1]=0.0;
	pi[2]=0.0;	
}

void mult(float p[][3],float *pi,float *pip){
	int i,j;
	for(j=0;j<3;j++){
		pip[j]=pi[j];
	}
	for(j=0;j<3;j++){
		pi[j]=0;
		for(i=0;i<3;i++){
			pi[j]+=pip[j]*p[i][j];
		}
	}
}

void aff(float *pi){
	printf("%0.6f,%0.6f,%0.6f \n",pi[0],pi[1],pi[2]);
}
