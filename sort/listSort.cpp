#include <vector>
#include <iostream>
#include <chrono>
#include <stdlib.h>    
#include <time.h>     

using namespace std;

void swap(vector<int>& a, int idx1, int idx2){
    int temp = a[idx1];
    a[idx1] = a[idx2];
    a[idx2] = temp;
}

void sortList(vector<int>& a){
    bool swapped = false;
    while(true){
        for(int i=0; i<a.size()-1; i++){
            if(a[i] > a[i+1]){
                swap(a, i, i+1);
                swapped = true;
            }
        }
        
        if(!swapped) break;
        else swapped = false;
    }
    
}

vector<vector<int>> createTestSet(int numTest, int listSize, int range, int shift){
    vector<vector<int>> testset(numTest, vector<int>{});
    srand (time(NULL));

    for(int i=0; i<numTest; i++){
        for(int j=0; j<listSize; j++){
            testset[i].push_back(rand() % range + (shift));
        }
    }

    return testset;
}

void printList(const vector<int>& list){
    for(int i=0; i<list.size(); i++){
        if(i != list.size()-1) cout << list[i] << ", ";
        else cout << list[i] << endl;
    }
}

int main(){
    // normal
    vector<vector<int>> test = createTestSet(5, 10, 20, -10);
    // extreme
    // vector<vector<int>> test = createTestSet(1, 10000, 2000, -1000);

    int i=1;
    for(auto& t : test){
        cout << "test #" << i << " (before sort) = ";
        printList(t);
        auto start = chrono::high_resolution_clock::now();
        sortList(t);
        auto stop = chrono::high_resolution_clock::now();
        cout << "test #" << i << " (after sort) = ";
        printList(t);
        auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
        cout << "test #" << i << " finished, with time(us): " << duration.count() << endl;
        cout << endl;
        i++;
    }

    return 0;
}