#include "kernel/types.h"
#include "user/user.h"

int main() {
  int i, space, k = 0;
  int rows = 5;
  for (i = 1; i <= rows; ++i, k = 0) {
    for (space = 1; space <= rows - i; ++space) {
      printf("  ");
    }
    while (k != 2 * i - 1) {
      printf("* ");
      ++k;
    }
    printf("\n");
  }
  exit(0);
}