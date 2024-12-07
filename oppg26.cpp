#include <iostream>          //  cout
#include <iomanip>           //  setw          
using namespace std;

const int N = 10;


void bytt(int & tall1, int & tall2);
void permuter(int arr[], const int i, const int n);
void roterVenstre(int arr[], const int i, const int n);
bool sjekk(const int arr[], const int n);
void skriv();


int gArray[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};            ///< er noden brukt
          // Node nr: 0  1  2  3  4  5  6  7  8  9 Node nr:
int gNabo[N][N] = { { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 }, // 0
                    { 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 }, // 1
                    { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 }, // 2
                    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, // 3
                    { 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 }, // 4
                    { 0, 0, 1, 0, 0, 0, 1, 1, 0, 0 }, // 5
                    { 0, 1, 1, 0, 1, 1, 0, 1, 1, 1 }, // 6
                    { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1 }, // 7
                    { 1, 0, 0, 0, 1, 0, 1, 0, 0, 1 }, // 8
                    { 0, 0, 0, 0, 1, 0, 1, 1, 1, 0 } }; // 9

int gSum[N] = { 21, 33, 14, 27, 1, 14, 20, 12, 28, 20 };   ///< Nodenes nabosum.

int main () {

    permuter(gArray, 0, N);

    return 0;
}


void bytt(int & tall1, int & tall2) {
    int temp = tall1;           //  Midlertidig (temporary) unnalagring.
    tall1 = tall2;
    tall2 = temp;
}


/**
 *  Genererer rekursivt ALLE mulige permutasjoner av innholdet i 'arr'.
 *
 *  @param   arr  -  Arrayen som skal permuteres
 *  @param   i    -  Indeksen som ALLE ETTERFØLGENDE verdier skal flyttes til
 *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
 *  @see     bytt(...)
 *  @see     sjekk()
 *  @see     roterVenstre(...)
 */
void permuter(int arr[], const int i, const int n) {
    if (i == n-1)                       //  Nådd en ny permutasjon:
        sjekk(arr, n);                  //  Skriver ut arrayens innhold.
    else {                              //  Skal permutere:
        permuter(arr, i+1, n);          //  Beholder nåværende nr.'i'.
                                        //    Permuterer resten.
        for (int t = i+1;  t < n;  t++) {
            bytt(arr[i], arr[t]);       //  Bytter nr.'i' etter tur med
                                        //    ALLE de andre etterfølgende.
            permuter(arr, i+1, n);      //  For hver av ombyttene: permuterer
        }                               //     resten av de etterfølgende.
        roterVenstre(arr, i, n);        //  Gjenoppretter opprinnelig array!!!
    }
}


/**
 *  Venstreroterer en array innhold.
 *
 *  @param   arr  -  Arrayen som får (deler av) sitt innhold venstrerotert
 *  @param   i    -  Laveste indeks som skal venstreroteres
 *  @param   n    -  'n-1' er høyeste indeks som venstreroteres
 */
void roterVenstre(int arr[], const int i, const int n) {
    int venstreVerdi = arr[i];            //  Tar vare på første.
    for (int k = i+1;  k < n;  k++)       //  Roterer (flytter alle ned
        arr[k-1] = arr[k];                //     ETT hakk/indeks).
    arr[n-1] = venstreVerdi;              //  Legger første inn bakerst.
}



void skriv() {
    for(int i = 0; i < N; i++)
        cout << setw(2) << "Node " << i << " Har verdi " << gArray[i] << endl;
}


bool sjekk(const int arr[], const int n) {
    int sum;
    bool check = true;
    for(int i = 0; i < N; i++) {
        sum = 0;
        for(int j = 0; j < N; j++) 
            if(gNabo[i][j])     sum += arr[j];
        if(sum != gSum[arr[i]])      return false;
    }
    skriv();
}