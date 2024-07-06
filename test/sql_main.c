/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sql_main
 * @created     : Duminică Mar 31, 2024 07:33:34 EEST
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

extern void *main_x(void *);

struct Thr {
  pthread_t id;
  int id2;
};

int main(int argc, char *argv[]) {
  struct Thr t = (struct Thr){0, 1};

  pthread_create(&t.id, NULL, main_x, &t);
  getchar();
  pthread_join(t.id, NULL);

  return 0;
}
