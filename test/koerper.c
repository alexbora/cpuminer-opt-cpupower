/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : koerper
 * @created     : Joi Apr 18, 2024 20:01:27 EEST
 */

#include <stdlib.h>

typedef struct {
  int left, right;
} Eye;

typedef struct Mouth {
  int size;
  char *color, *shape;
} Mouth;

typedef struct Nose *Nose;
typedef struct Arms *Arms;

typedef struct {
  Eye eyes[2];
  Mouth mouth;
  Nose nose;
} Head;

typedef struct {
  Head *head;
  int height;
  int weight;
} Body;

Body init(int height, int weight) {
  Body body;
  Head head = {
      {0, 1},
      {0, "red", "round"},
      0,
  };

  body.height = height;
  body.weight = weight;
  return body;
}

int main(int argc, char *argv[]) { return 0; }
