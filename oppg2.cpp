#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;

template <typename T1, typename T2>                //  'template'!  'T': fleksibel datatype!

class Map {
    private:
        T1* keypair;
        T2* data;
        int kapasitet, antall;
    
    public: 
        Map(const int lengde = 10) {
            antall = 0; kapasitet = lengde; keypair = new T1[lengde]; data = new T2[lengde]; }
        
        ~Map() {delete [] data; delete [] keypair;}
        
        int amount() const { return antall; }
        
        int capacity() const { return kapasitet; }
        
        void innhold() const {
            for(int i = 0; i < antall; i++) {
                cout << "nr: " << keypair[i] << " - " << data[i] << endl;
            }
        }
        void insert(const T1 first, const T2 second) {
            bool check = true;

            if(antall < kapasitet) {
                for(int i = 0; i < antall; i++) {
                    if(keypair[i] == first) check = false;
                }
                if (check) {
                    keypair[antall] = first;
                    data[antall++]  = second;
                } else cout << "Error: key already in use. \n\n";
            } else cout << "Error: Max capacity. \n\n";
        }

        T2 finn(const T1 key) {
            for(int i = 0; i < antall; i++) {
                if (keypair[i] == key) return data[i];
            }
        }

        void endre(const T1 key, const T2 dta) {
            for(int i = 0; i < antall; i++) {
                if(keypair[i] == key) data[i] = dta;
            }
        }

        void slette(const T1 key) {
            for(int i = 0; i < antall; i++) {
                if(keypair[i] == key) {
                    for(int j = i; j < antall; j++) {
                        data[j] = data[j+1];
                        keypair[j] = keypair[j+1];
                    }
                    antall--;
                }
            }
        }

};


int main() {

    // Create a Map with int as the template type
    Map<int, int> intMap;

    // Insert some data into intMap
    intMap.insert(1, 100);
    intMap.insert(2, 200);
    intMap.insert(3, 300);
    
    // Try to insert a duplicate key
    intMap.insert(2, 400);  // Should display an error
    
    // Display the contents of intMap
    cout << "Contents of intMap:" << endl;
    intMap.innhold();

    // Find a value by key
    int foundValue = intMap.finn(2);
    cout << "Found value for key 2: " << foundValue << endl;

    // Delete a key-value pair
    intMap.slette(2);
    cout << "Contents of intMap after deleting key 2:" << endl;
    intMap.innhold();

    // Try to find a deleted key
    foundValue = intMap.finn(2);
    cout << "Tried to find deleted key 2, found: " << foundValue << endl;

    intMap.endre(1, 111);
    cout << "Contents of intMap after changing key 1:\n";
    intMap.innhold();
    // Create a Map with string as the template type
    Map<int, string> stringMap;

    // Insert some data into stringMap
    stringMap.insert(1, "Apple");
    stringMap.insert(2, "Banana");
    stringMap.insert(3, "Cherry");

    // Display the contents of stringMap
    cout << "\nContents of stringMap:" << endl;
    stringMap.innhold();

    // Find a value by key
    string foundString = stringMap.finn(3);
    cout << "Found value for key 3: " << foundString << endl;

    // Delete a key-value pair
    stringMap.slette(3);
    cout << "Contents of stringMap after deleting key 1:" << endl;
    stringMap.innhold();

    stringMap.endre(1, "Grapes");
    cout << "Contents of stringMap after changing key 1:\n";
    stringMap.innhold();
    
    return 0;
}
