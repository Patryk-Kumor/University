#include "iostream"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int ended;
int how_many;
int g_P;
int g_Z;

void *Cook(void *arg)
{ 
   int i;

   for (i=0; i<365; i++)
   {
      pthread_mutex_lock(&mutex);
      if (g_Z > 0)
      {   
         int J = rand()%6+1;
         g_P += J;
         g_Z--;
         cout << "Kucharz przyrządził [" << J << "] sztuk jedzenia (Jedzenia w sumie: ";
         cout << g_P << ").\n";
      }
      else
      {   
         cout << "Brak zwierzyny. Kucharz nic nie mógł zrobić.\n"; 
      }
      pthread_mutex_unlock(&mutex);

      //usleep(1); #to mogłoby nam pomóc "wymusić" zmianę wątku wykonywanego, ale w zasadzie nie jest to wymagane do poprawnego działania
      // Zmniejsza to prawdopodobieństwo wykonywania jedej ogólnej iteracji (jednodniowy cykl życia) w całości

      pthread_mutex_lock(&mutex);
      if (g_P > 0)
      {
         g_P--;
         cout << "Kucharz zjada pożywienie (pozostało: " << g_P << ") i idzie spać.\n";
         pthread_mutex_unlock(&mutex);
      }
      else 
      {
         cout << "Kucharz nie może się pożywić, więc opuszcza osadę.\n";
         how_many--;
         pthread_mutex_unlock(&mutex);
	 pthread_exit(NULL);
      }

      usleep(100);
   }
   return NULL;
}

void *Hunter(void *arg)
{ 
   int i;

   for (i=0; i<365; i++)
   {
      pthread_mutex_lock(&mutex);
      int H = rand()%6+1;
      int Z = rand()%6+1;
      if (H > Z)
         {  
            g_Z++;
            cout << "Łowca zdobywa zwierzynę (W sumie [" << g_Z << "] zwierzyny).\n";
         }
      else
         { 
            cout << "Łowca nic nie upolował.\n";
         }
      pthread_mutex_unlock(&mutex);
	
      //usleep(1);
      pthread_mutex_lock(&mutex);

      if (g_P > 0)
      {
         g_P--;
         cout << "Łowca zjada pożywienie (pozostało: " << g_P << ") i idzie spać.\n";
         pthread_mutex_unlock(&mutex);
      }
      else 
      {
         cout << "Łowca nie może się pożywić, więc opuszcza osadę.\n";
         how_many--;
         pthread_mutex_unlock(&mutex);
	 pthread_exit(NULL);
      }
      usleep(100);
   }
   return NULL;
}



int main(int argc, char* argv[])
{
	if (argc == 5)
    {
       int H = atoi(argv[1]); int C = atoi(argv[2]); g_Z = atoi(argv[3]); g_P = atoi(argv[4]);
       int beg_Z = g_Z; int beg_P = g_P;

       if ((H>=0)&&(C>=0)&&(g_Z>=0)&&(g_P>=0))
       {
           cout << "Rozpoczęcie symulacji osadnictwa dla podanych argumentów:\n";
           cout << "Myśliwi: " << H << ", kucharze: " << C << "\n";
           cout << "Zwierzyna: " << g_Z << ", pożywienie: " << g_P << "\n\n";

           how_many=H+C; 

           pthread_t threadsH[H];
           pthread_t threadsC[C];
           int i; 
           for (i = 0; i < H; i++)
           {   
              pthread_create(&threadsH[i],NULL,Hunter,&threadsH[i]);
           }
           for (i = 0; i < C; i++)
           {   
              pthread_create(&threadsC[i],NULL,Cook,&threadsH[i]);
           }
           for (i = 0; i < H; i++)
           {   
              pthread_join(threadsH[i],NULL);
           }
           for (i = 0; i < C; i++)
           {   
              pthread_join(threadsC[i],NULL);
           } 

		   cout << "\nPODSUMOWANIE: \n" << "Grę przeżyło [" << how_many << "] osób.\n";
                   cout << "Pozostałe zasoby: zwierzyna [" << g_Z << "], pożywienie ["<< g_P << "]\n";
                   cout << "(Początkowe argumenty: " << H << " " << C << " ";
                   cout << beg_Z << " " << beg_P << ")\n";
       }
       else { cout << "Niepoprawne argumenty";}
    }
    else { cout << "Niepoprawna liczba argumentów";}
}

