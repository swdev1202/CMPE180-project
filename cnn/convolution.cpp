#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

vector<vector<int>> convoultion(vector<vector<int>>& input, int stride, int filter){
    

    return 
}

int main(){

    srand (time(NULL));

    vector<vector<int>> image1(50, vector<int>(50, 0));
    for(int i=0; i<image1.size(); i++){
        for(int j=0; j<image1[i].size(); j++){
            image1[i][j] = rand() % 256; // randomly assign an integer [0-255]
        }
    }
}