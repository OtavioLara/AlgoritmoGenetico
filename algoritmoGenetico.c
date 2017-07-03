#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define _MIN -10
#define _MAX 10

#define _NUM_BITS 16
#define _POP_SIZE 30
#define _MUTATION 1
#define _NUM_GENERATIONS 200

int individual[_POP_SIZE];
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
float getFeasibleValue(float num){
	float s = pow(2,_NUM_BITS);
	int sInt = (int)s;
	sInt--;
	s = (float)sInt;
	int pt1 = (_MAX - _MIN);
	return _MIN + ( pt1 * (num/s));
}
void crossOver(int x1, int x2,int* nx1, int* nx2){
	//~ float r = 1+(rand()%((sizeof(int)*8)-2)); \\com esses os filhos quase não alteravam pois x1 e x2 vem com numeros menor que 10
	float r = 1+(rand()%3);
	int rInt = (int)r;
	float nf = pow(2.0,r);
	int mask = (int)nf;
	mask--;
	unsigned int aux1, aux2;
	aux1 = x1;
	aux2 = x2;

	aux1 <<= (sizeof(int)*8 - rInt);
	aux1 >>= (sizeof(int)*8 - rInt);
	aux2 <<= (sizeof(int)*8 - rInt);
	aux2 >>= (sizeof(int)*8 - rInt);

	*nx1 = (x1 & ~(mask)) | (aux2 & mask);
	*nx2 = (x2 & ~(mask)) | (aux1 & mask);
	if(*nx1 > _MAX || *nx1 < _MIN){
		*nx1 = getFeasibleValue(*nx1);
	}
	if(*nx2 > _MAX || *nx2 < _MIN){
		*nx2 = getFeasibleValue(*nx2);
	}

	
}

void mutation(int* x){
	int exp = pow(2,rand()%_NUM_BITS);
	*x = *x ^ exp;
	if(*x > _MAX || *x < _MIN){
		*x = getFeasibleValue((float)(*x));
	}
}
int fitness(int x){
	if(x > _MAX || x < _MIN){
		x = getFeasibleValue((float)x);
	}
	return ((pow(x,2)) - (3*x) + 4);
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
	//~ individual = malloc(sizeof(int)*_POP_SIZE);
	int max_size = pow(2,_NUM_BITS);
	srand(time(NULL));
	int newIndividual[_POP_SIZE];
	int i, j;
	for(i = 0; i < _POP_SIZE; i++){
		newIndividual[i] = 0;
		individual[i] = 0;
	}
	
	for(i = 0; i < _POP_SIZE; i++){
		individual[i] = getFeasibleValue((float)(rand()%(max_size)));
	}
	for(i = 0; i < _POP_SIZE; i++){
		printf("[%d] -> %d\n",i, individual[i]);
	}
	//~ int* newIndividual = malloc(sizeof(int)*_POP_SIZE);

	printf("\n");
	for(i = 0; i < _NUM_GENERATIONS; i++){
		for(j = 0;j < _POP_SIZE-1; j+=2){
			int ind1,ind2,i1,i2;
			i1 = torneio();
			i2 = torneio();
			if(70 > rand()%100){
				printf("fiz crossover");
				crossOver(individual[i1],individual[i2],&ind1,&ind2);
				if(_MUTATION > rand()%100){
					mutation(&ind1);
				}
				if(_MUTATION > rand()%100){
					mutation(&ind2);
				}
				newIndividual[j] = ind1;
				newIndividual[j+1] = ind2;
			}else{
				newIndividual[j] = individual[i1];
				newIndividual[j+1] = individual[i2];
			}

			//~ if(ind1 > _MAX
			//~ printf("ind1 : %d ind2 : %d\n",ind1,ind2);
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

