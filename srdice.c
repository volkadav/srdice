#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifndef __APPLE__ // only use this on non-OSX
#include <unistd.h>
#endif

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

void usage(char* name) {
  printf("%s: a shadowrun 5th edition dice roller\n", name);
  printf("usage:\n");
  printf("\tskill checks: %s <integer # of dice>\n", name);
  printf("\tinitiative: %s -i <integer # of dice>\n", name);
}

int check_input(char* input) {
  for (int i = 0; i < strlen(input); i++) {
    if (!isdigit(input[i])) {
      return -1;
    }
  }
  return atoi(input);
}

int main(int argc, char** argv) {
  int die = 0;
  int initiative_mode = 0;

  switch (argc) {
    case 3:
        if (strcmp("-i", argv[1]) != 0) {
          usage(argv[0]);
          return EXIT_FAILURE;
        } 
        initiative_mode = 1;

        die = check_input(argv[2]);
        if (die == -1) {
          usage(argv[0]);
          return EXIT_FAILURE;
        }
        break;
    case 2:
        die = check_input(argv[1]); 
        if (die == -1) {
          usage(argv[0]);
          return EXIT_FAILURE;
        }
        break;
    default:
        usage(argv[0]);
        return EXIT_FAILURE;
  }

#ifdef __APPLE__
  sranddev();
#else
  srand(time(NULL) % getpid());
#endif

  int hits = 0;
  int glitches = 0;
  int roll = 0;
  int total = 0; // for initiative mode

  for (int i = 0; i < die; i++) {
    roll = (int)(((float)rand()/(float)RAND_MAX) * 6) + 1;

    if (initiative_mode) {
      total += roll;
    } else {
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
  }

  if (initiative_mode) {
    printf("%d\n", total);
  } else {
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
  }

  return EXIT_SUCCESS;
}
