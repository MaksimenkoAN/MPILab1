#include <iostream>

#include <iomanip>

#include <fstream>

#include <cstdlib>

#include <ctime>

#include <cassert>

#include <math.h>

#include <windows.h>

#include <mpi.h>

#include <locale>

#include <vector>

using namespace::std;

int myRank;

int numProcs;

int main(int argc, char* argv[])

{
	int n;

	int summ = 0;

	double endwtime = 0.0;

	double startwtime = 0.0;

	int result = 0;

	double mediumnum = 0.0;

	setlocale(LC_ALL, "Russia");

	int err = MPI_SUCCESS;

	MPI_Status status;

	MPI_Init(&argc, &argv);

	if (MPI_Comm_size(MPI_COMM_WORLD, &numProcs) != MPI_SUCCESS) return -1; // number of processes involved in run 

	if (MPI_Comm_rank(MPI_COMM_WORLD, &myRank) != MPI_SUCCESS) return -1; // my process id: 0 <= myRank < numProcs 

	if (myRank == 0)
	{

		cin >> n;

		startwtime = MPI_Wtime();

	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

		double* vector = new double[n];

		for (int i = 0; i < n; i++)
			vector[i] = i+1;


	for (int i = myRank; i < n; i += numProcs)
		summ += vector[i];

	MPI_Reduce(&summ, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myRank == 0)

	{

		mediumnum = (result*1.0/ n);

		cout << mediumnum << endl;

		endwtime = MPI_Wtime();

		cout << (endwtime - startwtime) << endl;

	}

	MPI_Finalize();

	delete[] vector;

	return 0;

}