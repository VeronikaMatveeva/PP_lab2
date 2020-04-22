#include <iostream>
#include <ctime>
#include <string>
#include <mpi.h>
#include <omp.h>

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);
	int seed = (int)time(0);
	srand(time(0));
	int p_rank, t_rank, total;
	MPI_Comm_size(MPI_COMM_WORLD, &total);
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
#pragma omp parallel num_threads(4) private(t_rank)
	{
#pragma omp critical 
		{	
			t_rank = omp_get_thread_num();
			srand(31 * seed + t_rank * 999983 + p_rank*991);
			int num = rand();
			std::cout << "I am " << t_rank << " thread from " << p_rank << " process, my random number = " << num << std::endl;
		}
	}
	MPI_Finalize();
}

