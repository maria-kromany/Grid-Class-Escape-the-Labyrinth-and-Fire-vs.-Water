#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change constant kYourNetID to store your netID 
 *    - your submission will be manually inspected to ensure
 *      you have used the exact string that is your netID
 *    - thus, it is vital you understand what your netID is
 *    - ex: Professor Reckinger's email is scotreck@uic.edu, so
 *          Professor Reckinger's netID is scotreck     
 *    - ex: Student Sparky's email is sspark211@uic.edu, so
 *          Student Sparky's netID is sspark211 
 * WARNING: Once you've set set this constant and started 
 * exploring your maze, do NOT edit the value of kYourNetID. 
 * Changing kYourNetID will change which maze you get back, 
 * which might invalidate all your hard work!
 */
const string kYourNetID = "mkari5";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "EWSSESEENWNNE";
const string kPathOutOfTwistyMaze = "EENWSWSWESW";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    
    
    /* TO DO: Delete this comment and the next few lines, 
     * then implement this function.
     */
    if (start == nullptr) {
        return false;
    } 
    for (char move: moves) {
        if (move != 'N' && move != 'S' && move != 'E' && move != 'W') {
            return false;
        }
    } 
    bool foundSpellbook = false; 
    bool foundPotion = false;
    bool foundWand = false; 

    MazeCell* current = start;

    if (current->whatsHere == "Spellbook"){
        foundSpellbook = true;
    } else if (current->whatsHere == "Potion") {
        foundPotion = true;
    } else if (current->whatsHere == "Wand") {
        foundWand = true;
    }
    for (char move: moves) {
        MazeCell* next = nullptr;
        switch (move) {
            case 'N': 
                next = current->north;
                break;
            case 'S': 
                next = current->south;
                break; 
            case 'E': 
                next = current->east;
                break;
            case 'W': 
                next = current->west;
                break;
        } 
        if (next == nullptr) {
            return false;
        } 
        current = next; 

        if (current->whatsHere == "Spellbook") {
            foundSpellbook = true;
        } else if (current->whatsHere == "Potion") {
            foundPotion = true;
        } else if(current->whatsHere == "Wand") {
            foundWand = true;
        }
    } 
    return foundSpellbook && foundPotion && foundWand;    
}
