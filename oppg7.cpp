#include <iostream>
#include <iomanip>
using namespace std;

const int N = 8;
int antallgrupper = 0, antallIGruppen;
int gBrett[N][N] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

void finnGruppe(int rekke, int kolonne, int & antall) {
    if(gBrett[rekke][kolonne] == 1) {
        antall++;
        gBrett[rekke][kolonne] = 2;
        finnGruppe(rekke, kolonne-1, antall);
        finnGruppe(rekke-1, kolonne, antall);
        finnGruppe(rekke, kolonne+1, antall);
        finnGruppe(rekke+1, kolonne, antall);
    }
}


int main() {
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(gBrett[i][j] == 1) {
                antallIGruppen = 0;
                finnGruppe(i, j, antallIGruppen);
                cout << "Gruppe " << ++antallgrupper << " har " << antallIGruppen << " medlemmer. \n";
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << gBrett[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
