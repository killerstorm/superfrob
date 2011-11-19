#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

volatile int c1, r1;

void* ThreadFun(void* threadid) {
  for (;;) {
    while (c1 != 1);// asm volatile ("mfence");
    c1 = 0;
    r1 = 1;
    //asm volatile ("sfence");
  }
}

unsigned long long rdtsc(void) {
    unsigned long lo, hi;
    __asm__ __volatile__ (      // serialize
    "xorl %%eax,%%eax \n        cpuid"
    ::: "%rax", "%rbx", "%rcx", "%rdx");
    /* We cannot use "=A", since this would use %rax on x86_64 and return only the lower 32bits of the TSC */
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return (unsigned long long)hi << 32 | lo;
 }

int main () {
  pthread_t thread;
  c1 = 0; r1 = 0;
  pthread_create(&thread, NULL, ThreadFun, NULL);
  sleep(1);
  unsigned long long start, end;
  int n_iter = 1000000;
  start = rdtsc();
  for (int i = 0; i < n_iter; ++i) {
    c1 = 1;
    //asm volatile ("sfence");
    while (r1 != 1);
    r1 = 0;
  }
  end = rdtsc();
  printf("%g\n", double(end - start)/double(n_iter));
  return 0;
}
