#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    
    map<bool, string> myMap;
    string myString;
    cin >> myString;
    map<bool, string>::iterator it;
    myMap.insert(pair<bool, string>(true, myString));

    //Pega o primeiro elemento dentro de um map para que seja possível imprimir dentro do terminal
    //Será útil para quando precisarmos sabe
    for (it = myMap.begin(); it != myMap.end(); it++) {
        cout << "Primeiro: " << it->first  << ", Segundo : " << it->second << endl;
    }
}