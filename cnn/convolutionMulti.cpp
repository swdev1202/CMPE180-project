#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <future>
#include <stdlib.h>
#include <time.h>

using namespace std;

int matrix_multiplication(int row, int col, const vector<vector<int>>& filter, const vector<vector<int>>& input){
    int multi = 0;
    for(int i=0; i < filter.size(); i++){
        for(int j=0; j<filter[i].size(); j++){
            multi += filter[i][j] * input[row][col];
            col++;
        }
        col -= filter[i].size();
        row++;
    }

    return multi;
}

void convolution(vector<vector<int>>& input, vector<vector<int>>& filter, int& startRow, vector<vector<int>>& output){
    for(int i=0; i<output.size(); i++){
        for(int j=0; j<output[i].size(); j++){
            output[i][j] = matrix_multiplication((i+startRow), j, filter, input);
        }
    }
}

void print2Dvector(vector<vector<int>>& in){
    for(auto& i: in){
        for(auto& a: i){
            cout << a << " ";
        }
        cout << endl;
    }
}

int main(){

    srand (time(NULL));

    // normal
    // int HEIGHT = 50;
    // int WIDTH = 50;
    // extreme
    int HEIGHT = 2160;
    int WIDTH = 3840;

    vector<vector<int>> image1(HEIGHT, vector<int>(WIDTH, 0));
    for(int i=0; i<image1.size(); i++){
        for(int j=0; j<image1[i].size(); j++){
            image1[i][j] = rand() % 2; // randomly assign an integer [0-1]
        }
    }
    vector<vector<int>> filter = {{0,0,0}, {1,1,1}, {0,0,0}};

    // double thread
    int filter_height = filter.size();
    int filter_width = filter[0].size();

    int out_height = (HEIGHT-2)/2;
    int out_width = (WIDTH-2);

    vector<vector<int>> out1(out_height, vector<int> (out_width, 0));
    vector<vector<int>> out2(out_height, vector<int> (out_width, 0));

    auto start = chrono::high_resolution_clock::now();
    int topRow = 0;
    int botRow = out_height;
    thread top(convolution, ref(image1), ref(filter), ref(topRow), ref(out1));
    thread bot(convolution, ref(image1), ref(filter), ref(botRow), ref(out2));

    top.join();
    bot.join();

    vector<vector<int>> result = out1;
    result.insert(result.end(), out2.begin(), out2.end());
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);

    cout << "Test Image Size = (" << image1.size() << "," << image1[0].size() << ")" << endl;
    // print2Dvector(image1);
    cout << "Filter Size = (" << filter.size() << "," << filter[0].size() << ")" <<  endl;
    // print2Dvector(filter);
    cout << "Convoluted Size = (" << result.size() << "," << result[0].size() << ")" << endl;
    // print2Dvector(result);
    cout << "finished, with time(us): " << duration.count() << endl;

    return 0;

}