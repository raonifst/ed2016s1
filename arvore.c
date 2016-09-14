#include "arvore.h"

typedef struct _ex {
  int *caract; // Valores das Características
  int y; // Resposta
} Exemplo;

typedef struct _dados {
  Exemplo *exemplo; //Exemplos
  int n;// Quantidade de exemplos
  int c; //Quantidade de características
  int *rem; //
} Dados;

float entropy(float a, float b)
{
	float p = (a+0.0)/(a+b);
	if(p == 1 || p == 0) return 0;		
	return -log2f(p)*p -log2f(1-p)*(1-p);	
}

float ganho_inf(Dados *pts, int c)
{
	int i ;
	float  sim[2] = {0,0}, nao[2] = {0,0}, s=0;
	
	
	for(i = 0; i < pts->n; i++) {
				
		if(pts->exemplo[i].caract[c] == 1) 
			sim[pts->exemplo[i].y]++;
		else
			nao[pts->exemplo[i].y]++;	
		s += pts->exemplo[i].y;	
	}
	
	return entropy(s, pts->n-s) - 
			( ((sim[0]+sim[1])/pts->n)*entropy(sim[0], sim[1]) + 
	        ((nao[0]+nao[1])/pts->n)*entropy(nao[0], nao[1]) );
	
}

int maior_ganho_inf(Dados* pts)
{
	float max = -1, vmax = -1;
	int i;
	float g;
	for(i = 0; i < pts->c; i++) {
		if(pts->rem[i] != REMOVIDO) {
			g = ganho_inf(pts, i);
			printf("%d %f %f\n", i, g, vmax);
			if(g - vmax > 0.001){
				max = i;
				vmax = g;
			}
		}
	}
	return max;
}
