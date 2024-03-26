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
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasini + 1));
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
		m.producator = malloc(strlen(token) + 1);
		strcpy(m.producator, token);
		token = strtok(NULL, sep);
		m.nrUsi = atoi(token);
		token = strtok(NULL, sep);
		m.pret = atof(token);
		masini = adaugareInVector(masini, m, nrMasini); //e deja pointer deci nu mai punem & (dresa)

	}
	fclose(f);
	return masini;
}


void citireMatrice(char* file, struct Masina** matrice, int nrLinii, int* nrColoane)
{
	FILE* f = fopen(file, "r");
	char buffer[100];
	char sep[] = ",\n";
	while (fgets(buffer, 100, f) != NULL)
	{
		char* token = strtok(buffer, sep);
		struct Masina m;
		m.id = atoi(token);
		token = strtok(NULL, sep);
		m.producator = malloc(strlen(token) + 1);
		strcpy(m.producator, token);
		token = strtok(NULL, sep);
		m.nrUsi = atoi(token);
		token = strtok(NULL, sep);
		m.pret = atof(token);
		matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrColoane[m.nrUsi - 2]));
	}
	fclose(f);
}

void afiseazaMasina(struct Masina m)
{

	printf("%d, %s, %d, %5.2f  \t", m.id, m.producator, m.nrUsi, m.pret);
	//printf("Id: %d\n", m.id);
	//printf("Producator: %s\n", m.producator);
	//printf("Numar usi: %d\n", m.nrUsi);
	//printf("Pret: %5.2f\n", m.pret);
	//printf("\n");
}

void afiseazaMatrice(struct Masina** matrice, int nrLinii, int* nrColoane)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			afiseazaMasina(matrice[i][j]);
		}
		printf("\n");
	}
}

float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi)
{
	if (nrUsi > 1 && nrUsi < 5)
	{
		float pretTotal = 0;
		int index = nrUsi - 2;
		if (nrColoane[index] == 0)
			return 0;
		for (int i = 0; i < nrColoane[index]; i++)
		{
			pretTotal += matrice[index][i].pret;
		}
		return pretTotal / nrColoane[index];
	}
	return -1;
}

struct Masina cautareDupaID(struct Masina** matrice, int nrLinii, int* nrColoane, int id)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			if (matrice[i][j].id == id) return matrice[i][j];
		}
		struct Masina m;
		m.id = -1;
		m.producator = "";
		m.nrUsi = 0;
		m.pret = 0.0;
		return m;
	}
}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrColoane)
{
	if (*matrice == NULL || *nrColoane == NULL)
	{
		return;
	}
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < (*nrColoane)[i]; j++)
		{
			free((*matrice)[i][j].producator);
		}
		free((*matrice)[i]);
	}
	free(*nrColoane);
	*nrColoane = NULL;
	free(*matrice);
	*matrice = NULL;
}


int main()
{
	/*int nrMasini = 0;
	struct Masina* masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++) {
		printf("Id: %d\n", masini[i].id);
		printf("Producator: %s\n", masini[i].producator);
		printf("Numar usi: %d\n", masini[i].nrUsi);
		printf("Pret: %5.2f\n", masini[i].pret);
		printf("\n");
	}*/

	struct Masina** matrice;
	int nrLinii = 3;
	int* nrColoane;
	nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (struct Masina*)malloc(sizeof(struct Masina) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		nrColoane[i] = 0;
		matrice[i] = NULL;
	}
	//afiseazaMatrice(matrice, nrLinii, nrColoane);
	citireMatrice("masini2.txt", matrice, nrLinii, nrColoane);
	afiseazaMatrice(matrice, nrLinii, nrColoane);
	float pret = pretMediu(matrice, nrLinii, nrColoane, 2);
	printf("\nPret mediu pentru %d usi este %5.2f", 2, pret);
	printf("\n\nMasina cautata: \n");
	afiseazaMasina(cautareDupaID(matrice, nrLinii, nrColoane, 5));
	dezalocareMatrice(&matrice, nrLinii, &nrColoane);
}