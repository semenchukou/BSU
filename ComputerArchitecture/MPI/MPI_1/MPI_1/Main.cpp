#include "mpi.h"
#include <iostream>
#include <fstream>
#include "Process.h"

using namespace std;

int L;

int main(int argc, char* argv[])
{
	auto process = MPI::Process();
	double* vect_a = nullptr;
	double* vect_b = nullptr;
	double* result = nullptr;
	int* sendcount = new int[process.ProcessCount()];//массив отправляемых кусков
	int *index = new int[process.ProcessCount()];//индексы начал этих кусочков
	if (process.IsMaster())
	{
		ifstream fin("task1_input.txt");
		fin >> L;
		vect_a = new double[L];
		vect_b = new double[L];
		result = new double[L];
		for (int i = 0; i < L; i++)
			fin >> vect_a[i];
		for (int i = 0; i < L; i++)
			fin >> vect_b[i];
		fin.close();

		int step = L / process.ProcessCount();
		int buff = L % process.ProcessCount();
		if (buff > 0)
		{
			sendcount[0] = step + 1;
			buff--;
		}
		else sendcount[0] = step;
		index[0] = 0;
		for (int i = 1; i < process.ProcessCount(); i++)
		{
			if (buff > 0)
			{
				sendcount[i] = step + 1;
				buff--;
			}
			else sendcount[i] = step;
			index[i] = index[i - 1] + sendcount[i - 1];
			MPI_Send(&sendcount[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);//указ на начало данных, длина, тип, ранг принимающего
		}
	}

	int k;

	if (process.IsMaster())
	{
		k = sendcount[MPI::MasterRank];
	}
	else
	{
		MPI_Recv(&k, 1, MPI_INT, MPI::MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//принимает, указ на начало данных, длина амссива данных, тип, ранг отправившего
	}
	double* getbuff_a = new double[k];
	double* getbuff_b = new double[k];
	MPI_Scatterv(vect_a, sendcount, index, MPI_DOUBLE, getbuff_a, k, MPI_DOUBLE, MPI::MasterRank, MPI_COMM_WORLD);//отправляет заданные куски
	MPI_Scatterv(vect_b, sendcount, index, MPI_DOUBLE, getbuff_b, k, MPI_DOUBLE, MPI::MasterRank, MPI_COMM_WORLD);
	double* send_buf = new double[k];
	for (int i = 0; i < k; i++)
		send_buf[i] = getbuff_a[i] * getbuff_b[i];

	MPI_Gatherv(send_buf, k, MPI_DOUBLE, result, sendcount, index, MPI_DOUBLE, MPI::MasterRank, MPI_COMM_WORLD);//отукда, сколько, куда, массивы
	delete[] getbuff_a;
	delete[] getbuff_b;
	delete[] send_buf;


	if (process.IsMaster())
	{
		ofstream fout("task1_output.txt");
		double S = 0;
		for (int i = 0; i < L; i++)
		{
			S += result[i];
		}
		fout << S;

		delete[] vect_a, vect_b;
		delete[] result;
		fout.close();
	}
	system("pause");
	return 0;
}