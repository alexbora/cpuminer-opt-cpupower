/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : lottery
 * @created     : Joi Apr 11, 2024 20:01:45 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int red, white;
} Lottery;

int lottery(Lottery *lottery) { return lottery->red * 10 + lottery->white; }

Lottery *lottery_create(int red, int white) {
  Lottery *lottery = malloc(sizeof(Lottery));
  if (lottery == NULL) {
    return NULL;
  }
  lottery->red = red;
  lottery->white = white;
  return lottery;
}

void lottery_destroy(Lottery *lottery) { free(lottery); }

void shuffle(int *array, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int black_jack() {
  char suits[4][16] = {"Hearts", "Diamonds", "Clubs", "Spades"};
  char numbers[13][16] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                          "8",   "9", "10", "Jack", "Queen", "King"};

  int draw = rand() % 52;
  int sum = 0;
  sum = atoi(numbers[draw % 13]);

  printf("%s of %s\n", numbers[draw % 13], suits[draw / 13]);
  return sum;
}

int main() {
  srand(time(NULL));
  int i;
  int numbers[50];
  for (i = 0; i < 50; i++) {
    numbers[i] = i + 1;
  }
  shuffle(numbers, 50);
  for (i = 0; i < 6; i++) {
    printf("%d ", numbers[i]);
  }
  printf("\n");
  black_jack();

  int sum = 0;
  do {
    sum += black_jack();
  } while (sum < 21);

  return 0;
}
