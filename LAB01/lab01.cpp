// zad2

#include <iostream> // system()

#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 10000000;//1000000000;
double step;

int main(int argc, char* argv[])
{
	clock_t start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();

#pragma omp parallel //for // then i is private for thread
	{
		//region
		double suml = 0;
#pragma omp for
		for (i = 0; i < num_steps; i++)
		{
			double x = (i + .5)*step; // x must be private (add double)


			//#pragma omp atomic //Niepodzielnoosc uaktualnienia
			//sum += 4.0 / (1. + x*x);

			suml += 4.0 / (1. + x*x);
		}
#pragma omp atomic
		sum += suml;
	}

	pi = sum*step;
	stop = clock();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Czas przetwarzania wynosi %f sekund\n", ((double)(stop - start) / 1000.0));
	
	system("pause");

	return 0;
}


// zad1
/*
#include <stdio.h>
#include <iostream> // system()

#include <omp.h>

int main() {
	int i;	// shared

	omp_set_num_threads(4);	//thread numbers

#pragma omp parallel //project propertis -> C/C++ -> Language -> Open MP Support YES
	{		
		//int i; // local for thread
		//printf("Hello World\n");

//#pragma omp parallel //all thread have number 0
		//schedule(static) 1 blok iteracji oraz ... przydzial porowno
		// chodzi o zachowanie lokalnosci 
//#pragma omp for schedule(static, 1) // next instructions is for, then i (before #pragma omp parallel) is private variable
		//6 to jeden dostanie i watek jeden robi prace
		// 1 to all cos robi
//#pragma omp for schedule(dynamic, 5) // dynamicznie przydzielane zadania (czas przydzielania sie wydluzy)
		//przy konkretnych obliczeniach moze sie przydac == niedetermistyczny

#pragma omp for schedule(guided) // na poczatku duzo przydziela jak duzo iteracji

		for (i = 0; i < 6; i++)
			printf("Iter:%d wykonal watek %d\n", i, omp_get_thread_num());

		printf("GoodBye World\n");
	}

	system("pause");
}

*/