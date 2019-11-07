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

int main(){
    vector<int> test1 = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8, -2, -11, 32, 27, 23, 31, 77};

    int mid_point = test1.size()/2;
    int first_list_size = 0;
    int second_list_size = 0;

    if(test1.size()%2 == 0){
        first_list_size = test1.size()/2;
        second_list_size = first_list_size;
    }
    else{
        first_list_size = test1.size()/2;
        second_list_size = first_list_size+1;
    }

    vector<int> left_list;
    vector<int> right_list;

    thread left (sortList, test1, 0, mid_point, ref(left_list));
    thread right (sortList, test1, mid_point, test1.size(), ref(right_list));

    left.join();
    right.join();

    vector<int> sorted_list;
    thread merge (mergeList, left_list, right_list, ref(sorted_list));
    merge.join();


    cout << "Unsorted List" << endl;
    for(auto& a : test1){
        cout << a << ",";
    }
    cout << endl;

    cout << "Left List" << endl;
    for(auto& a: left_list){
        cout << a << ",";
    }
    cout << endl;

    cout << "Right List" << endl;
    for(auto& a : right_list){
        cout << a << ",";
    }
    cout << endl;
    
    cout << "Final Sorted List" << endl;
    for(auto& a: sorted_list){
        cout << a <<",";
    }
    cout << endl;

    return 0;
}