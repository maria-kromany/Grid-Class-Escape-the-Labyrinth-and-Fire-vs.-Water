// boardcell.h
//
// BoardCell class starter code for course project
// University of Illinois at Chicago
// CS 211 - Programming Practicum
// Original Author: Professor Scott Reckinger
//

#ifndef _BOARDCELL_H
#define _BOARDCELL_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// First, the BoardCell abstract base class 
class BoardCell {
    private:
        size_t myRow; // current row for this board cell in a 2D grid
        size_t myCol; // current column for this board cell in a 2D grid
        bool newSpread; // true = this board cell was already updated as a result of a previous spread
        
    public:  
        BoardCell() {
            myRow = 0;
            myCol = 0;
            newSpread = false;
        } // default constructor
        
        virtual ~BoardCell() {} // destructor (do nothing)
        
        virtual char display() = 0; // pure virtual function; this is an abstract base class

        virtual void attemptSpreadTo(size_t& newR, size_t& newC) {
            // Default behavior is to stay in place
            newR = myRow;
            newC = myCol;
        }
        
        virtual void setWind(char inChar) {}

        void setRow(size_t r) {myRow = r;}
        size_t getRow() {return myRow;}
        void setCol(size_t c) {myCol = c;}
        size_t getCol() {return myCol;}
        void setPos(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        void setNewSpread(bool u) {newSpread = u;}
        bool getNewSpread() {return newSpread;}
}; // BoardCell (abstract base class)

// Derived classes
class Fire: public BoardCell {
    private:
        char windDir;

    public:
        Fire(size_t r, size_t c) {
            setRow(r);
            setCol(c);
            windDir = 's';
        }
        
        virtual char display() {
            return '*';
        }
        
        virtual void setWind(char inChar) {
            windDir = inChar;
        }
        
        virtual void attemptSpreadTo(size_t& newR, size_t& newC) {
            // Starts with current position
            newR = getRow();
            newC = getCol();
            
            // Spreads based on wind direction 
            switch (windDir) {
                case 'q': // Up and left
                    if (getRow() > 0) newR = getRow() - 1;
                    if (getCol() > 0) newC = getCol() - 1;
                    break;
                case 'w': // Up
                    if (getRow() > 0) newR = getRow() - 1;
                    break;
                case 'e': // Up and right
                    if (getRow() > 0) newR = getRow() - 1;
                    newC = getCol() + 1;
                    break;
                case 'a': // Left
                    if (getCol() > 0) newC = getCol() - 1;
                    break;
                case 's': // Stay
                    break;
                case 'd': // Right
                    newC = getCol() + 1;
                    break;
                case 'z': // Down and left
                    newR = getRow() + 1;
                    if (getCol() > 0) newC = getCol() - 1;
                    break;
                case 'x': // Down
                    newR = getRow() + 1;
                    break;
                case 'c': // Down and right
                    newR = getRow() + 1;
                    newC = getCol() + 1;
                    break;
                default: // Any other input, stays in place
                    break;
            }
        }
}; // Fire

class Water: public BoardCell {
    public:
        Water(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display() {
            return '~';
        }
        
        virtual void attemptSpreadTo(size_t& newR, size_t& newC) {
            // Starts with current position
            newR = getRow();
            newC = getCol();
            
            // Gets random offsets for row and column
            int rowOffset = rand() % 3 - 1;
            int colOffset = rand() % 3 - 1;
            
            // Applies row offset carefully 
            if (rowOffset < 0 && getRow() == 0) {
                // Stay in current row if at top edge
            } else {
                newR = getRow() + rowOffset;
            }
            
            // Applies column offset carefully 
            if (colOffset < 0 && getCol() == 0) {
                // Stays in current column if at left edge
            } else {
                newC = getCol() + colOffset;
            }
        }
}; // Water

class Grass: public BoardCell {
    public:
        Grass(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display() {
            return ',';
        }
}; // Grass

class Wall: public BoardCell {
    public:
        Wall(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display() {
            return 'x';
        }
}; // Wall

class Empty: public BoardCell {
    public:
        Empty(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display() {
            return ' ';
        }
}; // Empty

#endif //_BOARDCELL_H