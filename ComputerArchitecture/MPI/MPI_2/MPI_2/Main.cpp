#include "Process.h"
#include <mpi.h>
#include <iostream>
#include <fstream>
using namespace std;

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();
		int L;
		int *xes;
		int *result;
		int *buffer;
		int processes = process.ProcessCount();
		if (process.IsMaster())
		{
			ifstream in;
			in.open("task2_input.txt");
			in >> L;
			int sliceSize = (L / processes) * (L + 1);
			int **table = new int*[processes];
			int *x = new int[L];
			int a;
			for (int i = 0; i < processes; ++i)
			{
				table[i] = new int[sliceSize];
				for (int k = 0; k < sliceSize; ++k)
				{
					in >> a;
					table[i][k] = a;
				}
			}
			for (int i = 0; i < L; ++i)
			{
				in >> a;
				x[i] = a;
			}

			result = new int[L / processes];
			Calculating(table[0], x, L + 1, L / processes, result);
			for (int i = 1; i < processes; ++i)
			{
				MPI_Send(table[i], sliceSize, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&L, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
				MPI_Send(x, L, MPI_INT, i, 2, MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Status status;
			MPI_Probe(MPI::MasterRank, 0, MPI_COMM_WORLD, &status);

			int dataLength;
			MPI_Get_count(&status, MPI_INT, &dataLength);

			buffer = new int[dataLength];
			MPI_Recv(buffer, dataLength, MPI_INT, MPI::MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&L, 1, MPI_INT, MPI::MasterRank, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			xes = new int[L];
			MPI_Recv(xes, L, MPI_INT, MPI::MasterRank, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			result = new int[L / processes];
			Calculating(buffer, xes, L + 1, L / processes, result);
		}

		int* data = new int[L];

		MPI_Gather(result, L / process.ProcessCount(), MPI_INT, data, L / process.ProcessCount(), MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);

		if (process.IsMaster()) 
		{
			ofstream out;
			out.open("task2_output.txt");
			for (int i = 0; i < L; ++i) 
			{
				out << data[i] << "  ";
			}
			out.close();
		}
		MPI_Finalize();

	}
private:
	static void Calculating(int *table, int *xes, int length, int count, int *result)
	{
		for (int i = 0; i < count; ++i)
		{
			int sum = 0;
			for (int k = 0 + i * length, s = 0; k < length - 1 + i * length; ++k, ++s)
			{
				sum += table[i] * xes[s];
			}
			result[i] = table[length - 1 + i * length] - sum;
		}
	}

};

int main()
{
	Program::Main();
	return 0;
}