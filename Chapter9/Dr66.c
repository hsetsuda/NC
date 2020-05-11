#include <stdio.h> 

void backtrack(int, int);

#define N 5

int m[N+4][N+4];                              // board
int dx[8] = { 2, 1, -1, -2, -2, -1,  1,  2};  // knight x movement
int dy[8] = { 1, 2,  2,  1, -1, -2, -2, -1};  // knight y movement

void main()
{
  int i, j;

  for(i=0; i<=N+3; i++)
  {
    for(j=0; j<=N+3; j++)
    {
      if(2<=i && i<= N+1 && 2<=j && j<= N+1)  
      {
        m[i][j] = 0;  // on the board
      }
      else
      {
        m[i][j] = 1;  // wall
      }
    }
  }

  backtrack(2, 2);
}

void backtrack(int x, int y)
{
  int i, j, k;
  static int count = 0; // must "static"
  static int num = 0; // must "static"

  if(m[x][y]==0)
  {
    m[x][y]=++count;   // knight visiting log on the board
    if(count==N*N)
    {
      printf("\n answer %d \n", ++num); // display answer
      for(i=2; i<=N+1; i++)
      {
        for(j=2; j<=N+1; j++)
        {
          printf("%4d", m[i][j]);
        }
        printf("\n");
      }
    }

    else
    {
      for(k=0; k<8; k++)  // select next going
      {
        backtrack(x+dx[k], y+dy[k]);
      }
    }
    m[x][y] = 0;  // back one step
    count--;
  }
}
