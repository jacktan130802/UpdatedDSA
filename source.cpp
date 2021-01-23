#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Source1.cpp"

using namespace std;

//int main() {
//sadfasdffassd
//    ifstream inFile;
//    inFile.open("test.txt");
//
//    //error check
//    if (inFile.fail()) {
//        cerr << "Error Opening File" << endl;
//        exit(1);
//    }
//    int count = 0;
//    string box;
//    vector<int> numvect;
//    vector<string> boxvect;
//
//    for (; !inFile.eof(); count++) {
//        getline(inFile, box, '\n');
//        boxvect.push_back(box);
//    }
//    for (int n = 0; n < boxvect.size(); n++) {
//
//        string cha = boxvect[n].substr(11);
//        int m = stoi(cha);
//        numvect.push_back(m);
//        cout << numvect[n] << endl;
//    }
//
//}

int main() {

    ifstream inFile;
    inFile.open("test.txt");

    //error check
    if (inFile.fail()) {
        cerr << "Error Opening File" << endl;
        exit(1);
    }

    string boxString;
    vector<int> boxVect;
    int temp;
    int weight[4] = { 5, 4, 2, 1 }, sum = 0;
    for (int count = 0; !inFile.eof(); count++) {
        getline(inFile, boxString, '\n');
        temp= stoi(boxString.substr(11));
        boxVect.push_back(temp);
    }
    for (int i = 0; i < boxVect.size(); i++) {
        cout << boxVect[i] << endl;
    }

    //Getting total weight value
    for (int i = 0; i < boxVect.size(); i++) {
        sum += weight[i] * boxVect[i];
        cout << "Total No of " << weight[i] << "kg weights - " << boxVect[i] << endl;
    }
    cout << "Total Weight = " << sum;

    return 0;
}
    
 

