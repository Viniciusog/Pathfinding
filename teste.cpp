#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    ifstream myFile("arquivo.txt");
    std::string myLine;
    int indexChar;
    int indexStart = 0;
    while (myFile.good()) {
        getline(myFile, myLine);
        string copyLine = myLine;

        indexChar = copyLine.find(",");
        
        while (indexChar != std::string::npos) {
            string substring = myLine.substr(indexStart, indexChar);
            cout << "Substring: " << substring << endl;
            // the next start is after ,
            indexStart = indexChar + 1;
            // replace in the copy of the string just to now if there are any more , to be found
            copyLine.replace(indexChar, 1, "|");
            indexChar = copyLine.find(",");
        }

        cout << myLine.substr(indexStart) << endl;
    }

   /*  ifstream file("arquivo.txt");

   

    string myLine;
    int index;
    while (file.good()) {
        getline(file, myLine);
        index = myLine.find(",");
        cout << "index: " << index << endl;
        string substring = myLine.substr(0, index);
        cout << "Substring: " << substring << endl;
    }
    return 0; */
}