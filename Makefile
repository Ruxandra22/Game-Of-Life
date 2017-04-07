all: build

build: serial parallel

serial: g_serial.c
	gcc -o g_serial g_serial.c

parallel: g_omp.c
	gcc -fopenmp -o g_omp g_omp.c

clean:
	rm -rf g_serial g_omp out*.txt
