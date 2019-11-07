#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

class SudokuBoard{
    private:
        vector<vector<int>> board;
    public:
        SudokuBoard(vector<vector<int>> data) {
            board = data;
        }

        bool validateBoard(){
            // data storage for the columns
            vector<int> columnSums = {0,0,0,0,0,0,0,0,0};
            vector<int> squareSums = {0,0,0};

            for(int i=0; i<9; i++){
                int rowSum = 0;
                for(int j=0; j<9; j++){
                    rowSum += board[i][j];
                    columnSums[j] += board[i][j];

                    squareSums[j/3] += board[i][j];
                }
                // row check once row is calculated
                if(rowSum != 45) return false;

                if(i == 2 || i == 5 || i == 8){
                    // check square boxes
                    for(int k=0; k<3; k++){
                        if(squareSums[k] != 45) return false;
                        
                        // if found no false, initialize back
                        squareSums[k] = 0;
                    }
                }
            }

            // column check at the end
            for(int i=0; i<9; i++){
                if(columnSums[i] != 45) return false;
            }

            return true;
        }

        bool validateBoard_dumb(){
            vector<int> rowSums = {0,0,0,0,0,0,0,0,0};
            vector<int> columnSums = {0,0,0,0,0,0,0,0,0};
            vector<int> squareSums = {0,0,0,0,0,0,0,0,0};

            int squareJumper = 0;
            for(int i=0; i<9; i++){
                if(i == 3 || i == 6){
                    squareJumper += 3;
                }
                for(int j=0; j<9; j++){
                    rowSums[i] += board[i][j];
                    columnSums[j] += board[i][j];
                    squareSums[squareJumper + j/3] += board[i][j];
                }
            }

            bool result = true;

            for(int i=0; i<9; i++)
            {
                if(rowSums[i] != 45 || columnSums[i] != 45 || squareSums[i] != 45) result = false;
            }
            return result;
        }

        bool validateBoard_dumbest() {
            vector<int> rowSums = {0,0,0,0,0,0,0,0,0};
            vector<int> columnSums = {0,0,0,0,0,0,0,0,0};
            vector<int> squareSums = {0,0,0,0,0,0,0,0,0};

            int squareJumper = 0;

            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    rowSums[i] += board[i][j];
                }
            }

            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    columnSums[j] += board[i][j];
                }
            }


            for(int i=0; i<9; i++){
                if(i == 3 || i == 6){
                    squareJumper += 3;
                }
                for(int j=0; j<9; j++){
                    squareSums[squareJumper + j/3] += board[i][j];
                }
            }

            bool result = true;
            for(int i=0; i<9; i++){
                if(rowSums[i] != 45 || columnSums[i] != 45 || squareSums[i] !=45) result = false;
            }

            return result;

        }

        void printBoard(){
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }
};

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


    bool result = true;
    
    for(int i=0; i<gameBoards.size(); i++){
        auto start = chrono::high_resolution_clock::now();
        result = gameBoards[i].validateBoard();
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
        cout << (i+1) << "th result = " << result << ", with time(us): " << duration.count() << endl;
    }
    return 0;
}