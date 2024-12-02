/**
 *   Programeksempel nr 8 - Traverserer et bin�rt tre p� tre/fire ulike m�ter 
 *                          (vha stack og queue).
 *
 *   Eksempel som viser traversering (vha. stakk/k�) av et bin�rt tre 
 *   p� en preorder, levelorder og inorder m�te.
 *
 *   @file     EKS_08_TreTraversering.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <stack>                     //  stack fra STL
#include <queue>                     //  queue fra STL
using namespace std;


/**
 *  Node (med ID/key/data og venstre/h�yre pekere til nodens barn,
 *        samt en 'besokt' som KAN brukes n�r det er n�dvendig).
 */
struct Node {
    char ID;
    bool besokt;                       //  'besokt' brukes KUN ifm. postorder.
    Node *left, *right;                //  Initierende constructor:
    Node(char id)  {  ID = id;  left = right = nullptr;   besokt = false;  }
};


void  besok(const Node* node);
Node* byggTre();
void  traverserInorder(Node* node);
void  traverserLevelorder(Node* node);
void  traverserPostorder(Node* node);
void  traverserPreorder(Node* node);


stack <Node*> gStakk;                      ///<  Stakk med Node-pekere.
queue <Node*> gKo;                         ///<  K� med Node-pekere.


/**
 *  Hovedprogrammet:
 */
int main()  {
    Node*  root;

    root = byggTre();

    cout << "\n\nPreorder traversering:\n\t";
    traverserPreorder(root);

    cout << "\n\nLevelorder traversering:\n\t";
    traverserLevelorder(root);

    cout << "\n\nInorder traversering:\n\t";
    traverserInorder(root);

    cout << "\n\nPostorder traversering:\n\t";
    traverserPostorder(root);                //  jfr. Oppgave 5.

    cout << "\n\n";
    return 0;
}


/**
 *  Bes�ker (visit) en node - ved � kun skrive ut dens ID/key/data.
 *
 *  'besok'/'visit' kan v�re s� mange ulike operasjoner. 
 *   F.eks (som her) kun en ren utskrift. Men, det kan ogs� v�re slikt som 
 *   � endre dens (ulike) data, sammenligne datene med noe, gj�re beregninger,
 *   endre p� nodens struktur, osv .....
 *
 *  @param   node  -  Aktuell node som skal bes�kes
 */
void  besok(const Node* node) {
    cout << ' ' << node->ID;
}


/**
 *  Bygger et bin�rt eksempel-tre.
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


/**
 *  Traverserer/g�r gjennom et tre UNDER 'node'
 *  p� en INORDER m�te ved � bruke en stakk.
 *
 *   @param   node  -  Aktuell node � behandle
 *   @see     besok(...)
 */
void traverserInorder(Node* node) {
   while (node  ||  !gStakk.empty()) { //  Reell node ELLER noe p� stakken:
        if (node) {                    //  Reell node:
           gStakk.push(node);          //  Push'es p� stakken.
           node = node->left;          //  G�r til venstre.
        } else {                       //  'node' == nullptr:
           node = gStakk.top();  gStakk.pop();  //  pop'er en node.
           besok(node);                         //  Bes�ker den.
           node = node->right;                  //  G�r til h�yre.
        }
   }
}


/**
 *  Traverserer/g�r gjennom et tre UNDER 'node'
 *  p� en LEVELORDER m�te ved � bruke en k�.
 *
 *   @param   node  -  Aktuell node � behandle
 *   @see     besok(...)
 */
void traverserLevelorder(Node* node) {
    if (node) {                                  //  Reell node:
        gKo.push(node);                          //  Legger rota i k�en.
        while (!gKo.empty()) {                   //  Fortsatt noder igjen:
            node = gKo.front();   gKo.pop();     //  Tar ut f�rste node. 
            besok(node);                         //  Bes�ker den.
            if (node->left)  gKo.push(node->left);  //  Legger evt. venstre og
            if (node->right) gKo.push(node->right); //  h�yre subtre BAKERST. 
        }
    }
}


/**
 *  Traverserer/g�r gjennom et tre UNDER 'node'
 *  p� en POSTORDER m�te ved � bruke en stakk.
 *
 *   @param   node  -  Aktuell node � behandle
 *   @see     besok(...)
 */
void traverserPostorder(Node* node) {
    if(node) {
        gStakk.push(node);
        while(!gStakk.empty()) {
            node = gStakk.top();  gStakk.pop();
            if(node->besokt)    besok(node);
            else {
                node->besokt = true;
                if (node->right)  gStakk.push(node->right); 
                if (node->left)   gStakk.push(node->left);
            }
        }
    }
}


/**
 *  Traverserer/g�r gjennom et tre UNDER 'node'
 *  p� en PREORDER m�te ved � bruke en stakk.
 *
 *   @param   node  -  Aktuell node � behandle
 *   @see     besok(...)
 */
void traverserPreorder(Node* node) {
    if (node) {                                  //  Reell node:
        gStakk.push(node);                       //  Legger rota p� stakken.
        while (!gStakk.empty()) {                //  Fortsatt noder igjen:
            node = gStakk.top();   gStakk.pop(); //  Tar av �verste node.
            besok(node);                         //  Bes�ker den.
            if (node->right)  gStakk.push(node->right); //  Push'er evt. h�yre
            if (node->left)   gStakk.push(node->left);  //  og venstre subtre.
        }
    }
}