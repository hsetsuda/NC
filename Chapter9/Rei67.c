#include <stdio.h>

#define limit 8 // weight limit of napzack
#define n 5     // kind of item
#define min 1   // min of weight

void main()
{
  struct body
  {
    char name[20];
    int weight;
    long price;
  }a[] = {
    { "plum", 4, 4500},
    { "apple", 5, 5700},
    { "orange", 2, 2250},
    { "strawberry", 1, 1100},
    { "melon", 6, 6700}
  };
  long newvalue;
  long value[limit+1];
  int item[limit+1];
  int i, s, p;

  for(s=0; s<=limit; s++)
  {
    value[s] = 0; //  inital value
  }
  for(i=0; i<n; i++)
  {
    for(s=a[i].weight; s<=limit; s++)
    {
      p = s - a[i].weight;
      newvalue = value[p] + a[i].price;
      if(newvalue>value[s])
      {
        value[s] = newvalue;  // re-optimize
        item[s] = i;
      }
    }
  }

  printf("  selected fruits | price \n");
  for(s=limit; s>=min; s=s-a[item[s]].weight)
  {
    printf("%10s | %5ld\n", a[item[s]].name, a[item[s]].price);
  }
  printf(" sum price %5ld\n", value[limit]);
}


