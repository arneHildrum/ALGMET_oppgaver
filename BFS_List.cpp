/**
 *   Programeksempel nr 30 - DFS og BFS p� graf.
 *
 *   Eksemplet viser b�de DFS (Dybde-F�rst-S�k) og BFS (Bredde-F�rst-S�k)
 *   i en (liten) graf. Det vises hvordan dette kan gj�res b�de vha.
 *   nabo-matrise og nabo-liste.
 *
 *   Algoritme/virkem�te:
 *        Bruker en hjelpearray ('gBesokt') som inneholder:
 *            - USETT (= 0) om en node enn� ikke er sett/bes�kt.
 *            - N (= 1 til V) n�r noden ble sett/bes�kt som nr.N.
 *              Til denne opptellingen brukes variabelen 'gBesoktSomNr'.
 *            - SENERE (= -1) om en er innom noden (dvs. delvis sett), men
 *              den skal bes�kes ordentlig senere i et Bredde-F�rst-S�k (BFS).
 *        DFS-algoritmen er rekursiv.
 *        BFS-algoritmen er iterativ.
 *
 *   Orden ( O(...)):
 *        - DFS p� en graf representert vha. nabo-MATRISE er av orden:  V*V
 *        - DFS p� en graf representert vha. nabo-LISTE er av orden:  V+E
 *
 *   NB:  - Nodenes ID/nr er konvertert til indeksintervallet 0 til ANTNODER-1
 *        - Nabomatrisen for uretted graf er ALLTID en speiling omkring
 *          hoveddiagonalen (fra �vre venstre til nedre h�yre hj�rne).
 *        - Dersom man kommer tilbake til en node som tidligere er
 *          sett/bes�kt, s� inneholder (selvsagt) grafen minst en sykel.
 *        - Antall ganger hver enkelt for-l�kke i main f�r at
 *          (gBesokt[i] == USETT) er sann, er antall komponenter i grafen.
 *
 *
 *   Dybde-F�rst-S�ketreet for grafen i dette eksemplet (n�r startende i A):
 *   =======================================================================
 *
 *                     ..... A......
 *                     :   /    :  :
 *                     :  B     :  :
 *                     :/   \   :  :
 *                     C     F  :  :
 *                            \ :  :
 *                              D  :
 *                               \ :
 *                                 E
 *
 *   - Dersom dette treet traverseres
 *     - preorder:  s� f�s den rekkef�lgen nodene ble sett/bes�kt i.
 *     - postorder: s� f�s den rekkef�lge som nodene er ferdige med �
 *                  bes�ke alle sine naboer.
 *   - Prikkede linjer viser kanter/rekursive kall som IKKE blir
 *     fulgt/startet. Disse g�r ALLTID oppover i treet!
 *   - Treet m/prikkede linjer blir derfor ENDA en m�te � tegne grafen p�!
 *
 *
 *   @file     EKS_30_DFS_BFS.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <queue>             //  queue
#include <vector>            //  vector
using namespace std;


const int ANTNODER =  6;             ///<  Antall noder i grafen (V).
const int USETT    =  0;             ///<  Node er IKKE sett enn�.
const int SENERE   = -1;             ///<  Innom, men ikke ferdig sett/bes�kt.

void BFS(int nr);
void BFS_Liste(int nr);
void DFS(const int nr);
void DFS_Liste(const int nr);
void initierNaboListe();
void nullstill();
void skriv();


int  gNaboMatrise[ANTNODER][ANTNODER]       ///<  Nabomatrise for grafen:
     = { { 0, 1, 1, 1, 1, 0 },   // A = 0
         { 1, 0, 1, 0, 0, 1 },   // B = 1          E-------A-------C
         { 1, 1, 0, 0, 0, 0 },   // C = 2          |      / \      |
         { 1, 0, 0, 0, 1, 1 },   // D = 3          D------   B------
         { 1, 0, 0, 1, 0, 0 },   // E = 4          |         |
         { 0, 1, 0, 1, 0, 0 } }; // F = 5          F----------
//         A  B  C  D  E  F


int  gBesokt[ANTNODER];                     ///<  Status for node nr.i.
int  gBesoktSomNr;                          ///<  Bes�kt noden som nr.X.

queue  <int> gBesokeSenere;                 ///<  Noder � bes�ke senere/snart.
vector <int> gNaboListe[ANTNODER];          ///<  Nabolister for samme grafen.
                                            //    ARRAY MED VECTORER !!!

/**
 *  Hovedprogrammet:
 */
int main() {
    int i;

    //cout << "\n\n DYBDE-F�RST-S�K (DFS) vha. nabo-MATRISE:\n";
    nullstill();                          //  Nullstiller hjelpevariable.

    for (i = 0; i < ANTNODER; i++)        //  G�r gjennom ALLE nodene:
        if (gBesokt[i] == USETT) DFS(i);  //  Bes�ker f�rste USETTE p�trufne
                                          //    i HVER KOMPONENT !!!


    cout << "\n\n BREDDE-F�RST-S�K (BFS) vha. nabo-MATRISE:\n";
    nullstill();

    for (i = 0; i < ANTNODER; i++)
        if (gBesokt[i] == USETT) BFS(i);



    //cout << "\n\n BREDDE-F�RST-S�K (BFS) vha. nabo-LISTE:\n";
    nullstill();
    initierNaboListe();

    for (i = 0; i < ANTNODER; i++)
        if (gBesokt[i] == USETT) DFS_Liste(i);

    cout << "\n\n BREDDE-F�RST-S�K (BFS) vha. nabo-LISTE:\n";
    nullstill();
    initierNaboListe();

    for (i = 0; i < ANTNODER; i++)
        if (gBesokt[i] == USETT) BFS_Liste(i);

    cout << "\n\n";
    return 0;
}


