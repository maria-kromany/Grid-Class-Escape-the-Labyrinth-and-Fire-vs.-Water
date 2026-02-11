// gameboard.h
//
// GameBoard class starter code for course project
// University of Illinois at Chicago
// CS 211 - Programming Practicum
// Original Author: Professor Scott Reckinger
//
#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H 

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard {
    private: 
        Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        int numFire;
        int numWater;
        int numWall;
        int numGrass;
        int numEmpty;
        
    public: 
        /* default constructor */
        GameBoard() {
            numFire = 10;
            numWater = 20;
            numWall = 0;
            numGrass = 15*40-30;
            numEmpty = 0;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        // param constructor //
        GameBoard(size_t numRows, size_t numCols) {
            numFire = 10;
            numWater = 20;
            numWall = 0;
            numGrass = numRows*numCols-30;
            numEmpty = 0;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        // destructor //
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }

        void blankBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col) = new Grass(row,col);
                }
            }
        }

        char getCellDisplay(size_t r, size_t c) {
            return board(r,c)->display();
        }

        void setCell(BoardCell* myCell, size_t r, size_t c) {
            board(r,c) = myCell;
        }
    
        void freeCell(size_t r, size_t c) {
            delete board(r,c);
        }

      
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            for (int i = 0; i < numFire; i++) {
                r = rand() % numRows;
                c = rand() % 3;
                while (board(r,c)->display() != ',') {
                    r = rand() % numRows;
                    c = rand() % 3;
                }
                delete board(r,c);
                board(r,c) = new Fire(r,c);
            }

            int sizeMid = numCols - 6;
            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
                numWall++;
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);  
                numWall++;
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
                numWall++;
            }

            for (int i = 0; i < numWater; i++) {
                r = rand() % numRows;
                c = rand() % (numCols-3)+3;
                while (board(r,c)->display() != ',') {
                    r = rand() % numRows;
                    c = rand() % (numCols-3)+3;
                }
                delete board(r,c);
                board(r,c) = new Water(r,c);
            }

            numGrass = numRows*numCols - numFire - numWater - numWall;
            
        }

        // important setters and getters
        void setNumFire(int num) {numFire = num;}
        void setNumWater(int num) {numWater = num;}
        void setNumWall(int num) {numWall = num;}
        void setNumGrass(int num) {numGrass = num;}
        void setNumEmpty(int num) {numEmpty = num;}
        int getNumFire() {return numFire;}
        int getNumWater() {return numWater;}
        int getNumWall() {return numWall;}
        int getNumGrass() {return numGrass;}
        int getNumEmpty() {return numEmpty;}
        size_t getNumRows() {return numRows;}
        size_t getNumCols() {return numCols;}

        // neatly displays the game board, with cell counts 
        void displayBoard(bool printCounts) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
            if (printCounts) {
                cout << "# of Fire  * cells: " << numFire << endl;
                cout << "# of Water ~ cells: " << numWater << endl;
                cout << "# of Empty   cells: " << numEmpty << endl;
                cout << "# of Grass , cells: " << numGrass << endl;
                cout << "# of Wall  x cells: " << numWall << endl;
                cout << "# of ALL gridcells: " << numRows*numCols << endl;
            }
        }

        // SpreadFire() implementation
        void spreadFire(char windDir) {
            // Reset newSpread flag for all cells
            for (size_t row = 0; row < numRows; row++) {
                for (size_t col = 0; col < numCols; col++) {
                    board(row, col)->setNewSpread(false);
                }
            }

            // Updates wind direction for all Fire cells
            for (size_t row = 0; row < numRows; row++) {
                for (size_t col = 0; col < numCols; col++) {
                    if (board(row, col)->display() == '*') {
                        board(row, col)->setWind(windDir);
                    }
                }
            }

            // Processes all Fire cells in order
            for (size_t row = 0; row < numRows; row++) {
                for (size_t col = 0; col < numCols; col++) {
                    // Skip if not Fire or if it's already been spread this round
                    if (board(row, col)->display() != '*' || board(row, col)->getNewSpread()) {
                        continue;
                    }

                    // Gets attempted spread position
                    size_t newRow, newCol;
                    board(row, col)->attemptSpreadTo(newRow, newCol);
                    
                    // Handles boundary checks
                    try {
                        if (newCol >= numCols) {
                            throw runtime_error("Column out of bounds");
                        }
                    } catch (runtime_error& excpt) {
                        newCol = col;
                    }
                    
                    try {
                        if (newRow >= numRows) {
                            throw runtime_error("Row out of bounds");
                        }
                    } catch (runtime_error& excpt) {
                        newRow = row;
                    }
                    
                    // Handles spreading into Wall or Empty
                    bool isDiagonal = (newRow != row && newCol != col);
                    bool needsRedirect = false;
                    
                    try {
                        if (board(newRow, newCol)->display() == 'x' || board(newRow, newCol)->display() == ' ') {
                            throw runtime_error("Cannot spread into Wall or Empty");
                        }
                    } catch (runtime_error& excpt) {
                        needsRedirect = true;
                    }
                    
                    // Handles diagonal redirect logic if needed
                    if (needsRedirect && isDiagonal) {
                        // Tries horizontal movement first (maintaining column change, reset row)
                        size_t horizRow = row;
                        size_t horizCol = newCol;
                        
                        // Tries vertical movement second (maintaining row change, reset column)
                        size_t vertRow = newRow;
                        size_t vertCol = col;
                        
                        // Checks if horizontal movement is valid
                        if (horizCol < numCols && 
                            board(horizRow, horizCol)->display() != 'x' && 
                            board(horizRow, horizCol)->display() != ' ') {
                            // Horizontal movement is valid
                            newRow = horizRow;
                            newCol = horizCol;
                        }
                        // If horizontal isn't valid, checks vertical
                        else if (vertRow < numRows && 
                                 board(vertRow, vertCol)->display() != 'x' && 
                                 board(vertRow, vertCol)->display() != ' ') {
                            // Vertical movement is valid
                            newRow = vertRow;
                            newCol = vertCol;
                        }
                        // If neither works, stays in place
                        else {
                            newRow = row;
                            newCol = col;
                        }
                    } else if (needsRedirect) {
                        newRow = row;
                        newCol = col;
                    }
                    
                    // Handles the cell interactions based on target cell type
                    if (newRow == row && newCol == col) {
                        continue;
                    } else if (board(newRow, newCol)->display() == ',') {
                        // Fire consumes Grass
                        delete board(newRow, newCol);
                        board(newRow, newCol) = new Fire(newRow, newCol);
                        board(newRow, newCol)->setNewSpread(true);
                        board(newRow, newCol)->setWind(windDir);
                        numFire++;
                        numGrass--;
                    } else if (board(newRow, newCol)->display() == '~') {
                        // Fire and Water mix to create Empty
                        delete board(newRow, newCol);
                        board(newRow, newCol) = new Empty(newRow, newCol);
                        numWater--;
                        numEmpty++;
                    }
                    // Fire spreading to Fire is ignored
                }
            }
        }

        // SpreadWater() implementation 
        void spreadWater() {
            // Resets newSpread flag for all cells
            for (size_t row = 0; row < numRows; row++) {
                for (size_t col = 0; col < numCols; col++) {
                    board(row, col)->setNewSpread(false);
                }
            }
            
            // Processes all Water cells
            for (size_t row = 0; row < numRows; row++) {
                for (size_t col = 0; col < numCols; col++) {
                    // Skips if not Water or if it's already been spread this round
                    if (board(row, col)->display() != '~' || board(row, col)->getNewSpread()) {
                        continue;
                    }
                    
                    // Gets attempted spread position
                    size_t newRow, newCol;
                    board(row, col)->attemptSpreadTo(newRow, newCol);
                    
                    // Handles boundary checks
                    try {
                        if (newCol >= numCols) {
                            throw runtime_error("Column out of bounds");
                        }
                    } catch (runtime_error& excpt) {
                        newCol = col;
                    }
                    
                    try {
                        if (newRow >= numRows) {
                            throw runtime_error("Row out of bounds");
                        }
                    } catch (runtime_error& excpt) {
                        newRow = row;
                    }
                    
                    // Handles spreading into Wall or Grass
                    bool isDiagonal = (newRow != row && newCol != col);
                    bool needsRedirect = false;
                    
                    try {
                        if (board(newRow, newCol)->display() == 'x' || board(newRow, newCol)->display() == ',') {
                            throw runtime_error("Cannot spread into Wall or Grass");
                        }
                    } catch (runtime_error& excpt) {
                        needsRedirect = true;
                    }
                    
                    // Handles diagonal redirect logic if needed
                    if (needsRedirect && isDiagonal) {
                        // Try horizontal movement first 
                        size_t horizRow = row;
                        size_t horizCol = newCol;
                        
                        // Tries vertical movement second 
                        size_t vertRow = newRow;
                        size_t vertCol = col;
                        
                        // Checks if horizontal movement is valid
                        if (horizCol < numCols && 
                            board(horizRow, horizCol)->display() != 'x' && 
                            board(horizRow, horizCol)->display() != ',') {
                            // Horizontal movement is valid
                            newRow = horizRow;
                            newCol = horizCol;
                        }
                        // If horizontal isn't valid, checks vertical
                        else if (vertRow < numRows && 
                                 board(vertRow, vertCol)->display() != 'x' && 
                                 board(vertRow, vertCol)->display() != ',') {
                            // Vertical movement is valid
                            newRow = vertRow;
                            newCol = vertCol;
                        }
                        // If neither works, stays in place
                        else {
                            newRow = row;
                            newCol = col;
                        }
                    } else if (needsRedirect) {
            
                        newRow = row;
                        newCol = col;
                    }
                    
                    // Handles the cell interactions based on target cell type
                    if (newRow == row && newCol == col) {
                        continue;
                    } else if (board(newRow, newCol)->display() == ' ') {
                        // Water fills Empty space
                        delete board(newRow, newCol);
                        board(newRow, newCol) = new Water(newRow, newCol);
                        board(newRow, newCol)->setNewSpread(true);
                        numWater++;
                        numEmpty--;
                    } else if (board(newRow, newCol)->display() == '*') {
                        // Water puts out Fire, creating Empty
                        delete board(newRow, newCol);
                        board(newRow, newCol) = new Empty(newRow, newCol);
                        numFire--;
                        numEmpty++;
                    }
                    // Water spreading to Water is ignored
                }
            }
        }
};

#endif //_GAMEBOARD_H