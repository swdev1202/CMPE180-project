#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <future>

using namespace std;

class SudokuBoard{
    public:
        vector<vector<int>> board;

        SudokuBoard(vector<vector<int>> data) {
            board = data;
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

void rowChecker(const SudokuBoard& game_board, bool& result){
    result = true; // initially it's true
    for(int i=0; i<9; i++){ // every row
        int rowsum = 0;
        for(int j=0; j<9; j++){ // every column
            rowsum += game_board.board[i][j];
        }
        if(rowsum != 45) result &= false;
    }
}

void columnChecker(const SudokuBoard& game_board, bool& result){
    result = true;
    vector<int> colSum = {0,0,0,0,0,0,0,0,0};
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            colSum[j] += game_board.board[i][j];
        }
    }

    for(auto& sum : colSum){
        if(sum != 45) result &= false;
    }
}

void squareChecker(const SudokuBoard& game_board, int sqNum, bool& result){
    // sqNum ranging from 0 to 8
    // {0,1,2} => row 0,1,2 | {3,4,5} => row 3,4,5 | {6,7,8} => row 6,7,8
    // {0,3,6} => col 0,1,2 | {1,4,7} => col 3,4,5 | {2,5,8} => col 6,7,8

    int startRow = 0;
    if(sqNum >= 0 && sqNum <=2) startRow = 0;
    else if(sqNum >=3 && sqNum <= 5) startRow = 3;
    else if(sqNum >=6 && sqNum <= 8) startRow = 6;
    else return;

    int startCol = 0;
    if(sqNum == 0 || sqNum == 3 || sqNum == 6) startCol = 0;
    else if(sqNum == 1 || sqNum == 4 || sqNum == 7) startCol = 3;
    else if(sqNum == 2 || sqNum == 5 || sqNum == 8) startCol = 6;
    else return;

    int sum = 0;
    for(int i=startRow; i<startRow+3; i++){
        for(int j=startCol; j<startCol+3; j++){
            sum += game_board.board[i][j];
        }
    }

    result = (sum != 45)? false:true;
}

void loadGameBoards(string filepath, vector<SudokuBoard>& board){
    // board reading container
    vector<vector<int>> board_container;

    int numBoards = 0;
    int boardReadingCnt = 1;
    string line = "";
    ifstream infile(filepath);
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
                    board.push_back(temp);
                    board_container.clear();
                    boardReadingCnt = 1;
                }
            }
        }
    }
}

int main(int argc, char** argv){
    int NORMAL = (int)*argv[1] - '0';
    string filename;
    if(NORMAL) filename = "sudoku_board_single.txt";
    else filename = "sudoku_boards.txt";

    // prepare game boards
    vector<SudokuBoard> gameBoards;

    // load data onto gameboards
    loadGameBoards(filename, gameBoards);

    for(int i=0; i<gameBoards.size(); i++){
        if(NORMAL) gameBoards[i].printBoard();

        auto start = chrono::high_resolution_clock::now();
        bool final_result = true;
        bool row_result;
        bool col_result;
        bool sq0_result;
        bool sq1_result;
        bool sq2_result;
        bool sq3_result;
        bool sq4_result;
        bool sq5_result;
        bool sq6_result;
        bool sq7_result;
        bool sq8_result;

        thread row_check (rowChecker, gameBoards[i], ref(row_result));
        thread col_check (columnChecker, gameBoards[i], ref(col_result));
        thread sq0_check (squareChecker, gameBoards[i], 0, ref(sq0_result));
        thread sq1_check (squareChecker, gameBoards[i], 1, ref(sq1_result));
        thread sq2_check (squareChecker, gameBoards[i], 2, ref(sq2_result));
        thread sq3_check (squareChecker, gameBoards[i], 3, ref(sq3_result));
        thread sq4_check (squareChecker, gameBoards[i], 4, ref(sq4_result));
        thread sq5_check (squareChecker, gameBoards[i], 5, ref(sq5_result));
        thread sq6_check (squareChecker, gameBoards[i], 6, ref(sq6_result));
        thread sq7_check (squareChecker, gameBoards[i], 7, ref(sq7_result));
        thread sq8_check (squareChecker, gameBoards[i], 8, ref(sq8_result));

        row_check.join();
        col_check.join();
        sq0_check.join();
        sq1_check.join();
        sq2_check.join();
        sq3_check.join();
        sq4_check.join();
        sq5_check.join();
        sq6_check.join();
        sq7_check.join();
        sq8_check.join();

        final_result = row_result && col_result && sq0_result &&
                        sq1_result && sq2_result && sq3_result &&
                        sq4_result && sq5_result && sq6_result &&
                        sq7_result && sq8_result;

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);

        std::cout << (i+1) << "th result = " << final_result << ", with time(us): " << duration.count() << std::endl;
    } 
    return 0;
}