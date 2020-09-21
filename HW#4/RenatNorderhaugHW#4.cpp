#include <iostream>
#include <string.h>
#include <cstring>
#include <array>
using namespace std;

/*****
 * Author: Renat Norderhaug
 * Class: CS 477
 * 11/8/20
 */

void negPosSort(int pSet[], int pLen);


int main() {
    int numSet[] = {4, 3, -2, 9, -1, 10, 0, 5, 23, -4};
/// to find size of the array
    int setLen = 0;

    int i = 0;
    setLen = sizeof(numSet) / sizeof(numSet[0]);
// sort the set of numbers
    negPosSort(numSet, setLen);
    cout << "[";
    for (i; i < setLen; i++) {
        cout << numSet[i];
        if (i < (setLen - 1)) {
            cout << ",";
        }
    }
    cout << "]" << endl;
    return 0;
}

void negPosSort(int pSet[], int pLen) {
    int i = 0, j = 0;

    for (i; i < pLen; i++) {

        if (pSet[i] < 0) {
            swap(pSet[i], pSet[j]);
            j++;
        }

    }
}






