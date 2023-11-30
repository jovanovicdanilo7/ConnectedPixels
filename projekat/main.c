/*
RA102/2020 Jovanović Danilo

ZADATAK
Napraviti modul koji predstavlja red. Modul izvesti kao dinamičku biblioteku (deljeni objekat). Napisati program
koji učitava sliku iz datoteke u formi matrice nula i jedinica. Zatim napisati funkciju koja kreće od zadatog
piksela i pronalazi sve piksele iste vrednosti koji su mu susedi, kao i sve piskele iste vrednosti koji su susedi
njegovim istovrednosnim susedima itd. Uzeti u obzir da je ne pretpostavljenom namenskom procesoru maksimalna dubina
poziva funkcije 4. Deljeni objekat koji predstavlja red dinamički povezati tokom izvršavanja. U rešenju se osloniti
na strukturu reda iz modula.

REŠENJE
Red je implementiran pomoću jednostruko spregnute liste.

Funckija createMatrix kreira matricu nad kojom se vrši tesiranje zajedno sa findConnectedPixels funkcijom koja
korišćenjem BFS-a pronalazi susede sa istom vrednosti kao i prosleđen piksel.

Program većim delom poštuje MISRA standard, jedino što nije ispoštovano su dinamičko zauzimanje memorije i
korišćenje stvari iz "stdio.h" biblioteke, poput printf exit...

Što se ograničenja programa tiče red, u koji se smeštaju susedni piskeli sa istim vrednostima kao i zadati piksel,
teorijski nije ograničen i nije specificirano šta će se desiti ukoliko se maksimalna veličina reda prekorači.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <dlfcn.h>
#include "matrix.h"

int_least8_t main(void)
{

    int startRow_m;
    int startColumn_m;

    printf("Enter the pixel coordinates.\nOrder coordinate: ");
    scanf("%d", &startRow_m);
    printf("Column coordinate: ");
    scanf("%d", &startColumn_m);

    assert((startRow_m >= 0) && (startColumn_m >= 0));

    void* handle_m;
    void (*findConnectedPixels_m)(int_least8_t, int_least8_t);
    char* error;

    handle_m = dlopen("libmatrix.so", RTLD_LAZY);
    if (handle_m == NULL)
    {
        fputs(dlerror(), stderr);
        exit(1);
    }
    findConnectedPixels_m = dlsym(handle_m, "findConnectedPixels");
    if ((error == dlerror()) != false)
    {
        fputs(error, stderr);
        exit(1);
    }

    (*findConnectedPixels_m)(startRow_m, startColumn_m);
    dlclose(handle_m);

    return 0;
}
