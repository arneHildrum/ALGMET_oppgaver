/**
 *   Programeksempel nr 12 - Traverserer et bin�rt tre REKURSIVT.
 *
 *   Eksempel som viser traversering av et bin�rt tre vha rekursjon.
 *   Det viser hvor enkelt treet kan traverseres b�de p� en preorder,
 *   inorder og postorder m�te.
 *
 *   @file     EKS_12_RekursivTreTraversering.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <iomanip>                   //  setw
using namespace std;


/**
 *  Node (med ID/key/data og venstre/h�yre pekere til nodens barn).
 */
struct Node {
    char ID;
    Node *left, *right;                //  Initierende constructor:
    Node(char id)  {  ID = id;  left = right = nullptr;  }
};


void  besok(const Node* node);
Node* byggTre();
void finnAntallNoder(Node* node);
void finnAntallNULL(Node* node);
void finnAntallFulleNoder(Node* node);
void finnHoyde(Node* node, int hoyde);
void  traverserInorder(Node* node);
void  traverserPostorder(Node* node);
void  traverserPreorder(Node* node);


int gNivaa = -1;          ///<  Hvilket niv� vi for �yeblikket er p� i treet.
int gNr;                  ///<  Fortl�pende nummerering av bes�kte noder.
                          //    NB:  Begge disse er kun i bruk her for � vise
                          //         i hvilken rekkef�lge nodene bes�kes og
                          //         hvilket niv� de befinner seg p�.
                          //         Normalt brukes IKKE disse!

int gAntall = 0;

/**
 *  Hovedprogrammet:
 */
int main()  {
    Node*  root;

    root = byggTre();

    gNr = 0;                        //  M� nullstilles for hver traversering!
                                    //  Mens 'gNivaa' telles tilbake til -1!!!
    cout << "\n\nPreorder traversering:\n";
    traverserPreorder(root);

    gNr = 0;
    cout << "\n\nInorder traversering:\n";
    traverserInorder(root);

    gNr = 0;
    cout << "\n\nPostorder traversering:\n";
    traverserPostorder(root);

    finnAntallNoder(root);
    cout << "Det er totalt " << gAntall << " antall noder i treet. \n";
    gAntall = 0;

    finnAntallNULL(root);
    cout << "Det er totalt " << gAntall << " antall referanser til nullptr. \n";
    gAntall = 0;

    finnAntallFulleNoder(root);
    cout << "Det er totalt " << gAntall << " antall fulle noder i treet. \n";
    gAntall = 0;

    finnHoyde(root, 1);
    cout << "Hoyden til treet er " << gAntall << "\n(Roten har hoyde 1)\n";

    cout << "\n\n";
    return 0;
}


/**
 *  Bes�ker (visit) en node - ved � skrive dens bes�ksnummer ('gNr'), 
 *  dens ID/key/data og hvilket niv� ('gNivaa') den er p�.
 *
 *  @param   node  -  Aktuell node som skal bes�kes
 */
void  besok(const Node* node) {
    cout << setw(6) << ++gNr << ": " << node->ID
         << "  p� niv�: " << gNivaa << '\n';
}


/**
 *  Bygger et bin�rt eksempel-tre (likt med det i EKS_08).
 *
 *  @return   Peker til det bygde treets rot
 */
Node* byggTre() {
/*   Bygger treet:                                     A
                                              /                 \
                                         B                          C
                                    /         \                  /
                                  D             E              F
                              /       \           \          /
                            G           H           I      J
                              \        / \         /        \
                               K      L   M       N          O
*/
    Node*  noder[15];
    for (int i = 0; i < 15; i++)
        noder[i] = new Node(static_cast <char> ('A' + i));

    noder[0]->left = noder[1];  noder[0]->right = noder[2];
    noder[1]->left = noder[3];  noder[1]->right = noder[4];
    noder[2]->left = noder[5];
    noder[3]->left = noder[6];  noder[3]->right = noder[7];
                                noder[4]->right = noder[8];
    noder[5]->left = noder[9];
                                noder[6]->right = noder[10];
    noder[7]->left = noder[11]; noder[7]->right = noder[12];
    noder[8]->left = noder[13];
                                noder[9]->right = noder[14];
    return noder[0];
}


void finnAntallNoder(Node* node) {
    if(node) {
        gAntall++;
        if(node->left)      finnAntallNoder(node->left);
        if(node->right)      finnAntallNoder(node->right);
    }

}


void finnAntallNULL(Node* node) {
    if(node) {
        finnAntallNULL(node->left);
        finnAntallNULL(node->right);
    }
    else gAntall++;
}


void finnAntallFulleNoder(Node* node) {
    if(node) {
        if(node->left && node->right) {
            gAntall++;
            cout << node->ID << " Er en full node. \n";
        }
        finnAntallFulleNoder(node->left);
        finnAntallFulleNoder(node->right);
    }
}


void finnHoyde(Node* node, int hoyde) {
    if(node) {
        if(hoyde > gAntall)     gAntall = hoyde;
        if (node->left)         finnHoyde(node->left, hoyde+1);
        if (node->right)        finnHoyde(node->right, hoyde+1);
    }
}


/**
 *  Traverserer/g�r gjennom et tre UNDER 'node'
 *  p� en INORDER m�te ved hjelp av rekursjon.
 *
 *   @param   node  -  Aktuell node � behandle
 *   @see     besok(...)
 */
void traverserInorder(Node* node) {
    if (node) {
        gNivaa++;
        traverserInorder(node->left);
        besok(node);                  //  Bes�ker MELLOM de rekursive kallene!
        traverserInorder(node->right);
        gNivaa--;
    }
}


/**
*  Traverserer/g�r gjennom et tre UNDER 'node'
*  p� en POSTORDER m�te ved hjelp av rekursjon.
*
*   @param   node  -  Aktuell node � behandle
*   @see     besok(...)
*/
void traverserPostorder(Node* node) {
    if (node) {
        gNivaa++;
        traverserPostorder(node->left);
        traverserPostorder(node->right);
        besok(node);                  //  Bes�ker ETTER de rekursive kallene!
        gNivaa--;
    }
}


/**
 *  Traverserer/g�r gjennom et tre UNDER 'node'
 *  p� en PREORDER m�te ved hjelp av rekursjon.
 *
 *   @param   node  -  Aktuell node � behandle
 *   @see     besok(...)
 */
void traverserPreorder(Node* node) {
    if (node) {
        gNivaa++;
        besok(node);                  //  Bes�ker F�R de rekursive kallene!
        traverserPreorder(node->left);
        traverserPreorder(node->right);
        gNivaa--;
    }
}