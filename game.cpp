#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "grid.h"
#include "boardcell.h"
#include "gameboard.h"

using namespace std;

int main() {
    cout << "Welcome to Fire vs. Water Game!" << endl;
    cout << "================================" << endl;

    // Default values
    size_t numRows = 15;
    size_t numCols = 40;
    int numFire = 10;
    int numWater = 20;
    int waterReps = 4;
    int seed = -1;
    
    // Get game parameters
    cout << "Enter the number of rows (5-30): ";
    cin >> numRows;
    
    cout << "Enter the number of columns (5-80): ";
    cin >> numCols;
    
    cout << "Enter the number of initial Fire cells (1-20): ";
    cin >> numFire;
    
    cout << "Enter the number of initial Water cells (1-40): ";
    cin >> numWater;
    
    cout << "Enter the number of Water spread repetitions per round (1-10): ";
    cin >> waterReps;
    
    // Gets seed for random number generator
    cout << "Enter a seed for random number generator (-1 for time-based seed): ";
    cin >> seed;
    
    if (seed == -1) {
        seed = time(nullptr);
    }
    
    // Creates and initializes the game board
    GameBoard game(numRows, numCols);
    game.setNumFire(numFire);
    game.setNumWater(numWater);
    game.setupBoard(seed);
    
    // Displays initial state
    cout << "\nInitial Game Board:" << endl;
    game.displayBoard(true);
    
    // Main game loop
    bool gameOver = false;
    int roundCount = 0;
    
    while (!gameOver) {
        roundCount++;
        cout << "\n=== Round " << roundCount << " ===" << endl;
        
        // Gets wind direction
        char windDir;
        cout << "Enter wind direction (q/w/e/a/s/d/z/x/c or k to quit): ";
        cin >> windDir;
        
        // Checks for game termination
        if (windDir == 'k') {
            cout << "Game terminated by user." << endl;
            break;
        }
        
        // Validates wind direction input
        if (windDir != 'q' && windDir != 'w' && windDir != 'e' && 
            windDir != 'a' && windDir != 's' && windDir != 'd' && 
            windDir != 'z' && windDir != 'x' && windDir != 'c') {
            windDir = 's'; // Default to stay
        }
        
        // Spread Fire once
        game.spreadFire(windDir);
        
        // Spread Water multiple times
        for (int i = 0; i < waterReps; i++) {
            game.spreadWater();
        }
        
        // Displays updated board
        cout << "\nGame Board after Round " << roundCount << ":" << endl;
        game.displayBoard(true);
        
        // Checks for game end conditions
        if (game.getNumFire() == 0) {
            cout << "\nGame Over! All Fire has been extinguished by Water." << endl;
            gameOver = true;
        } else if (game.getNumGrass() == 0) {
            cout << "\nGame Over! All Grass has been consumed by Fire." << endl;
            gameOver = true;
        }
    }
    
    return 0;
}