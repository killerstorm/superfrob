#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

extern unsigned long long bounce_s_1();
extern void bounce_s_2();

void* thread_fun (void* p) {  bounce_s_2(); return NULL; }

int main () {
  pthread_t thread;
  pthread_create(&thread, NULL, thread_fun, NULL);
  sleep(1);
  unsigned long long a = bounce_s_1();
  double f = a;
  printf("%g\n", f/1000000.0);
  return 0;
}