/**
 *  Vha. BFS og nabomatrise bes�kes iterativt ALLE komponentens noder.
 *
 *  @param   nr  - Indeks (0 til ANTNODER-1) for STARTNODEN i bes�ket
 */
 void BFS(int nr) {
    int j;                                     //  Indeks for aktuelle naboer.
    gBesokeSenere.push(nr);                    //  Legges BAKERST i bes�ksk�.
    while (!gBesokeSenere.empty()) {           //  Enn� noder � bes�ke igjen:
        nr = gBesokeSenere.front();            //  AVLES den f�rstes ID/nr.
        gBesokeSenere.pop();                   //  FJERNER/TAR UT fra k�en.
        gBesokt[nr] = ++gBesoktSomNr;          //  Setter bes�ksnummeret.
        for (j = 0;  j < ANTNODER;  j++)       //  Nodens linje i matrisen:
            if (gNaboMatrise[nr][j])           //  Er nabo med nr.j,
                if (gBesokt[j] == USETT) {     //    og denne er ubes�kt:
                    gBesokeSenere.push(j);     //  Legger nabo BAKERST i k�en.
                    gBesokt[j] = SENERE;       //  Setter at delvis bes�kt!!!
                }
        skriv();
    }
}


void BFS_Liste(int nr) {
    int nabo;
    gBesokeSenere.push(nr);  // Add starting node to the queue
    gBesokt[nr] = ++gBesoktSomNr;  // Mark it as visited

    while (!gBesokeSenere.empty()) {  // Continue while there are nodes to process
        nr = gBesokeSenere.front();  // Get the first node from the queue
        gBesokeSenere.pop();  // Remove it from the queue

        for (int j = 0; j < gNaboListe[nr].size(); j++) {
            nabo = gNaboListe[nr][j];
            if (gBesokt[nabo-1] == USETT) {  // If the neighbor hasn't been visited
                gBesokeSenere.push(nabo-1);  // Add the neighbor to the queue
                gBesokt[nabo-1] = ++gBesoktSomNr;  // Mark it as visited
            }
        }
        skriv();  // Print the current state
    }
}



/**
 *  Vha. DFS og NABOMATRISE bes�kes rekursivt ALLE komponentens noder.
 *
 *  @param   nr  -  Indeks (0 til ANTNODER-1) for noden som skal bes�kes
 */
 void DFS(const int nr) {
    gBesokt[nr] = ++gBesoktSomNr;               //  Setter bes�ksnummeret.
//                                              skriv();
    for (int j = 0;  j < ANTNODER;  j++)        //  Nodens linje i matrisen:
        if (gNaboMatrise[nr][j])                //  ER nabo med nr.j:
            if (gBesokt[j] == USETT) DFS(j);    //  Nr.j er usett:  Bes�ker
}


/**
 *  Vha. DFS og NABOLISTE bes�kes rekursivt ALLE komponentens noder.
 *
 *  @param   nr  -  Indeks (0 til ANTNODER-1) for noden som skal bes�kes
 */
 void DFS_Liste(const int nr) {
    int nabo;                                   //  Aktuell nabos ID/nr.
    gBesokt[nr] = ++gBesoktSomNr;               //  Setter bes�ksnummeret.
//                                              skriv();
                                                //  G�r gjennom naboer:
    for (unsigned int j = 0;  j < gNaboListe[nr].size();  j++)  {
        nabo = gNaboListe[nr].at(j);            //  Henter naboen ID/nr.
                                                //  Usett nabo bes�kes:
        if (gBesokt[nabo-1] == USETT) DFS_Liste(nabo-1);
    }
}


/**
 *  Initierer naboliste (med "tilfeldig" rekkef�lge) for eksemplets graf.
 */
 void initierNaboListe() {
    gNaboListe[0].push_back(5);    gNaboListe[0].push_back(4);
    gNaboListe[0].push_back(2);    gNaboListe[0].push_back(3);
    gNaboListe[1].push_back(3);    gNaboListe[1].push_back(1);
                                   gNaboListe[1].push_back(6);
    gNaboListe[2].push_back(2);    gNaboListe[2].push_back(1);
    gNaboListe[3].push_back(1);    gNaboListe[3].push_back(6);
                                   gNaboListe[3].push_back(5);
    gNaboListe[4].push_back(1);    gNaboListe[4].push_back(4);
    gNaboListe[5].push_back(4);    gNaboListe[5].push_back(2);
}


 /**
  *  Nullstiller/initierer de globale variablene 'gBesoktSomNr' og 'gBesokt'.
  */
 void nullstill() {
    gBesoktSomNr = 0;
    for (int i = 0;  i < ANTNODER;  i++)
        gBesokt[i] = USETT;
}


 /**
  *  Skriver ut p� skjermen HELE arrayen 'gBesokt' sitt innhold.
  */
 void skriv() {
    for (int i = 0;  i < ANTNODER;  i++)
        cout << ' ' << gBesokt[i];
    cout << '\n';
}
