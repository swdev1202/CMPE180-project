#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <future>

using namespace std;

#define NUM_THREADS 9

class SudokuBoard{
    public:
        vector<vector<int>> board;

        SudokuBoard(vector<vector<int>> data) {
            board = data;
        }
};


bool checkSum(const vector<int>& a){
    int sum = 0;
    for(int s : a){
        sum += s;
    }

    return (sum == 45)? true:false; 
}

void calculateSum(int& sum, const vector<int>& a){
    for(int s : a){
        sum += s;
    }
    pthread_exit(NULL);
}

int main(){
    // prepare game boards
    vector<SudokuBoard> gameBoards;

    // board reading container
    vector<vector<int>> board_container;

    int numBoards = 0;
    int boardReadingCnt = 1;
    string line = "";
    ifstream infile("sudoku_boards.txt");
    if(infile.is_open()){
        while(getline(infile,line)){
            if(line.size() < 9){
                // this means you just read the first line
                // this line contains how many boards I have
                numBoards = stoi(line);
            }
            else{
                // if we are reading the boards
                vector<int> row;
                for(int i=0; i<9; i++){
                    row.push_back(line[i]-48);
                }
                
                board_container.push_back(row);

                boardReadingCnt++;

                if(boardReadingCnt > 9){
                    // vector is full now, insert into gameboard
                    SudokuBoard temp(board_container);
                    gameBoards.push_back(temp);
                    board_container.clear();
                    boardReadingCnt = 1;
                }
            }
        }
    }

    /*----------------------------------------------------------------*/
    SudokuBoard sample = gameBoards[0];
    
    for(int i=0; i<NUM_THREADS; i++){
        auto future = async(checkSum, sample.board[i]);
        cout << future.get() << endl;
    }

    bool result = true;
    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);

    cout << result << ", with time(us): " << duration.count() << endl;
    return 0;
}