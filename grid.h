#pragma once
 
#ifndef _GRID_H
#define _GRID_H


#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm> 
#include <string> 

using namespace std;

template<typename T>
class Grid {
private:
    struct CELL {
        CELL* Next;
        T Val;
        size_t NumCols;  // total # of columns (0..NumCols-1)
        CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
            Next = _Next;
            Val = _Val;
            NumCols = _NumCols;
        }
    };

    size_t NumRows;  // total # of rows (0..NumRows-1)
    CELL** Rows;     // C array of linked lists

public:
    //
    // default constructor:
    //
    // Called automatically by C++ to construct a 4x4 Grid.
    // All elements are initialized to the default value of T.
    //
    Grid() {
        // initialize 4 rows
        Rows = new CELL*[4];
        NumRows = 4;
        
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), 4);
            CELL* cur = Rows[r];
            
            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }

    //
    // parameterized constructor:
    //
    // Called automatically by C++ to construct a Grid with the
    // specified number of rows and columns.
    // All elements are initialized to the default value of T.
    //
    Grid(size_t r, size_t c) {
        // Initialize the Grid with r rows and c columns
        Rows = new CELL*[r];
        NumRows = r;
        
        // Allocate the first cell of each linked list with default value
        for (size_t i = 0; i < NumRows; ++i) {
            Rows[i] = new CELL(nullptr, T(), c);
            CELL* cur = Rows[i];
            
            // Create the linked list for this row
            for(size_t j = 1; j < Rows[i]->NumCols; ++j) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to construct a Grid that contains a
    // copy of an existing Grid. Deep copy.
    //
    Grid(const Grid<T>& other) {
        // Initialize with the same number of rows as other
        NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        
        // Copy each row's linked list
        for (size_t r = 0; r < NumRows; ++r) {
            // Copy the first cell including NumCols
            Rows[r] = new CELL(nullptr, other.Rows[r]->Val, other.Rows[r]->NumCols);
            
            // Set up pointers to traverse both lists
            CELL* thisCur = Rows[r];
            CELL* otherCur = other.Rows[r]->Next;
            
            // Copy the rest of the linked list for this row
            while (otherCur != nullptr) {
                thisCur->Next = new CELL(nullptr, otherCur->Val);
                thisCur = thisCur->Next;
                otherCur = otherCur->Next;
            }
        }
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated with this Grid.
    //
    virtual ~Grid() {
        // Free the memory for each row's linked list
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = Rows[r];
            
            // Delete each cell in the linked list
            while (cur != nullptr) {
                CELL* next = cur->Next;
                delete cur;
                cur = next;
            }
        }
        
        // Free the array of row pointers
        delete[] Rows;
    }

    //
    // copy operator=
    //
    // Called when you assign one Grid into another, i.e. this = other;
    //
    Grid& operator=(const Grid& other) {
        // Check for self-assignment
        if (this == &other)
            return *this;
        
        // Delete the current grid contents
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = Rows[r];
            
            while (cur != nullptr) {
                CELL* next = cur->Next;
                delete cur;
                cur = next;
            }
        }
        delete[] Rows;
        
        // Copy from other grid
        NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        
        // Copy each row's linked list
        for (size_t r = 0; r < NumRows; ++r) {
            // Copy the first cell including NumCols
            Rows[r] = new CELL(nullptr, other.Rows[r]->Val, other.Rows[r]->NumCols);
            
            // Set up pointers to traverse both lists
            CELL* thisCur = Rows[r];
            CELL* otherCur = other.Rows[r]->Next;
            
            // Copy the rest of the linked list for this row
            while (otherCur != nullptr) {
                thisCur->Next = new CELL(nullptr, otherCur->Val);
                thisCur = thisCur->Next;
                otherCur = otherCur->Next;
            }
        }
        
        return *this;
    }

    //
    // numrows
    //
    // Returns the # of rows in the Grid. The indices range from 0..numrows-1.
    //
    size_t numrows() const {
        return NumRows;
    }

    //
    // numcols
    //
    // Returns the # of columns in row r. The indices range from 0..numcols-1.
    //
    size_t numcols(size_t r) const {
        if (r >= NumRows)
            throw std::invalid_argument("Grid::numcols: row out of range");
        
        return Rows[r]->NumCols;
    }

    //
    // size
    //
    // Returns the total # of elements in the Grid.
    //
    size_t size() const {
        size_t total = 0;
        
        for (size_t r = 0; r < NumRows; ++r) {
            total += Rows[r]->NumCols;
        }
        
        return total;
    }

    //
    // operator()(r, c)
    //
    // Returns a reference to the element at location (r, c). This allows
    // both reading and writing of the element:
    //
    //    grid(r, c) = ...
    //    cout << grid(r, c) << endl;
    //
    T& operator()(size_t r, size_t c) {
        if (r >= NumRows)
            throw std::invalid_argument("Grid::operator(): row out of range");
        
        if (c >= Rows[r]->NumCols)
            throw std::invalid_argument("Grid::operator(): col out of range");
        
        CELL* cur = Rows[r];
        size_t col = 0;
        
        // Traverse the linked list to find the cell at position c
        while (col < c) {
            cur = cur->Next;
            col++;
        }
        
        return cur->Val;
    }

    //
    // operator()(r, c)
    //
    // Returns a reference to the element at location (r, c). This allows
    // both reading and writing of the element:
    //
    //    grid(r, c) = ...
    //    cout << grid(r, c) << endl;
    //
    // This is the const version, which returns a const reference to the element.
    //
    const T& operator()(size_t r, size_t c) const {
        if (r >= NumRows)
            throw std::invalid_argument("Grid::operator(): row out of range");
        
        if (c >= Rows[r]->NumCols)
            throw std::invalid_argument("Grid::operator(): col out of range");
        
        CELL* cur = Rows[r];
        size_t col = 0;
        
        // Traverse the linked list to find the cell at position c
        while (col < c) {
            cur = cur->Next;
            col++;
        }
        
        return cur->Val;
    }

    //
    // _output
    //
    // Outputs the contents of the grid; for debugging purposes. This is not
    // tested.
    //
    void _output() {
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = Rows[r];
            size_t col = 0;
            
            // Traverse the linked list for this row
            while (cur != nullptr) {
                std::cout << "grid(" << r << "," << col << ") = " << cur->Val << std::endl;
                cur = cur->Next;
                col++;
            }
        }
    }
}; 
#endif // _GRID_H