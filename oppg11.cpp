/**
 *   Programeksempel nr 24 - Quicksort.
 *
 *   Algoritme/virkem�te:
 *        Prinsippet: Splitt og hersk, partisjonere i to, sortere hver del.
 *        Dette l�ses/gj�res ved �:
 *         - velge arr[hoyre] som et tilfeldig element/verdi � sortere ut fra.
 *           Det valgte elementet kalles "partisjonselementet".
 *         - lete fra venstre etter en st�rre eller lik verdi, og fra h�yre
 *           etter en mindre eller lik verdi, og s� bytte om p� disse to.
 *         - gjenta det forrige punktet inntil letingen har passert hverandre.
 *         - til slutt bytte arr[hoyre] (partisjonselementet) med den
 *           HELT TIL H�YRE I VENSTRE DELARRAY (nr.'i').
 *        Alt dette medf�rer at:
 *         - Partisjonselementet i arr[i] er p� sin endelige plass for godt
 *         - ALLE verdier i arr[venstre] til arr[i-1] er MINDRE ELLER LIK
 *         - ALLE verdier i arr[i+1] til arr[hoyre] er ST�RRE ELLER LIK
 *
 *   Orden ( O(...)):
 *        Quicksort bruker i gjennomsnitt omtrent  2N ln N  sammenligninger.
 *        (som er omtrent  1.39N lg N)     "Worst case":  (N*N)/2
 *
 *   NB:  - Koden i funksjonen 'partisjoner' kan/burde ogs� bare flyttes inn
 *          i funksjonen 'quickSort' - s� g�r den ENDA raskere.
 *        - Skal elementet HELT til h�yre eller venstre velges som
 *          partisjonselement?  Dette er en smakssak, og gj�res litt ulikt
 *          i de forskjellige kodesnutter, visualiseringer og animasjoner.
 *          Det viktigste er at man gj�r ET VALG, og er konsekvent mot dette !
 *          ==================================================================
 *          I koden nedenfor er det brukt det HELT TIL H�YRE i delarrayen, og
 *          DETTE ER DET OGS� FORUTSATT AT MAN GJ�R IFM. OPPGAVER/P� EKSAMEN !
 *          ==================================================================
 *        - Quicksort bytter ogs� om p� elementer som er likt med
 *          partisjonselementet. Hadde det KUN v�rt LIKE elementer i hele
 *          arrayen s� ville vi ellers ha f�tt et "worst case". Men gj�res
 *          det slik, s� vil gi hele tiden f� en EKSAKT todeling/halvering av
 *          av arrayen - som jo er en god, rask og effektiv m�te.
 *        - Bruker ogs� SENTINEL KEY - i tilfelle partisjonselementet
 *          er det aller minste
 *        - Stabil?  NEI - da bl.a. bytter om like elementer
 *
 *        - Siden Quicksort er en av de aller raskeste sorteringsmetoder som
 *          er laget/utviklet, s� er det ogs� sett p� mye hvordan gj�re den
 *          ENDA raskere. Tre forbedringer i s� m�te KAN v�re:
 *             1) Fjerne rekursjon - heller bruke Stack:
 *                Rekursjon er ofte elegant og den enkleste m�ten � l�se en
 *                del problemer p�. Men den er ogs� litt ekstra ressurs-
 *                krevende, ved at data (adresser i hukommelsen og lokale
 *                variable m� pushes p� "programstacken"). Fjerner man derfor
 *                rekursjon og heller pusher p� en egen stack 'venstre'- og
 *                'hoyre'-intervaller som koden har igjen � jobbe med, s� vil
 *                hastigheten kunne g� litt/noe opp.
 *             2) Spesialh�ndtere mindre/kortere delarrayer:
 *                N�r delarrayen som skal sorteres vha. Quicksort blir rimelig
 *                kort (typisk 5-25 elementer), s� kan man la v�re � sortere
 *                disse vha. rekursive Quicksort, men la de forbli usortert.
 *                HELT TIL SLUTT g�r man gjennom HELE arrayen og sorterer den
 *                vha. f.eks. Insertion sort. Da vil den jo best� av masse
 *                delarrayer, der ALLE elementer i en delarray er st�rre enn
 *                de i den forrige, og mindre enn ALLE i den neste. Dermed vil
 *                ikke Insertion sort flytte elementene s� langt bakover.
 *             3) Median-of-three:
 *                I stedet for � bare ta h�yre/venstre element som partisjons-
 *                element, som jo blir en meget tilfeldig verdi, s� pr�ver man
 *                � finne en verdi som kanskje er LITT mer representativ for
 *                gjennomsnittet av verdiene i delarrayen. Dette gj�r man ved
 *                � se p� venstre, midtre og h�yre element. Bytte om p� disse,
 *                slik at de blir i stigende rekkef�lge, bytte arr[midtre] opp
 *                til arr[hoyre-1], og s� sortere delarrayen arr[venstre+1] og
 *                opp til arr[hoyre-2]. Slipper da ogs� sentinel key!
 *          Men, selv med alle alt dette blir Quicksort bare 25-30% raskere.
 *
 *   @file     EKS_24_QuickSort.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <string>            //  string
#include <cstdlib>           //  (s)rand
using namespace std;


const int N = 11;            ///<  Antall elementer i array som skal sorteres.


void bytt(char & tegn1, char & tegn2);
void display(const string & tekst, const char arr[],
             const int venstre, const int hoyre);
int  partisjoner(char arr[], const int venstre, const int hoyre);
void quickSort(char arr[], const int venstre, const int hoyre);


/**
 *  Hovedprogrammet:
 */
