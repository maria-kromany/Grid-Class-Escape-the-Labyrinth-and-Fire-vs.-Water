# Grid-Class-Escape-the-Labyrinth-and-Fire-vs.-Water

Project Overview
Escape the Labyrinth - A maze navigation puzzle where you must find paths through regular and twisty mazes to collect three magical items (Spellbook, Potion, and Wand)
Fire vs. Water Game - A cellular automaton simulation where fire and water spread across a grid of grass cells

Components
1. Escape the Labyrinth
Navigate through mazes to collect all three magical items needed for escape.
Files:

EscapeTheLabyrinth.h - Main implementation with path validation
ExploreTheRegularLabyrinth.cpp - Test driver for regular maze
ExploreTheTwistyLabyrinth.cpp - Test driver for twisty maze
maze.h - Maze generation and cell structure
grid.h - Template-based 2D grid implementation using linked lists

Key Features:

Personalized mazes based on student NetID
Path validation using directional commands (N, S, E, W)
Two maze types: Regular and Twisty
Must collect Spellbook, Potion, and Wand to escape

Current Paths:

Regular Maze: EWSSESEENWNNE
Twisty Maze: EENWSWSWESW

2. Fire vs. Water Game
An interactive cellular automaton where fire and water compete on a grass field.
Files:

game.cpp - Main game loop and user interface
gameboard.h - Game board management and spread logic
boardcell.h - Cell type definitions (Fire, Water, Grass, Wall, Empty)

Cell Types:

* - Fire (spreads based on wind direction)
~ - Water (spreads randomly)
, - Grass (fuel for fire)
x - Wall (immovable barrier)
  - Empty space

Game Mechanics:

Fire spreads once per round based on wind direction
Water spreads multiple times per round (configurable)
Fire consumes grass, water extinguishes fire
Wind directions: q/w/e/a/s/d/z/x/c (8 directions + stay)

Win Conditions:

Water wins if all fire is extinguished
Fire wins if all grass is consumed

Building the Project
Use the provided Makefile to compile the project:
bash# Build everything
make

# Build specific targets
make game           # Fire vs. Water game
make regular        # Regular labyrinth explorer
make twisty         # Twisty labyrinth explorer

# Clean build artifacts
make clean
Running the Programs
Escape the Labyrinth
bash# Run regular maze
./regular

# Run twisty maze
./twisty
Important: Before running:

Fire vs. Water Game
bash./game
Game Setup:

Rows: 5-30
Columns: 5-80
Initial Fire cells: 1-20
Initial Water cells: 1-40
Water spread repetitions: 1-10
Random seed: -1 for time-based, or specific number for reproducibility

Controls:

Wind directions:
q - Northwest
w - North
e - Northeast
a - West
s - Stay/No wind
d - East
z - Southwest
x - South
c - Southeast


k - Quit game

Data Structures
Grid Template Class

Custom 2D grid implementation using linked lists
Each row is a separate linked list
Supports dynamic sizing and jagged grids
Template-based for type flexibility

BoardCell Hierarchy
Abstract base class with virtual methods:

Fire - Wind-directed spreading
Water - Random spreading
Grass - Passive fuel
Wall - Blocking cells
Empty - Void space

MazeCell Structure

Connected graph of cells
Each cell has north, south, east, west pointers
Optional items: Spellbook, Potion, Wand

Implementation Details
Path Validation Algorithm
cppbool isPathToFreedom(MazeCell *start, const string& moves)

Validates each move is legal (N/S/E/W)
Tracks collection of all three items
Ensures no nullptr traversals
Returns true only if all items collected

Spreading Algorithms
Fire Spreading:

Deterministic based on wind direction
Spreads to adjacent cell in wind direction
Consumes grass cells
Blocked by walls and water

Water Spreading:
Random offset generation (-1, 0, or 1 in each direction)
Can move diagonally
Extinguishes fire cells
Respects grid boundaries


File Structure
boardcell.h              # Cell type definitions
gameboard.h              # Game board management
game.cpp                 # Fire vs. Water main program
EscapeTheLabyrinth.h     # Maze escape logic
ExploreTheRegularLabyrinth.cpp
ExploreTheTwistyLabyrinth.cpp
maze.h                   # Maze generation
grid.h                   # Grid template class
hashcode.h               # Hash function utilities
makefile                 # Build configuration

Maze Solving:
Use breakpoint debugging to explore maze structure
Map out item locations before planning path
Test paths incrementally
Remember: changing NetID changes your maze!

Fire vs. Water Game:
Start with balanced fire/water ratios
Use strategic wind directions to control fire
Water spread repetitions greatly affect game balance
Experiment with different seeds for varied gameplay

