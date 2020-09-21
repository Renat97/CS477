#include <iostream>
#include <string.h>
#include <cstring>
#include <array>
using namespace std;

#define MAX 30 // Max size of array


// #1
// a) This algorithm checks the next element in the array to see if it has an equal value to the previous element, if the value is equal then it returns false
// a) if the value is not equal then it returns true
// b) running time is 0(^2)

std::array<int,6> ints = {6,5,2,8,3,1};
array<char,6> chars = {'h','e'};

bool method() {
    return true;
}

int inputarray(std::array<int,6> myints) {
    for(int i = 0; i <=myints.size() - 2; i++) {
        for(int j = i+1; j<= myints.size() - 1; j++) {
            if(myints[i] == myints[j]) {
                return false;
            }
            else {
                return true;
            }
        }
    }
}

void bubbleSort(char array[], int size)
{
    for(int i = 0; i < size/2; i++)
    {
        for(int j = i; j < size-i; j++)
            if(array[j] > array[j+1])
            {
                char temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        cout << "After left to right pass #" << i+1 << ": ";
        for(int i = 0; i < 12; i++)
            cout << array[i] << " ";
        cout << endl;
        for(int j = size-i-1; j >= i; j--)
            if(array[j] < array[j-1])
            {
                char temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
            /*
        cout << "After right to left pass #" << i+1 << ": ";
        for(int i = 0; i < 12; i++)
            cout << array[i] << " ";
        cout << endl;
        */
    }
}

//function declaration

void joinarr(int mergarr[], int l, int m, int r);

//calculating the minimum of two numbers

int min(int x, int y) { return (x<y)? x :y; }

void sort_merge(int mergarr[], int n)

{

    int arrlength; //merges after two halves sorted

    int tp;

    for (arrlength=1; arrlength<=n-1; arrlength = 2*arrlength)

    {

        for (tp=0; tp<n-1; tp += 2*arrlength)

        {

            int midval = tp + arrlength - 1;

            int tp2 = min(tp + 2*arrlength - 1, n-1);

            joinarr(mergarr, tp, midval, tp2);

        }

    }

}

void joinarr(int mergarr[], int l, int m, int r)

{

    int i, j, k;

    int s1 = m - l + 1;

    int s2 = r - m;

//two separate array to store the elemetns

    int ar1[s1], ar2[s2];

    cout<<"First Half"<<endl;

    for (i = 0; i < s1; i++)

    {

        ar1[i] = mergarr[l + i]; //one part of array

        cout<<" "<<ar1[i];

    }

    cout<<endl;

    cout<<"Second Half"<<endl;

    for (j = 0; j < s2; j++)

    {

        ar2[j] = mergarr[m + 1+ j]; //other part of array

        cout<<" "<<ar2[j];

    }

    cout<<endl;

    i = 0;

    j = 0;

    k = l;

    cout<<"Merging the Halves"<<endl;

    while (i < s1 && j < s2) //joining the two halves

    {

        if (ar1[i] <= ar2[j])

        {

            mergarr[k] = ar1[i];

            i++;

        }

        else

        {

            mergarr[k] = ar2[j];

            j++;

        }

        k++;

        cout<<" "<<mergarr[k];

    }

    cout<<endl;

    while (i < s1)

    {

        mergarr[k] = ar1[i];

        i++;

        k++;

    }

    while (j < s2)

    {

        mergarr[k] = ar2[j];

        j++;

        k++;

    }

}

void display(int A[], int size) //display function

{

    int i;

    for (i=0; i < size; i++)

        cout<<" "<<A[i]; //printing the values

    cout<<endl;

}

int main() {

    char array[] = "EASYQUESTION";
    cout << "Before the sort: ";
    for(int i = 0; i < 12; i++)
        cout << array[i] << " ";
    cout << endl;

    bubbleSort(array, 12);

    cout << "After the sort: ";
    for(int i = 0; i < 12; i++)
        cout << array[i] << " ";
    cout << endl;

    cout << endl;


    cout << "MERGE SORT ALGORITHM" << " " << endl;

    int n; //varaible declaration

    int mergarr[] = {16,8,29,23,11,19};

    n = sizeof(mergarr)/sizeof(mergarr[0]);

    cout<<"Original Array"<<endl;

    display(mergarr, n); //calling the display function

    sort_merge(mergarr, n); //calling the sort_merge function

    cout<<"Sorted Array"<<endl;

    display(mergarr, n); //calling the display function

    return 0;



}