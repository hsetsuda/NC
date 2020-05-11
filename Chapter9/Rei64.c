/*
 * -----------------------------
 *  odd number magic circle
 *  ----------------------------
 */
#include <stdio.h>

#define N 7     // n * n magic circle(n=3, 5, 7...)

void main()
{
  int hojin[N+1][N+1];
  int i, j, k;

  j = (N + 1) / 2;
  i = 0;
  for(k=1; k<N*N; k++)
  {
    if((k%N)==1)
    {
      i++;
    }
    else
    {
      i--;
      j++;
    }

    if(i==0)
    {
      i = N;
    }
    if(j>N)
    {
      j = 1;
    }
    hojin[i][j] = k;
  }

  printf("       odd number magic circle (N=%d)\n", N);
  for(i=i; i<=N; i++)
  {
    for(j=1; j<=N; j++)
    {
      printf("%4d", hojin[i][j]);
    }
    printf("\n");
  }
}
