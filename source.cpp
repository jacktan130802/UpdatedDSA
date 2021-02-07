#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "Rack.h"
using namespace std;

int main()
{
    //Using fstream to read from text file
    ifstream inFile;
    inFile.open("inputs.txt");

    //error check
    if (inFile.fail()) {
        cerr << "Error Opening File" << endl;
        exit(1);
    }

    string boxString, delimiter = "-";
    vector<int> boxVect, rack, limit, rackOut;
    int box;

    for (int count = 0; !inFile.eof(); count++) {
        getline(inFile, boxString, '\n');
        if (boxString == "") {
            //Ignore Empty Spaces
        }
        else {
            size_t found = boxString.find(delimiter);
            box = stoi(boxString.substr(found + 1));
            boxVect.push_back(box);
        }
    }


    int w = boxVect[0];//number of 5kgs
    int x = boxVect[1];//number of 3kgs
    int y = boxVect[2];//number of 2kgs
    int z = boxVect[3];//number of 1 kgs

    int no_rack = boxVect[4]; // Number of Racks
    int box_limit = boxVect[5]; //Number of boxes per rack

    int limit1 = boxVect[6];  //Weight Limit for rack 1
    int limit2 = boxVect[7];  //Weight Limit for rack 2
    int limit3 = boxVect[8];  //Weight Limit for rack 3

    
    //Cheek for inccorect file format    

    if (no_rack > boxVect.size() - 6) {
        cout << "Error with input file format!" << endl;
        cout << "Check if there are more racks then there are limits." <<endl;
        return 0;
    }

    else if (no_rack < boxVect.size() - 6) {
        cout << "Error with input file format!" << endl;
        cout << "Cheek if there are less racks then there are limits." << endl;
        return 0;
    }

    else {

        //Using a vector to store weight limit
        for (int i = 0; i < no_rack; i++) {
            limit.push_back(boxVect[i + 6]);
        }

    }
    vector<int> skips, lastBox;

    //lastBox is just a vector that contains the value 1 (represents a stored box)
    lastBox.push_back(1);
    Rack rack1;
    int temp = 0, skip = 0;

    /*
    Using Rack Class Functions:
    Each fucntion takes to parameters (*number of boxes, rack weight limit)
    *number of boxes[weight specific] - ie number of 5/3/2/1kg weight

    rack1.fiveKG() - Determines number of 5kg weights can be placed in the rack

    rack1.threeKG() - Determines number of 3kg weights can be placed in the rack

    rack1.twoKG() - Determines number of 2kg weights can be placed in the rack

    rack1.oneKG() - Determines number of 1kg weights can be placed in the rack

    Functions listed above peform recursion until the no more of the type of weight can fit
    the rack's limit.

    The remaining value is then passed into the next function as the order above to determine
    number of the next largest weight can be fit into the rack.

    Process:
    Determine max number of the largest weight that can fit onto a rack, pass the reaminder
    to the next largest weight and repeat until no more weights can be fitted onto the rack.
    Note this prioritises the largest weight type.

    To view this process output better uncomment the following lines and execute:
    Line 82, 138-143, 149

    */

    for (int k = 0; k < no_rack; k++) {

        //Uncomment if you want to the output clearly:
        //cout << "Rack " << k + 1 << ": " << endl;

        //Update remainder value and store corresponding amt of 5kg into vector
        for (int i = 0; i < rack1.fiveKG(w, limit[k]); i++) {
            if (rack.size() < box_limit) {
                rack.push_back(5);
                skips.push_back(1);
                temp++;
            }
        }

        limit[k] -= rack1.fiveKG(w, limit[k]) * 5;
        w -= temp;
        temp = 0;

        //Update remainder value and store corresponding amt of 3kg into vector
        for (int i = 0; i < rack1.threeKG(x, limit[k]); i++) {
            if (rack.size() < box_limit) {
                rack.push_back(3);
                skips.push_back(1);
                temp++;
            }
        }
        limit[k] -= rack1.threeKG(x, limit[k]) * 3;
        x -= temp;
        temp = 0;

        //Update remainder value and store corresponding amt of 2kg into vector
        for (int i = 0; i < rack1.twoKG(y, limit[k]); i++) {
            if (rack.size() < box_limit) {
                rack.push_back(2);
                skips.push_back(1);
                temp++;
            }
        }
        limit[k] -= rack1.twoKG(y, limit[k]) * 2;
        y -= temp;
        temp = 0;


        //Update remainder value and store corresponding amt of 1kg into vector
        for (int i = 0; i < rack1.oneKG(z, limit[k]); i++) {
            if (rack.size() < box_limit) {
                rack.push_back(1);
                skips.push_back(1);
                temp++;
            }
        }
        limit[k] -= rack1.oneKG(z, limit[k]) * 1;
        z -= temp;
        temp = 0;

        while (rack.size() != box_limit) {
            rack.push_back(0);
            skips.push_back(0);
        }

        // Storing the rack values into vector called rackOut 
        for (auto i = rack.begin(); i != rack.end(); i++) {

            //Uncomment code below to show the output of the recursion functions above
            /*if (*i == 0)
               cout << "_";
            else
                cout << *i;*/

            rackOut.push_back(*i);
        }

        //Uncomment to for output to be clearer
        //cout << endl;

        rack.clear();

        //Uncomment to show the number of remaining weights -> 5kg | 3kg | 2kg | 1kg respectively
        //cout << endl << "Remaining Weights: " << w << " " << x << " " << y << " " << z << endl << endl;
    }

    //Uncomment to view rackOut 
    /*cout << "Rack Output: " << endl;
    for (auto i = rackOut.begin(); i != rackOut.end(); i++) {
        cout << *i;
    }
    cout << endl << endl;*/

    //Split the vector into a 2d vector storing each sub vector
    vector<vector<int>> rack_split;


    //Spliting the rackOut vector into sub vectors which contain 4 elements each (4 items per rack)
    /*
        Find the end position of the split data (Input: 5531-5520-2100)

        On the first loop:
        The first number is at position 0, the last number is at position 4
        now copy values from position 0-4 and store into rack_sep

        On the second loop:
        The first number is at position 4, the last number is at position 8
        now copy values from position 4-8 and store into rack_sep

        etc...
        */
    for (size_t i = 0; i < rackOut.size(); i += box_limit) {
        auto last = min(rackOut.size(), i + box_limit);
        rack_split.emplace_back(rackOut.begin() + i, rackOut.begin() + last);
    }



    //rack_sep 2d vector has been created by splitting the values into sub vectors of 4 elements
    /*

    example output before reversal: (Input: 5531-5520-2100)

     rack_sep[0][0 - 3] = 5 5 3 1 | -> Rack 3 Intended Outcome : 2 1 0 0
     rack_sep[1][0 - 3] = 5 5 2 0 | -> Rack 2 Intended Outcome : 5 5 2 0
     rack_sep[2][0 - 3] = 2 1 0 0 | -> Rack 1 Intended Outcome : 5 5 3 1

     ^After seperation, output is correct however data is being displayed in the wrong order^

     This can be fixed by pritning the vectors starting from the highest index

    */

    //Run code below to test the output
    /*cout << "Test Output for rack_sep: " << endl;
    for (int i = 2; i >= 0; i--) {
        for (int j = 0; j <4 ; j++) {
            cout << rack_sep[i][j];
        }
        cout << endl;
    }
    cout << endl;*/


    //Usisng a for loop to output all the sub vectors 


    /*
    To Print Rack in Ascending Order:
    for (int j = 0; j < no_rack; j++) {
        int total = 0;
        cout << "Rack: " << (-1 * j) + no_rack << " - ";


    To Print Rack in Descending Order:
    for (int j = no_rack-1; j >= 0; j--) {
        int total = 0;
        cout << "Rack: " << (j+1) << " - ";
    */


    for (int j = no_rack - 1; j >= 0; j--) {
        int total = 0;
        cout << "Rack: " << j + 1 << " -";
        //Printing out the rack_sep vector starting from the highest index (See line 194 and above)
        for (auto i = rack_split[j].begin(); i != rack_split[j].end(); i++) {

            //Cheek for any blanks and replace with an "_" if not display box
            if (*i == 0)
                cout << " _";
            else
                cout << " " << *i;
            total += *i;
        }

        cout << " total(" << total << "kg)";
        cout << endl;
    }

    //Determining any outstanding weights left over displaying the result
    cout << "Outstanding boxes : ";

    if (w == 0 && x == 0 && y == 0 && z == 0) {
        cout << 0;
    }
    else {
        for (int i = 0; i < w; i++) {
            cout << "5 ";
        }
        for (int i = 0; i < x; i++) {
            cout << "3 ";
        }
        for (int i = 0; i < y; i++) {
            cout << "2 ";
        }
        for (int i = 0; i < z; i++) {
            cout << "1 ";
        }
    }
    cout << endl;

    //Uncomment to display the skips vector

    /*cout << "Skips vector:" << endl;
    for (auto i = skips.begin(); i < skips.end(); i++) {
        cout << *i;
    }*/

    vector<int>::iterator it;
    for (auto i = skips.begin(); i < skips.end(); i++) {
        it = find_end(skips.begin(), skips.end(), lastBox.begin(), lastBox.end());
    }

    for (auto i = skips.begin(); i <= it; i++) {
        if (*i == 0) {
            skip++;
        }
    }
    cout << "Skip Spaces: " << skip << " " << endl;
}


