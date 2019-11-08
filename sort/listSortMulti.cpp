#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <future>

using namespace std;

void swap(vector<int>& a, int idx1, int idx2){
    int temp = a[idx1];
    a[idx1] = a[idx2];
    a[idx2] = temp;
}

void sortList(const vector<int>& a, int startIdx, int endIdx, vector<int>& sorted){
    for(int i=startIdx; i<endIdx; i++){
        sorted.push_back(a[i]);
    }

    bool swapped = false;
    while(true){
        for(int i=0; i<sorted.size()-1; i++){
            if(sorted[i] > sorted[i+1]){
                swap(sorted, i, i+1);
                swapped = true;
            }
        }
        
        if(!swapped) break;
        else swapped = false;
    }
}

void mergeList(const vector<int>& a, const vector<int>& b, vector<int>& sorted){
    auto a_itr = a.begin();
    auto b_itr = b.begin();

    bool a_turn = false;

    while(true){
        if(*a_itr > *b_itr){
            sorted.push_back(*b_itr);
            b_itr++;
        }
        else{
            sorted.push_back(*a_itr);
            a_itr++;
        }

        if(a_itr == a.end()){
            a_turn = false;
            break;
        }
        else if(b_itr == b.end()){
            a_turn = true;
            break;
        }
    }

    if(a_turn){
        while(a_itr != a.end()){
            sorted.push_back(*a_itr);
            a_itr++;
        }
    }
    else{
        while(b_itr != b.end()){
            sorted.push_back(*b_itr);
            b_itr++;
        }
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
    //vector<vector<int>> test = createTestSet(1, 10000, 2000, -1000);

    int i=1;
    for(auto& t : test){
        cout << "test #" << i << " (before sort) = ";
        printList(t);

        int mid_point = t.size()/2;
        int first_list_size = 0;
        int second_list_size = 0;

        if(t.size()%2 == 0){
            first_list_size = t.size()/2;
            second_list_size = first_list_size;
        }
        else{
            first_list_size = t.size()/2;
            second_list_size = first_list_size+1;
        }

        vector<int> left_list;
        vector<int> right_list;

        auto start = chrono::high_resolution_clock::now();
        thread left (sortList, t, 0, mid_point, ref(left_list));
        thread right (sortList, t, mid_point, t.size(), ref(right_list));

        left.join();
        right.join();

        vector<int> sorted_list;
        thread merge (mergeList, left_list, right_list, ref(sorted_list));
        merge.join();
        auto stop = chrono::high_resolution_clock::now();

        cout << "test #" << i << " (after sort) = ";
        printList(sorted_list);
        auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
        cout << "test #" << i << " finished, with time(us): " << duration.count() << endl;
        cout << endl;
        i++;
    }
    return 0;
}