#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;

};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++) {
		aux[i] = masini[i]; //am facut shallow copy
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;
	if (masini != NULL) //verificam pt ca initial , la prima inserare vectorul e null si n am avea ce sterge
		free(masini); //nu l am parcurs pt ca am facut shallow copy

	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini)//transmis prin pointer pt a putea fi modificat
{
	FILE* f = fopen(numeFisier, "r");
	//bufferul e unde sa citeasca(primul param al functiei)
	char buffer[100];//alocat static, practic cu cat ar putea contine o linie maxim
	char sep[] = ",\n"; //alocam pe stiva pt ca n avem nevoie de el in main(heap)
	struct Masina* masini = NULL;
	(*nrMasini) = 0;
	while (fgets(buffer, 100, f) != NULL)//cand ajunge la finalul fisierului si nu mai are ce citi, returneaza null
	{
		char* token = strtok(buffer, sep);
		struct Masina m;
		m.id = atoi(token);
		token = strtok(NULL, sep);
		m.producator =(char*) malloc(strlen(token) + 1);
		strcpy(m.producator, token);
		token = strtok(NULL, sep);
		m.nrUsi = atoi(token);
		token = strtok(NULL, sep);
		m.pret = atof(token);
		masini = adaugareInVector(masini, m, nrMasini); //e deja pointer deci nu mai punem & (dresa)



	}
	return masini;
}
int main()
{
	int nrMasini = 0;
	struct Masina* masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++) {
		printf("Id: %d\n", masini[i].id);
		printf("Producator: %s\n", masini[i].producator);
		printf("Numar usi: %d\n", masini[i].nrUsi);
		printf("Pret: %5.2f\n", masini[i].pret);
		printf("\n");
	}
}