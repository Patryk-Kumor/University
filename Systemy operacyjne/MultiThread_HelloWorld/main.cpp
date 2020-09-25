#include "iostream"
#include <pthread.h>

using namespace std;

#define NUM_THREADS 4

void *Hello(void *argument_id)
{
   cout << "Hello World!" << " (Thread:" << argument_id << ") " << "\n";
   pthread_exit(NULL);
}

int main(void)
{
   cout << "Starting: main()" << "\n";
   pthread_t threads[NUM_THREADS];
   int i;
   for (i=0; i<NUM_THREADS; i++)
   {
      cout << "Creating thread:" << i << "\n";
      pthread_create(&threads[i], NULL, Hello, &threads[i]);
   }
   for (i=0; i<NUM_THREADS; i++)
   {
      pthread_join(threads[i],NULL);
   }
   return 0;
}