int main() {
    char array[N+1] = " LIGAMESTER";
    display("\n\nArrayen F�R sortering:\n", array, 1, N);


    quickSort(array, 1, N);      //  QUICKSORT SORTERER !!!

                                   //  Skriver array ETTER sortering:
    display("\n\nArrayen ETTER QUICKSORT sortering:\n", array, 1, N);

    cout << "\n\n";
    return 0;
}


/**
 *  Bytter om to referanseoverf�rte variables innhold.
 *
 *  @param   tegn1  -  Verdien som skal byttes med 'tegn2' (referanseoverf�rt)
 *  @param   tegn2  -  Verdien som skal byttes med 'tegn1' (referanseoverf�rt)
 */
void bytt(char & tegn1, char & tegn2) {
    char temp = tegn1;           //  Midlertidig (temporary) unnalagring.
    tegn1 = tegn2;
    tegn2 = temp;
}


/**
 *  Skriver ut (deler av) arrayen 'arr' sitt innhold.
 *
 *  @param   tekst    -  Ledetekst som skrives aller f�rst
 *  @param   arr      -  Arrayen som f�r (deler av) innholdet skrevet ut
 *  @param   venstre  -  Nedre/venstre indeks for utskrift
 *  @param   hoyre    -  �vre/h�yre    indeks for utskrift
 */
void display(const string & tekst, const char arr[],
             const int venstre, const int hoyre) {
    char tegn;
    cout << tekst << "\t";
    for (int i = venstre;  i <= hoyre;  i++)
        cout << arr[i];
    cin >> tegn;                        //  Venter p� ETT tegn og '\n'.
}


/**
 *  Flytter elementer i (deler av) array ut fra H�YRE partisjonselement,
 *  slik at ALT til venstre er mindre/lik, og ALT til h�yre er st�rre/lik.
 *
 *  @param    arr      -  Arrayen som skal partisjoneres
 *  @param    venstre  -  Nedre/venstre indeks for partisjonering
 *  @param    hoyre    -  �vre/h�yre    indeks for partisjonering
 *  @return   Indeksen der partisjonselementet havnet/ble plassert
 *  @see      display(...)
 */
int partisjoner(char arr[], const int venstre, const int hoyre) {
    if (hoyre > venstre) {              //  Minst TO elementer:
        int i, j;                       //  Indekser som g�r mot hverandre.
        char partisjonsElement;         //  Partisjonselementet.

        partisjonsElement = arr[hoyre]; //  Initierer til H�YRE element.
        i = venstre-1;                  //  Initierer indeksene til ETT
        j = hoyre;                      //    hakk utenfor intervallet.
                             //  NB:  'i' og 'j' �kes/minskes F�R bruk.
                             //       Derfor er de initiert utenfor grensene.
                             //       De stopper dermed p� de aktuelle
                             //       indekser UTEN � "hoppe" en for langt.
//                            display("\nF�r:", arr, venstre, hoyre);
        while (true) {                  //  Looper til breaker ut:
                                        //  Leter etter ST�RRE ELLER LIK:
            while (arr[++i] < partisjonsElement)   ;   //  NB:  Tom innmat !!!
                                        //  Leter etter MINDRE ELLER LIK:
            while (arr[--j] > partisjonsElement)   ;   //  NB:  Tom innmat !!!

//                             cout << "i: " << i << "  j: " << j << "   - "
//                                  << ((i < j) ? "Bytte" : "BREAK") << '\n';
            if (i >= j)  break;         //  Indekser n�dd/passert hverandre.
            bytt(arr[i], arr[j]);       //  Bytter der stanset med 'i' og 'j'.
        }

        bytt(arr[i], arr[hoyre]);     //  Bytter/setter (for godt) partisjons-
                                      //    elementet med det HELT TIL H�YRE I
                                      //    VENSTRE HALVDEL (dvs. der 'i' er).
//                             display("Etter:", arr, venstre, hoyre);
        return i;                     //  Returnerer der partisjonselementet
    }                                 //    havnet/ble plassert.
    return 0;                         //  Mindre enn to elementer:
}                                     //    returnerer "dummy" verdi.


/**
 *  Sorterer REKURSIVT en char-array STIGENDE med QUICKSORT.
 *
 *  @param   arr      -  Arrayen som skal sorteres
 *  @param   venstre  -  Nedre/venstre indeks for sorteringsintervall
 *  @param   hoyre    -  �vre/h�yre    indeks for sorteringsintervall
 *  @see     partisjoner(...)
 */
void quickSort(char arr[], const int venstre, const int hoyre)  {
    if (hoyre > venstre) {                  //  MINST TO elementer:
        int indeks = partisjoner(arr, venstre, hoyre);    //  Partisjonerer!!!
        quickSort(arr, venstre, indeks-1);  //  Gj�r det samme for venstre og
        quickSort(arr, indeks+1, hoyre);    //    h�yre halvdel ift. 'indeks'.
    }
}
