/**
 *   Hovedrisset til oppgave nr 8.
 *
 *   For programmets funksjonalitet:  se oppgaveteksten.
 *
 *   (Dette var oppg.nr.3 på eksamen 15/8-2016 i IMT2021-Algoritmiske metoder)
 *
 *   @file	  OPPG_08-HOVEDRISS.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Node (med ID/key/data og venstre/høyre pekere til nodens barn).
 */
struct Node {
    int   ID;	        //  Nodens ID/key/nøkkel/navn (et tall).
    Node* left;	      //  Peker til venstre subtre, evt. 'nullptr' når tomt.
    Node* right;	    //  Peker til høyre subtre, evt. 'nullptr' når tomt.
                      //  Constructor:
    Node(int id, Node* l, Node* r) { ID = id;  left = l, right = r; }
};


Node* byggTre();
bool  erBST(Node* n);                        //  Oppgave B
int   finnMax(Node* n);                      //  Oppgave A2
int   finnMin(Node* n);                      //  Oppgave A1


Node* gRoot = nullptr;	  ///<  Peker til hele treets rot.
const int MIN = 0,        ///<  Verdier mindre/større enn ALLE ID'er i treet.
          MAX = 9999;


/**
 *  Hovedprogrammet:
 */
int main() {

    gRoot = byggTre();

    cout << "\n\nTester oppgave A - Minste og største verdi i treet:\n";
    cout << "Minste  verdi i treet er:  " << finnMin(gRoot) << '\n';   //   3
    cout << "Største verdi i treet er:  " << finnMax(gRoot) << '\n';   //  82


    cout << "\n\nTester oppgave B - Er treet et binært søketre eller ei:\n";
    cout << "Treet er " << (erBST(gRoot) ? "" : "IKKE ")      //  Er IKKE BST!
         << "et binært SØKEtre\n\n";

    return 0;
}


/**
 *  Bygger et binært testtre.
 *
 *  @return   Peker til rota i treet som er bygd
 */
Node* byggTre() {
    //          Bygger treet:                         //
    //                       17                       //
    //                  /          \                  //
    //                 33           11                //
    //               /    \       /    \              //
    //              7      35   82      5             //
    //            /   \           \    /              //
    //           27     13        31  34              //
    //                   \        /                   //
    //                   10      57                   //
    //                          /  \                  //
    //                         3   30                 //
    Node *n3  = new Node(3, nullptr, nullptr),
         *n30 = new Node(30, nullptr, nullptr),
         *n10 = new Node(10, nullptr, nullptr),
         *n57 = new Node(57, n3, n30),
         *n27 = new Node(27, nullptr, nullptr),
         *n13 = new Node(13, nullptr, n10),
         *n31 = new Node(31, n57, nullptr),
         *n34 = new Node(34, nullptr, nullptr),
         *n7  = new Node(7, n27, n13),
         *n35 = new Node(35, nullptr, nullptr),
         *n82 = new Node(82, nullptr, n31),
         *n5  = new Node(5, n34, nullptr),
         *n33 = new Node(33, n7, n35),
         *n11 = new Node(11, n82, n5),
         *n17 = new Node(17, n33, n11);
    return n17;
}


/**
 *  OPPGAVE B - Finner ut om et binært tre er et binært SØKEtre (BST)
 *
 *  @param    node  -  Aktuell node å behandle
 *  @return   Om treet under 'node' er binært søketre (BST) eller ei
 *  @see      finnMax(...)
 *  @see      finnMin(...)
 */
bool erBST(Node* node) {

    if(node) {
        int lmax = finnMax(node->left),
            rmin = finnMin(node->right);
            
        
        return (lmax < rmin) ? true : false;
    }
}


/**
 *  OPPGAVE A2 - Finner STØRSTE verdi i et binært (IKKE nødvendigvis SØKE)tre.
 *
 *  @param    node  -  Aktuell node å behandle
 *  @return   ALLER største verdi (ID) funnet i HELE treet under 'node'
 */
int finnMax(Node* node) {

    if(node) {
        int max = node->ID,
           lmax = finnMax(node->left),
           rmax = finnMax(node->right);

        if(lmax > max) max = lmax;
        if(rmax > max) max = rmax;

        return max;
        
    } else return MIN;
}


/**
 *  OPPGAVE A1 - Finner MINSTE verdi i et binært (IKKE nødvendigvis SØKE)tre.
 *
 *  @param    node  -  Aktuell node å behandle
 *  @return   ALLER minste verdi (ID) funnet i HELE treet under 'node'
 */
int finnMin(Node* node) {

    if(node) {
        int min = node->ID,
           lmin = finnMin(node->left),
           rmin = finnMin(node->right);

        if(lmin < min) min = lmin;
        if(rmin < min) min = rmin;

        return min;
        
    } else return MAX;
}