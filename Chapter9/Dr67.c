#include <stdio.h>

#define limit 42  // change 
#define n 3       // kinds of coin

void main()
{
  int size[] = { 1, 10, 25};
  int value[ limit + 1 ];   // number of coin
  int  item[ limit + 1 ];   // coin number
  int i, s, p, newvalue;

  for (s=0; s<=limit; s++)
  {
    value[s] = s;   // initial value
  }
  for (i=0; i<n; i++) // coin number
  {
    for (s=size[i]; s<=limit; s++)  // nupback size
    {
      p = s - size[i];
      newvalue = value[p] + 1;
      if (newvalue <= value[s])
      {
        value[s] = newvalue;
        item[s] = i;
      }
    }
  }

  printf("numer of coin = %3d : ", value[limit]);
  for (s = limit; s > 0; s = s - size[item[s]])
  {
    printf("%3d", size[item[s]]);
  }

  printf("\n");
}


