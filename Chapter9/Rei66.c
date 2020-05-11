#include <stdio.h> 

void backtrack(int);

#define N 8
int column[N+1];  // whether queen is here or not
int rup[2*N+1];   // whether queen is right-up cross line
int lup[2*N+1];   // whether queen is left-up cross line
int queen[N+1];   // queen position

void main()
{
  int i;
  for(i=1; i<=N; i++)
  {
    column[i] = 1;
  }
  for(i=1; i<=2*N; i++)
  {
    rup[i] = lup[i] = 1;
  }

  backtrack(1);
}

void backtrack(int i)
{
  int j, x, y;
  static int num = 0;

  if(i>N)
  {
    printf("\n answer %d \n", ++num); // display answer
    for(y=1; y<=N; y++)
    {
      for(x=1; x<=N; x++)
      {
        if(queen[y]==x)
          printf(" Q");
        else
          printf(" .");
      }
      printf("\n");
    }
  }

  else
  {
    for(j=1; j<=N; j++)
    {
      if(column[j]==1 && rup[i+j]==1 && lup[i-j+N]==1)
      {
        queen[i] = j;                           // (i, j) : queen position
        column[j] = rup[i+j] = lup[i-j+N] = 0;  // go next part
        backtrack(i+1);
        column[j] = rup[i+j] = lup[i-j+N] = 1;  // back before part
      }
    }
  }
}
