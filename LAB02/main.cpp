#include <cstdio>
#include <ctime>
#include <omp.h>
#include <iostream>

long long num_steps = 100000000;
double step;

int main()
{
	clock_t start, stop;
	volatile double x;	//kompilator nie zaklada ze zmienna moze sie zmieniac poza obszarem gdzie wytepuje
	long double pi, sum = 0.0, tablica[100];
	for (int j = 0; j < 100; j++)
		tablica[j] = 0;
	int i;
	step = 1. / (double)num_steps;
	omp_set_num_threads(2);	//ile watkow
	for (int j = 0; j < 30; j++) {
		start = clock();
		sum = 0.0;
#pragma omp parallel
		{
			int id = omp_get_thread_num();	//raz wywolana

			tablica[id + j] = 0;
#pragma omp for
			//powstaja kopie zmiennej sum
			for (int i = 0; i < num_steps; i++) {

				double x = (i + .5) * step;
				//lokalny sum
				tablica[id + j] += 4.0 / (1. + x*x);
			}
#pragma omp atomic
			sum += tablica[id + j];	//tablica -> zamek -> odczyt z pamieci -> zmienic wartosz -> zmiana wartosci -> zciagam blokade
		}

		pi = sum * step;
		stop = clock();

		//printf("PI: %15.12f\n", pi);
		printf("Czas dla j = %d: %llf\n", j, (double)(stop - start) / 1000.);
	}
	system("pause");
}

/*
    clock_t start, stop;
    volatile double x;	//kompilator nie zaklada ze zmienna moze sie zmieniac poza obszarem gdzie wytepuje
    long double pi, sum = 0.0, tablica[100];
    
    for (int j = 0; j < 100; j++)
        tablica[j] = 0;
    
    int i;
    step = 1. / (double)num_steps;
    start = clock();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();	//raz wywolana
        #pragma omp for
        //powstaja kopie zmiennej sum
        for (int i = 0; i < num_steps; i++) {
            double x = (i + .5) * step;
            //lokalny sum
            tablica[id] += 4.0 / (1. +x*x);
        }
        #pragma omp atomic
            sum += tablica[id];	//tablica -> zamek -> odczyt z pamieci -> zmienic wartosz -> zmiana wartosci -> zciagam blokade
    }
    pi = sum * step;
    stop = clock();

    printf("PI: %llf\n", pi);
    printf("Czas: %llf\n", (double)(stop - start) / 1000.);
    system("pause");
*/

/*
    clock_t start, stop;
    volatile double x;	//kompilator nie zaklada ze zmienna moze sie zmieniac poza obszarem gdzie wytepuje
    double pi, sum = 0.0, tablica[100];
    for (int j = 0; j < 100; j++)
    tablica[j] = 0;
    int i;
    step = 1. / (double)num_steps;
    start = clock();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();	//raz wywolana
        #pragma omp for
        //powstaja kopie zmiennej sum
        for (int i = 0; i < num_steps; i++) {
            double x = (i + .5) * step;
            //lokalny sum
            tablica[id] += 4.0 / (1. +x*x);
        }
        #pragma omp atomic
            sum += tablica[id];	//tablica -> zamek -> odczyt z pamieci -> zmienic wartosz -> zmiana wartosci -> zciagam blokade
    }
    pi = sum * step;
    stop = clock();

    printf("%lf\n", pi);
    system("pause");
*/



/*
int main()
{
    clock_t start, stop;
    volatile double x;	//kompilator nie zaklada ze zmienna moze sie zmieniac poza obszarem gdzie wytepuje
    double pi, sum = 0.0;
    int i;
    step = 1. / (double)num_steps;
    start = clock();
    #pragma omp parallel
    {
        //double suml = 0;
        #pragma omp  for reduction(+:sum)
        //powstaja kopie zmiennej sum
        for (int i = 0; i < num_steps; i++) {

            double x = (i + .5) * step;
            //lokalny sum
            sum += 4.0 / (1. +x*x);
        }
        //scalenie
        //globalna sum
    }
    pi = sum * step;
    stop = clock();

    printf("%lf\n", pi);
    system("pause");
}
*/

/*
int main()
{
    clock_t start, stop;
    volatile double x;	//kompilator nie zaklada ze zmienna moze sie zmieniac poza obszarem gdzie wytepuje
    double pi, sum = 0.0;
    int i;
    step = 1. / (double)num_steps;
    start = clock();
    #pragma omp parallel
    {
        double suml = 0;

        #pragma omp  for reduction(+:sum)
        for (int i = 0; i < num_steps; i++) {
            double x = (i + .5) * step;
            suml += 4.0 / (1. +x*x);
        }
        #pragma omp atomic
        sum += suml;
    }
    pi = sum * step;
    stop = clock();

    printf("%lf\n", pi);
    system("pause");
}
*/


/*
#include <cstdio>
#include <ctime>
#include <omp.h>
#include <iostream>

long long num_steps = 100000000;
double step;

int main()
{
	clock_t start, stop;
    volatile double x;	//kompilator nie zaklada ze zmienna moze sie zmieniac poza obszarem gdzie wytepuje
    double pi, sum = 0.0;
    int i;
    step = 1. / (double)num_steps;
    start = clock();
    #pragma omp parallel
    {
        double suml = 0;

        #pragma omp  for reduction(+:sum)
        for (int i = 0; i < num_steps; i++) {

        double x = (i + .5) * step;
        suml += 4.0 / (1. +x*x);
        }
        #pragma omp atomic
        sum += suml;
    }
    pi = sum * step;
    stop = clock();

    printf("%lf\n", pi);
    system("pause");
}
*/
