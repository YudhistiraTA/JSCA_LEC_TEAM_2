#include <stdio.h>

int main() {
  int x = 10;
  int *p = &x;
  int **pp = &p;
  int ***ppp = &pp;

  printf("Value of x: %d\n", x); // 10
  printf("Address of x: %p\n\n", &x); // x memory

  printf("Value of p: %p\n", p); // address of x
  printf("ACTUAL Value of *p: %d\n", *p); // 10
  printf("Address of p: %p\n\n", &p); // p memory

  printf("Value of pp: %p\n", pp); // address of p
  printf("ACTUAL Value of *pp: %p\n", *pp); // address of x
  printf("ACTUAL Value of **pp: %d\n", **pp); // 10
  printf("Address of pp: %p\n\n", &pp); // pp memory

  printf("Value of ppp: %p\n", ppp); // address of pp
  printf("ACTUAL Value of *ppp: %p\n", *ppp); // address of p
  printf("ACTUAL Value of **ppp: %p\n", **ppp); // address of x
  printf("ACTUAL Value of ***ppp: %d\n", ***ppp); // address of x
  printf("Address of ppp: %p\n", &ppp); // ppp memory

  return 0;
}