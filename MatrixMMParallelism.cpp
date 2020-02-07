/*
* tiled matrix multiplication
* Peyton and Ryan
*/

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>

using namespace std;

void tileMM(float** C, float** A, float** B, int n, int tN);

void tileMMH(float** C, float** A, float** B, int i0, int i1, int j0, int j1, int k0, int k1);

int main(int argc, char *argv[])
{
	int matrixSize, tileSize, execTimes;

	if (argc < 3)
	{
		cout << "\nNot enough arguments for the program";
	}else{
		matrixSize = atoi(argv[1]);
		tileSize = atoi(argv[2]);
		execTimes = atoi(argv[3]);
	}

	mt19937 rand(time(0));
	
	//lines 34 - 58 create and fill matrices A and B
	float **A = new float*[matrixSize];
	for (int i = 0; i < matrixSize; i++)
	{
		A[i] = new float[matrixSize];
	}

	float **B = new float*[matrixSize];
	for (int i = 0; i < matrixSize; i++)
	{
		B[i] = new float[matrixSize];
	}

	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			A[i][j] = rand();
		}
	}

	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			B[i][j] = rand();
		}
	}

	//create matrix C
	float **C = new float*[matrixSize];
	for (int i = 0; i < matrixSize; i++)
	{
		C[i] = new float[matrixSize];
	}

	//start the timer
	chrono::high_resolution_clock::time_point t1 =
		chrono::high_resolution_clock::now();

	//run the interface function	
	for (int i = 0; i < execTimes; i++) {
		tileMM(C, A, B, matrixSize, tileSize);
	}

	//stop timing
	chrono::high_resolution_clock::time_point t2 =
		chrono::high_resolution_clock::now();

	//compute and print the elapsed time
	chrono::duration<double> time_span =
		chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cout << matrixSize << ", " << tileSize << ", " << execTimes << time_span.count()
		<< ", " << time_span.count() / execTimes << endl;

	return EXIT_SUCCESS;
}


//Interface function for tiled matrix multiplication
void tileMM(float** C, float** A, float** B, int n, int tN){
	int i0, i1, j0, j1, k0, k1;

	for (i0 = 0; i0 < n; i0 += tN) {
		i1 = i0 + tN - 1;
		if (i1 >= n)
		{
			i1 = n - 1;
		}
		for (j0 = 0; j0 <= n; j0 += tN) {
			j1 = j0 + tN - 1;
			if (j1 >= n)
			{
				j1 = n - 1;
			}
			for (k0 = 0; k0 <= n; k0 += tN) {
				k1 = k0 + tN - 1;
				if (k1 >= n)
				{
					k1 = n - 1;
				}
				tileMMH(C, A, B, i0, i1, j0, j1, k0, k1);
			}
		}
	}
}
//helper function for tiled matrix multiplication
void tileMMH(float** C, float** A, float** B, int i0, int i1, int j0, int j1, int k0, int k1){
	int i, j, k;

	for (i = i0; i <= i1; i++)
	{
		for (j = j0; j <= j1; j++)
		{
			if (k0 == 0)
			{
				C[i][j] == 0.0;
			}
			for (k = k0; k <= k1; k++)
			{
				C[i][j] = C[i][j] + A[i][k] + B[k][j];
			}
		}
	}
}
