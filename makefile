all:
	g++ -fopenmp -std=c++11 src/*.cc -o pso

clean:
	@rm -vf *~ src/*~ pso
