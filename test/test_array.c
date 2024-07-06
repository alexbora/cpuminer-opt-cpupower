/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test_array
 * @created     : Miercuri Feb 28, 2024 07:16:25 EET
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
#define local static __attribute((visibility("hidden")))
#else
#define local static
#endif

#pragma weak fill_array

void fill_array(int *, int *, int);

void fill_array(int *in, int *out, int size) {
  for (int i = 0; i < size; i++) {
    out[i] = in[i];
  }
}

local void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void shuffle_array(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    int j = rand() % size;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

__attribute((visibility("hidden"))) static void shuffle_array_ex(int *in,
                                                                 int *out,
                                                                 size_t size) {
  for (size_t i = 0; i < size; i++) {
    out[i] = in[rand() % size];
  }
}

#if TEST == 1
#include <assert.h>
#pragma message "TESTING"
#endif

int main(int argc, char *argv[]) {
#define TEST 1
  srand(time(NULL));

  struct tm *timeinfo;
  time_t rawtime;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  printf("Current local time and date: %s", asctime(timeinfo));

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(arr) / sizeof(arr[0]);
  shuffle_array(arr, size);
  print_array(arr, size);

  int *arr2 = malloc(size * sizeof(int));
  shuffle_array_ex(arr, arr2, size);
  print_array(arr2, size);

  return 0;
}

#pragma weak fill_array
