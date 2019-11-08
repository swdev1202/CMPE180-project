#include <vector>
#include <iostream>
#include <chrono>
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

vector<vector<int>> convoultion(vector<vector<int>>& input, vector<vector<int>>& filter){
    int filter_size = filter.size();
    int input_size = input.size();

    // only stride 1
    vector<vector<int>> output(input_size-2, vector<int> (input_size-2, 0));

    for(int i=0; i<output.size(); i++){
        for(int j=0; j<output[i].size(); j++){
            output[i][j] = matrix_multiplication(i, j, filter, input);
        }
    }

    return output;
}

void print2Dvector(vector<vector<int>>& in){
    for(auto& i: in){
        for(auto& a: i){
            cout << a << " ";
        }
        cout << endl;
    }
}

int main(int argc, char** argv){
    srand (time(NULL));
    int NORMAL = (int)*argv[1] - '0';
    int HEIGHT, WIDTH;

    if(NORMAL) HEIGHT = 20, WIDTH = 20;
    else HEIGHT = 2160, WIDTH = 3840;

    vector<vector<int>> image1(HEIGHT, vector<int>(WIDTH, 0));
    for(int i=0; i<image1.size(); i++){
        for(int j=0; j<image1[i].size(); j++){
            image1[i][j] = rand() % 2; // randomly assign an integer [0-1]
        }
    }
    vector<vector<int>> filter = {{0,0,0}, {1,1,1}, {0,0,0}};

    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> result = convoultion(image1, filter);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);

    cout << "Test Image Size = (" << image1.size() << "," << image1[0].size() << ")" << endl;
    if(NORMAL) print2Dvector(image1);
    cout << "Filter Size = (" << filter.size() << "," << filter[0].size() << ")" <<  endl;
    if(NORMAL) print2Dvector(filter);
    cout << "Convoluted Size = (" << result.size() << "," << result[0].size() << ")" << endl;
    if(NORMAL) print2Dvector(result);
    cout << "finished, with time(us): " << duration.count() << endl;

    return 0;

}