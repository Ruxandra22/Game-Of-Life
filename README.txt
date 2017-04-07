============================== GAME OF LIFE ===================================


===============================================================================
CUPRINS:

	1. Implementare seriala
	2. Implementare paralela


===============================================================================
1. Implementare seriala
	

	Dupa citirea din fisier a numarului de linii si de coloane si a matricii, am
alocat dinamic cele doua matrici pe care le folosesc in implementare:
		- borded_map -> matricea originala
		- copy_borded_map -> o copie a matricii originale, care ma ajuta sa fac
							modificarile din borded_map in functie de numarul de
							vecini al fiecarui element din matrice

	De asemenea, in borded_map am pus 1 pentru "X"(elementele ALIVE) si 0 pentru
"."(elementele DEAD).
	Pentru numarul de iteratii dat, am realizat urmatorii pasi:
		- am bordat matricea originala pentru coloanele de sus si jos, pentru
		  liniile de sus si de jos si pentru cele 4 colturi, aplicand regulile
		  din enunt;
		- am copiat toate elementele in copy_borded_map;
		- pentru fiecare element din matrice:
			-> am aflat numarul de vecini;
			-> am aplicat regulile pe copy_borded_map pentru a actualiza elemen-
			tele din ALIVE in DEAD si din DEAD in ALIVE;

	Am scris in fisier matricea rezultata:

		- 0 s-a transformat in "."(DEAD);
		- 1 s-a transformat in "X"(ALIVE).

	In final, am eliberat memoria pentru borded_map si pentru copy_borded_map si
am inchis fisierle.

===============================================================================
2. Implementarea paralela

	In plus fata de ce am implementat la varianta seriala, am adaugat:

		-  #pragma omp parallel pentru a marca inceputul unui bloc paralel;
		-  #pragma omp for private(i) in care thread-urile executa bucata de cod
			din interiorul for-urilor si fiecare thread are i-ul lui;
		-  #pragma omp master pentru a specifica faptul ca acea bucata de cod
		(bordarea colturilor) trebuie executata de thread-ul master;
		-  #pragma omp for collapse(2) pentru a specifica faptul ca avem dopa
			for-uri imbricate;
		- #pragma omp for collapse(2) private(sum) pentru a specifica faptul ca
			avem doua for-uri imbricate si ca fiecare thread are variabila "sum"
			a sa.

===============================================================================
