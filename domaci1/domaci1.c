/*
 * ============================================================================
 * Predmet:         Optimizacioni algoritmi u inženjerstvu
 * Zadatak:         Vežba 1 - Domaći zadatak
 * 
 * Ime:             Mihailo Ćuk
 * Broj indeksa:    3524/06
 * Datum:           22.10.2026.
 * 
 * Opis:            Četiri proizvoda imaju cene čiji je zbir i proizvod $7.11.
 *                  Različiti algoritmi i njihova efikasnost za pronalaženje 
 *                  mogućih takvih kombinacija.
 * ============================================================================
 */

#include <stdio.h>
#include <time.h>

// Proverava da li proizvod odgovara 711.000.000 (7.11*100*100*100*100)
int proveri_proizvod(long long a, long long b, long long c, long long d) {
    return (a * b * c * d == 711000000LL);
}

// (a) Potpuna pretraga po 4 cene
void deo_a(void) {
    printf("***(a): Pretraga po 4 cene***\n\n");
    long long pozivi = 0;
    time_t t1,t2;
    time(&t1);
    clock_t start = clock();
    for (int a = 1; a <= 711; a++) {
        for (int b = a; b <= 711 - a; b++) {
            for (int c = b; c <= 711 - a - b; c++) {
                for (int d = c; d <= 711 - a - b - c; d++) {
                    pozivi++;
                    if (a + b + c + d == 711) {
                        if (proveri_proizvod(a, b, c, d)) {
                            printf("Resenje: $%.2f, $%.2f, $%.2f, $%.2f\n", 
                                   a/100.0, b/100.0, c/100.0, d/100.0);
                        }
                    }
                }
            }
        }
    }
    time(&t2);
    clock_t end = clock();
    printf("Broj poziva opt. funkcije: %lld\n", pozivi);
    printf("Vreme izvsavanja (clock): %.3f s\n", (double)(end - start) / CLOCKS_PER_SEC); 
    printf("Vreme izvsavanja (time): %.3f s\n\n", difftime(t2, t1));
}

// (b) Pretraga po 3 cene (d = 711 - a - b - c)
void deo_b(void) {
    printf("***(b): Pretraga po 3 cene***\n\n");
    time_t t1,t2;
    time(&t1);
    clock_t start = clock();
    long long pozivi = 0;
    
    for (int a = 1; a <= 711 / 4; a++) {
        for (int b = a; b <= (711 - a) / 3; b++) {
            for (int c = b; c <= (711 - a - b) / 2; c++) {
                int d = 711 - a - b - c;
                pozivi++;
                if (proveri_proizvod(a, b, c, d)) {
                    printf("Resenje: $%.2f, $%.2f, $%.2f, $%.2f\n", 
                           a/100.0, b/100.0, c/100.0, d/100.0);
                }
            }
        }
    }

    time(&t2);
    clock_t end = clock();
    printf("Broj poziva opt. funkcije: %lld\n", pozivi);
    printf("Vreme izvrsavanja: %.3f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("Vreme izvsavanja (time): %.3f s\n\n", difftime(t2, t1));
}

// (v) Faktorizacija
void deo_v(void) {
    printf("***(v): Pretraga po faktorima broja 711000000***\n\n");
    time_t t1,t2;
    time(&t1);
    clock_t start = clock();
    int delioci[360];
    int br_delilaca = 0;
    long long cilj = 711000000LL;
    
    // Nalaženje svih delilaca broja 711.000.000 koji su <= 711
    for (int i = 1; i <= 711; i++) {
        if (cilj % i == 0) {
            delioci[br_delilaca++] = i;
        }
    }
    printf("broj delilaca: %i \n", br_delilaca );
    
    long long pozivi = 0;
    for (int i = 0; i < br_delilaca; i++) {
        int a = delioci[i];
        for (int j = i; j < br_delilaca; j++) {
            int b = delioci[j];
            if (a + b >= 711) break;
            
            for (int k = j; k < br_delilaca; k++) {
                int c = delioci[k];
                int d = 711 - a - b - c;
                if (d < c) break;
                
                pozivi++;
                if (cilj % d == 0) {
                    if (proveri_proizvod(a, b, c, d)) {
                        printf("Resenje: $%.2f, $%.2f, $%.2f, $%.2f\n", 
                               a/100.0, b/100.0, c/100.0, d/100.0);
                    }
                }
            }
        }
    }
    
    time(&t2);
    clock_t end = clock();
    printf("Broj poziva opt. funkcije: %lld\n", pozivi);
    printf("Vreme izvrsavanja (clock): %.4f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("Vreme izvsavanja (time): %.3f s\n\n", difftime(t2, t1));
}

int main(void) {
    deo_a();
    deo_b();
    deo_v();
    return 0;
}