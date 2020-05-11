#include <stdio.h>

void main()
{
  int man, computer, M, judge;
  int table[3][3] = {   // tactics table
                      {0, 0, 0},
                      {0, 0, 0},
                      {0, 0, 0}
                    };
  int hist[3] = {0, 0, 0};  // win lose persent
  char *hand[3] = {"rock", "sisors", "paper"};
  
  M = 0;
  while(1)
  {
    if (table[M][0]>table[M][1] && table[M][0]>table[M][2])
      computer = 2;
    else if(table[M][1]>table[M][2])
      computer = 0;
    else
      computer = 1;

    printf("0:rock, 1:sisors, 2:paper \n");
    printf("which? : ");
    scanf("%d", &man);
    putchar('\n');

    printf("computer select %s\n", hand[computer]);

    judge = (computer-man+3) % 3;
    switch(judge)
    {
      case 0: 
        printf("Draw. \n"); break;
        
      case 1:
        printf("You win. \n"); break;

      case 2:
        printf("Computer win. \n"); break;
    }
    
    hist[judge]++;
    table[M][man]++; //  learning
    M = man;
    printf("--- %d win %d lose %d draw ---\n\n", hist[1], hist[2], hist[0]);
  }
}


