#include<stdio.h>
#include<malloc.h>

typedef struct Santier Santier;
struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

typedef struct NodLdi NodLdi;
struct NodLdi {

    NodLdi* prev;
    NodLdi* next;
    Santier info;
};
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    NodLdi* prim;
    NodLdi* ultim;
};

void inserareInceput(ListaDubla* lista, Santier s) {
    NodLdi* aux = malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;

    if (lista->prim != NULL) {
        lista->prim->prev = aux;
    }
    else {

        lista->ultim = aux;
    }
    lista->prim = aux;
}

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;

    return santier;
}

//Nod* inserareInceput(Santier santier, Nod* lista)
//{
//    Nod* nod = (Nod*)malloc(sizeof(Nod));
//    //shallow copy pt a nu avea un obiect in plus de sters in main
//    nod->santier = santier;
//    nod->next = lista;
//    return nod;
//}

void afisareSantier(Santier s) {
    printf("Proiectul %s are %d muncitori ce lucreaza pe o suprafata de %5.2f m^2\n", s.numeProiect, s.nrMuncitori, s.suprafata);
}

//void afisareLista(Nod* lista) {
//    while (lista != NULL) {
//        //procesare
//        afisareSantier(lista->santier);
//        lista = lista->next;
//    }
//}

//int sumaMuncitori(Nod* lista) {
//    int suma = 0;
//    while (lista != NULL) {
//        suma += lista->santier.nrMuncitori;
//        lista = lista->next;
//    }
//    return suma;
//}

//void stergereLista(Nod** lista) {
//    while ((*lista) != NULL) {
//        free((*lista)->santier.numeProiect);
//        Nod* aux = (*lista)->next;
//        free(*lista);
//        (*lista) = aux;
//    }
//    (*lista) = NULL;
//
//}

//numele santierului cu densitatea de muncitori cea mai mare pe m^2

float densitateMuncitori(Santier s) {
    if (s.suprafata > 0) {
        return s.nrMuncitori / s.suprafata;
    }
    else return 0;


}

void afisareDeLaInceput(ListaDubla lista) {
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        afisareSantier(nod->info);
    }
}

//stergem santierul cu nume dat
void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier) {

    NodLdi* nod = lista->prim;
    while (nod != NULL) {
        if (strcmp(nod->info.numeProiect, numeSantier) == 0) {
            //daca e primul nod
            if (nod->prev == NULL) {
                //verificam daca exista urm nod
                if (nod->next == NULL) {
                    lista->prim = NULL;
                    lista->ultim = NULL;
                }
                else {
                    nod->next->prev = NULL;
                    lista->prim = nod->next;
                }
            }
            else {
                if (nod->next == NULL) {
                    nod->prev->next = NULL;
                    lista->ultim = nod->prev;
                }
                else {
                    nod->prev->next = nod->next;
                    nod->next->prev = nod->prev;
                }
            }
            free(nod->info.numeProiect);
            free(nod);
            nod = NULL;
        }
        else {

            nod = nod->next;
        }
    }

}

void stergereCompleta(ListaDubla* lista) {
    if (lista != NULL) {
        NodLdi* aux = lista->prim;
        while (aux != NULL) {
            free(aux->info.numeProiect);
            NodLdi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}


//char* numeSantierDensitateMaxima(Nod* lista) {
//    float max = 0;
//    char* aux = NULL;
//    while (lista != NULL) {
//        if (densitateMuncitori(lista->santier) > max)
//        {
//            max = densitateMuncitori(lista->santier);
//            aux = lista->santier.numeProiect;
//        }
//        lista = lista->next;
//
//    }
//    if (aux != NULL) {
//        char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
//        strcpy(numeProiectDensitate, aux);
//
//        return numeProiectDensitate;
//    }
//
//    else return NULL;
//}
//
//

//nr muncitori total din lista
int nrMuncitoriTotal(ListaDubla lista) {
    int s = 0;
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        s += nod->info.nrMuncitori;
    }
    return s;
}
int calculMuncitoriSuprafata(ListaDubla lista, float suprafata) {
    int s = 0;
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        if (nod->info.suprafata < suprafata)
            s = s + nod->info.nrMuncitori;
    }
    return s;
}
int main() {
    /* Nod* lista = NULL;*/
    Santier s1 = initializareSantier("Santier 1", 700, 450);
    Santier s2 = initializareSantier("Santier 2", 3000, 500);
    Santier s3 = initializareSantier("Santier 3", 6700, 300);

    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);

    afisareDeLaInceput(lista);
     printf("\n\n");
     stergereSantierDupaNume(&lista, "Santier 1");
     afisareDeLaInceput(lista);
     printf("\n\n");
     stergereSantierDupaNume(&lista, "Santier 2");
     afisareDeLaInceput(lista);
     printf("\n\n");
     stergereSantierDupaNume(&lista, "Santier 3");
     afisareDeLaInceput(lista);
     printf("\n\n");

     afisareDeLaInceput(lista);
     printf("\n\n");

   




    int numarMuncitori = nrMuncitoriTotal(lista);
    printf("\n Numar muncitori %d", numarMuncitori);
    stergereCompleta(&lista);
}