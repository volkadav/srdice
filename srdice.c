#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

int main(int argc, char** argv) {
  if (argc == 1) {
    printf("usage: %s N where N is number of dice to roll\n", argv[0]);
    return EXIT_FAILURE;
  }

  srand(time(NULL));

  int die = atoi(argv[1]);
  int hits = 0;
  int glitches = 0;
  int roll = 0;

  for (int i = 0; i < die; i++) {
    roll = (int)(((float)rand()/(float)RAND_MAX) * 6) + 1;
    printf("%d", roll);

    if (roll >= 5) {
      hits++;
      printf(" " GREEN "HIT" RESET);
    } else if (roll == 1) {
      glitches++;
      printf(" " YELLOW "GLITCH" RESET);
    }
    printf("\n");
  }

  if (hits > 0) {
    printf("hits: %d", hits);
    if (glitches*2 > die) {
      printf(" " RED "GLITCH" RESET);
    }
  } else {
    printf("No hits!");
    if (glitches*2 > die) {
      printf(" " RED "CRITICAL GLITCH!" RESET);
    }
  }

  printf("\n");
  return EXIT_SUCCESS;
}
