#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <iostream>

#define X_ROUND 100000
#define Y_ROUND 1000
void proc1 () {
  int i,j;
  static int x[X_ROUND][Y_ROUND];
  for (i = 0; i < X_ROUND; i++) {
    for (j = 0; j < Y_ROUND; j++) {
      x[i][j] = i + j; }
  }
}

void proc2 () {
  int i,j;
  static int x[X_ROUND][Y_ROUND];
  for (j = 0; j < Y_ROUND; j++) {
     for (i = 0; i < X_ROUND; i++) {
       x[i][j] = i + j; }
   }
}

int main()
{
    std::chrono::steady_clock::time_point s1 = std::chrono::steady_clock::now();
    proc1();
    std::chrono::steady_clock::time_point f1 = std::chrono::steady_clock::now();
    auto gap1 = std::chrono::duration_cast<std::chrono::milliseconds>(f1 - s1).count();
    proc2();
    std::chrono::steady_clock::time_point f2 = std::chrono::steady_clock::now();

    auto gap2 = std::chrono::duration_cast<std::chrono::milliseconds>(f2 - f1).count();

    std::cout << "cost : " << gap1 << ", " << gap2 << std::endl;
}