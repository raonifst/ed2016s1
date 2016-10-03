#include <stdio.h>

/*Torre de hanoi*/

void mover(int origem, int destino)
{
  printf("move um disco de %d para %d\n", origem, destino);
}

void resolver(int n, int origem, int destino, int aux)
{
  if(n == 0)
    return;
  if(n == 1)
    return mover(origem, destino);

  resolver(n-1, origem, aux, destino);
  mover(origem, destino);
  resolver(n-1, aux, destino, origem);
}

int main()
{
  resolver(3, 1, 3, 2);
  return 0;
}
