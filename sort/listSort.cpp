#include <vector>
#include <iostream>

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

int main(){
    vector<int> test1 = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};

    sortList(test1);

    for(auto& a : test1){
        cout << a << endl;
    }

    return 0;
}