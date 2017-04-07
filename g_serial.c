#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Functie prin care verific daca fisierul de intrare se poate deschide.
void check_file(FILE *f) {

	if(f == NULL) {
		printf("The file cannot be opened!\n");
		exit(0);
	}
} 

int main(int argc, char** argv) {

	//In cazul in care, la rulare sunt date argumentele gresite,
	//va aparea un mesaj de eroare si programul se va inchide
	if(argc < 4) {
		printf("Wrong arguments!\n");
		printf("USAGE: ./g_serial input_file nr_iterations output_file\n");
		exit(0);
	}


	FILE *input_file, *output_file;
	char file_line[10];
	const char delim[2] = " ";
	char *token;
	int L, C;			// numarul de linii si de coloane ale matricii
	int nr_iteratii;
	nr_iteratii = atoi(argv[2]);

	input_file = fopen(argv[1], "r");
	check_file(input_file);
	fgets(file_line, 10, input_file);

	//despartim cele 2 valori din string-ul file_line
	token = strtok(file_line, delim);
	L = atoi(token);
	token = strtok(NULL, delim);
	C = atoi(token);

	//DECLARAM MATRICEA SI MATRICEA BORDATA -> alocare dinamica

	int i, j;
	char c;
	int** borded_map;
	int** copy_borded_map;
	
	borded_map = malloc((L + 2) * sizeof(int *));
	for(i = 0; i < L + 2; i ++) {
		borded_map[i] = calloc((C + 2), sizeof(int));
	}

	copy_borded_map = malloc((L + 2) * sizeof(int *));
	for(i = 0; i < L + 2; i ++) {
		copy_borded_map[i] = calloc((C + 2), sizeof(int));
	}

	//citim toata matricea din fisier

	for(i = 1; i <= L; i ++) {
		for(j = 1; j <= C; j ++) {
			fscanf(input_file, " \n%c", &c);
			if(c == 'X') {
				borded_map[i][j] = 1;
			}
			else if(c == '.') {
				borded_map[i][j] = 0;
			}
		}
	}

	int count = 0;

	//Rezolv problema pentru un numar dat de pasi
	for(count = 0; count < nr_iteratii; count ++) {

		//matricea trebuie bordata cu noile elemente
		for(i = 1; i < L + 1; i ++) {
			borded_map[i][0] = borded_map[i][C];		//coloana stanga
			borded_map[i][C + 1] = borded_map[i][1];	//coloana dreapta
		}

		for(i = 1; i < C + 1; i ++) {
			borded_map[0][i] = borded_map[L][i];		//linie sus
			borded_map[L + 1][i] = borded_map[1][i];	//linie jos
		}

		borded_map[0][0] = borded_map[L][C];			//colt stanga sus
		borded_map[L + 1][0] = borded_map[1][C];		//colt stanga jos
		borded_map[0][C + 1] = borded_map[L][1];		//colt dreapta sus
		borded_map[L + 1][C + 1] = borded_map[1][1];	//colt dreapta jos


		//tebuie sa ne cream o copie a matricii bordate inainte
		//de a aplica regulile de ALIVE si DEAD
		for(i = 0; i < L + 2; i ++) {
			for(j = 0; j < C + 2; j ++) {
				copy_borded_map[i][j] = borded_map[i][j];
			}
		}

		//variabila pentru a calcula numarul de vecini ALIVE
		int sum = 0;
		
		//CONDITIILE PENTRU VECINI
		
		for(i = 1; i <= L; i ++) {
			for(j = 1; j <= C; j ++) {

				sum = copy_borded_map[i - 1][j -1] +
					  copy_borded_map[i - 1][j] + 
					  copy_borded_map[i -1][j + 1] + 
					  copy_borded_map[i][j - 1]+
					  copy_borded_map[i][j + 1] + 
					  copy_borded_map[i + 1][j - 1] + 
					  copy_borded_map[i + 1][j] +
					  copy_borded_map[i + 1][j + 1];

				//daca are mai putin de 2 vecini in viata
				//nu conteaza daca celula este ALIVE(1) sau DEAD(0)
				if(sum < 2) {
					borded_map[i][j] = 0;
				}

				//daca e ALIVE(1) si are 2 sau 3 vecini ALIVE => ALIVE
				if(copy_borded_map[i][j] == 1 && (sum == 2 || sum == 3)) {
					borded_map[i][j] = 1;
				}

				//daca are mai mult de 3 vecini ALIVE => DEAD
				if(sum > 3) {
					borded_map[i][j] = 0;
				}

				//daca e DEAD(0) si are 3 vecini ALIVE => ALIVE
				if(copy_borded_map[i][j] == 0 && sum == 3)  {
					borded_map[i][j] = 1;
				}
			}
		}
	}

	//SCRIEREA IN FISIER
	output_file = fopen(argv[3], "w");

	for(i = 1; i <= L; i ++) {
		for(j = 1; j <= C; j ++) {
			//daca este 0 -> punem in fisier "." urmat de spatiu
			if(borded_map[i][j] == 0) {
				fprintf(output_file, "%c ", '.');
			}
			//daca este 1 -> punem in fisier "X" urmat de spatiu
			else if(borded_map[i][j] == 1) {
				fprintf(output_file, "%c ", 'X');
			}
		}
		fprintf(output_file, "\n");
	}

	//eliberarea memoriei pentru borded_map
	for(i = 0; i < L + 2; i ++) {
		free(borded_map[i]);
	}
	free(borded_map);

	//eliberarea memoriei pentru copy_borded_map
	for(i = 0; i < L + 2; i ++) {
		free(copy_borded_map[i]);
	}
	free(copy_borded_map);

	//inchiderea fisierelor
	fclose(output_file);
	fclose(input_file);

	return 0;
}	