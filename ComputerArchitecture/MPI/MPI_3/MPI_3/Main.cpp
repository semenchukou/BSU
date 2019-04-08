#include "mpi.h"
#include <iostream>
#include <fstream>
#include "Process.h"
#include <vector>

using namespace std;

int L = 0;

int isPrime(int buff)
{
	for (int i = 2; i < abs(sqrt(buff)) + 1; i++)
	{
		if (buff % i == 0 && i != buff)
			return 0;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	auto process = MPI::Process();
	int* vect_a = nullptr;
	int* result = nullptr;
	vector<int> v;
	int *sendcount = new int[process.ProcessCount()];//подмассивов объемы
	int *index = new int[process.ProcessCount()];//индексы
	if (process.IsMaster())
	{
		ifstream fin("task3_input.txt");
		int buffread;
		while (fin >> buffread)
		{
			v.push_back(buffread);
			L++;
		}
		vect_a = v.data();
		result = new int[L];
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
			MPI_Send(&sendcount[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	int k;

	if (process.IsMaster())
	{
		k = sendcount[MPI::MasterRank];
	}
	else
	{
		MPI_Recv(&k, 1, MPI_INT, MPI::MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	int* getbuff_a = new int[k];
	MPI_Scatterv(vect_a, sendcount, index, MPI_INT, getbuff_a, k, MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);
	int* send_buf = new int[k];
	for (int i = 0; i < k; i++)
		send_buf[i] = isPrime(getbuff_a[i]);

	MPI_Gatherv(send_buf, k, MPI_INT, result, sendcount, index, MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);
	delete[] getbuff_a;
	delete[] send_buf;


	if (process.IsMaster())
	{
		ofstream fout("task3_output.txt");
		for (int i = 0; i < L; i++)
		{
			fout << result[i] << " ";
		}
		delete[] result;
		fout.close();
	}
	//system("pause");
	return 0;
}