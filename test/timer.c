/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : timer
 * @created     : Miercuri Apr 17, 2024 21:07:43 EEST
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned interval;
  void (*proc)(void);
} Timer;

void fnA() { printf("A\n"); }
void fnB() { printf("B\n"); }

Timer t[] = {{1, fnA}, {2, fnB}};

int main(int argc, char *argv[]) {
  for (int i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
    if (t[i].proc != NULL) {
      t[i].proc();
    }
  }
  return 0;
}

