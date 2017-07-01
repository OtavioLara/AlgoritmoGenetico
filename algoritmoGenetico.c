#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define _MAX 10
#define _MIN -10
#define _NUM_BITS 16
#define _POP_SIZE 30
#define _MUTATION 1
#define _NUM_GENERATIONS 30

int individual[_POP_SIZE];

int getFeasibleValue(int num){
	return (_MIN + (_MAX - _MIN) * (num/((pow(2,_NUM_BITS))-1)));
}
void crossOver(int x1, int x2,int* nx1, int* nx2){
	//~ float r = 1+(rand()%((sizeof(int)*8)-2)); \\com esses os filhos quase não alteravam pois x1 e x2 vem com numeros menor que 10
	float r = rand()%4;
	int rInt = (int)r;
	float nf = pow(2.0,r);
	int mask = (int)nf;
	mask--;
	displayBits("mask: ", mask);
	unsigned int aux1, aux2;
	aux1 = x1;
	aux2 = x2;
	printf("shift %d\n",((sizeof(int)*8)-rInt));
	displayBits("x1: ",aux1);
	displayBits("x2: ",aux2);
	
	aux1 <<= (sizeof(int)*8 - rInt);
	aux1 >>= (sizeof(int)*8 - rInt);
	aux2 <<= (sizeof(int)*8 - rInt);
	aux2 >>= (sizeof(int)*8 - rInt);
	displayBits("aux1: ",aux1);
	displayBits("aux2: ",aux2);
	
	*nx1 = (x1 & ~(mask)) | aux2;
	*nx2 = (x2 & ~(mask)) | aux1;
	
	displayBits("nx1: ",*nx1);
	displayBits("nx2: ",*nx2);
	printf("\n");
	//~ printf("\n x1:%d x2:%d nx1:%d nx2:%d x3:%d x4:%d\n",x1,x2,*nx1,*nx2,x3,x4);
	//~ printf("x1:%d x2:%d nx1:%d nx2:%d\n",x1,x2,*nx1,*nx2);
	
}
void displayBits(char* mensage, int value){
	int c;
	int displayMask = 1 << 31;
	printf("%s%10d = ",mensage, value);
	for(c = 1; c <= sizeof(int)*8; c++){
		putchar(value & displayMask ? '1':'0');
		value <<= 1;
		if(c%8 == 0){
			putchar(' ');
		}
	}
	putchar('\n');
}
void mutation(int* x){
	int exp = pow(2,rand()%_NUM_BITS);
	*x = *x ^ exp;
	getFeasibleValue(*x);
}
int fitness(int x){
	x = getFeasibleValue(x);
	return pow(x,2) - 3*x + 4;
}
int torneio(){
	int x,y;
	x = (rand()%(_POP_SIZE));
	do{
		y = (rand()%(_POP_SIZE));
	}while(x == y);
	if(fitness(individual[x]) <= fitness(individual[y])){
		return y;
	}else{
		return x;
	}
}
int main() {
	
	int max_size = pow(2,_NUM_BITS);
	srand(time(NULL));
	
	int i, j;
	
	for(i = 0; i < _POP_SIZE; i++){
		individual[i] = getFeasibleValue(rand()%(max_size));
	}
	for(i = 0; i < _POP_SIZE; i++){
		printf("[%d] -> %d\n",i, individual[i]);
	}
	int newIndividual[_POP_SIZE];
	
	
	printf("\n");
	for(i = 0; i < _NUM_GENERATIONS; i++){
		for(j = 0;j < _POP_SIZE-1; j+=2){
			int ind1,ind2,i1,i2;
			i1 = torneio();
			i2 = torneio();
			if(70 > rand()%100){
				crossOver(individual[i1],individual[i2],&ind1,&ind2);
				if(_MUTATION > rand()%100){
					mutation(&ind1);
				}
				if(_MUTATION > rand()%100){
					mutation(&ind2);
				}
				//~ printf("ind 1: %d\n", ind1);
				//~ printf("factibilidade: %d\n", getFeasibleValue(ind1));
				if(ind1 > _MAX && ind1 < _MIN){
					newIndividual[j] = getFeasibleValue(ind1);
				}else{
					newIndividual[j] = ind1;
									}
				if(ind2 > _MAX && ind2 < _MIN){
					newIndividual[j+1] = getFeasibleValue(ind2);
				}else{
					newIndividual[j+1] = ind2;
				}
			}else{
				if(individual[i1] > _MAX && individual[i1] < _MIN){
					newIndividual[j] = getFeasibleValue(individual[i1]);
				}else{
					newIndividual[j] = individual[i1];
				}
				if(individual[i2] > _MAX && individual[i2] < _MIN){
					newIndividual[j+1] = getFeasibleValue(individual[i2]);
				}else{
					newIndividual[j+1] = individual[i2];
				}
			}
			//printf("ind1 : %d ind2 : %d\n",ind1,ind2);
		}
		int k;
		for(k = 0; k < _POP_SIZE; k++){
			individual[k] = newIndividual[k];
			printf("[%d] -> %d\n",k, individual[k]);
		}
		printf("\n");
	}
	printf("\n");
	for(i = 0; i < _POP_SIZE; i++){
		printf("[%d] -> %d\n",i, individual[i]);
	}
	
	return 0;
}

