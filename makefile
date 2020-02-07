TiledMatrixMM:	MatrixMMParallelism.cpp
	g++ -Wall -std=c++11 -O3 MatrixMMParallelism.cpp -o TiledMatrixMM
	
clean:
	rm TiledMatrixMM
