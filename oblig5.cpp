#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;

struct Node {
char ID; // Nodens id/key/data
Node* naboer[10]; // Nodens naboer (ligger i indeks nr. 0 - 9)
int antNaboer; // Antall naboer (max. 10 stk)
 bool besokt; // Om besøkt noden hittil eller ei

Node(char id, int ant) {    ID = id;     besokt = false;    antNaboer = ant;    };
};

void brettUt(Node* node);
Node* kopier(Node* node);


int main () {
    Node* node1 = new Node ('E', 0);
    Node* node2 = new Node ('D', 1);    node2->naboer[0] = node1;
    Node* node3 = new Node ('C', 2);    node3->naboer[0] = node2;   node3->naboer[1] = node1;
    node1 = new Node ('B', 1);          node1->naboer[0] = node2;
    node2 = new Node ('A', 2);          node2->naboer[0] = node1;   node2->naboer[1] = node3;

    brettUt(node2);
}


void brettUt(Node* node) {
    Node* kopi = nullptr;

    node->besokt = true;
    for(int i = 0; i < node->antNaboer; i++) {
        if(node->naboer[i]->besokt) {
            cout << node->ID << " lager Kopi av: " << node->naboer[i]->ID << endl;
            kopi = kopier(node->naboer[i]);
            node->naboer[i] = kopi;
        }
        brettUt(node->naboer[i]);
    }
}


Node* kopier(Node* node) {
 Node* kopi = new Node(node->ID, node->antNaboer);
 for (int i = 0; i < node->antNaboer; i++) {
    kopi->naboer[i] = kopier(node->naboer[i]);
    cout << kopi->ID << " lager videre Kopi av: " << kopi->naboer[i]->ID << endl;
 }
 return kopi;
}