#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

const int GRID_SIZE = 5;
const char WATER = '~';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

typedef std::vector<std::vector<char>> Grid;

void initializeGrid(Grid& grid) {
    grid = Grid(GRID_SIZE, std::vector<char>(GRID_SIZE, WATER));
}

void placeShips(Grid& grid, int shipCount) {
    std::srand(std::time(0));
    int placed = 0;
    while (placed < shipCount) {
        int x = std::rand() % GRID_SIZE;
        int y = std::rand() % GRID_SIZE;
        if (grid[x][y] == WATER) {
            grid[x][y] = SHIP;
            placed++;
        }
    }
}

void displayGrid(const Grid& grid, bool revealShips = false) {
    std::cout << "  0 1 2 3 4" << std::endl;
    for (int i = 0; i < GRID_SIZE; i++) {
        std::cout << i << " ";
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == SHIP && !revealShips) {
                std::cout << WATER << " ";
            }
            else {
                std::cout << grid[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool takeShot(Grid& grid, int x, int y) {
    if (grid[x][y] == SHIP) {
        grid[x][y] = HIT;
        std::cout << "Hit!" << std::endl;
        return true;
    }
    else if (grid[x][y] == WATER) {
        grid[x][y] = MISS;
        std::cout << "Miss!" << std::endl;
    }
    else {
        std::cout << "Already fired there!" << std::endl;
    }
    return false;
}

bool allShipsSunk(const Grid& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == SHIP) return false;
        }
    }
    return true;
}

int main() {
    Grid playerGrid, computerGrid;
    initializeGrid(playerGrid);
    initializeGrid(computerGrid);

    placeShips(computerGrid, 3);
    placeShips(playerGrid, 3);

    std::cout << "Welcome to Battleship!" << std::endl;

    while (true) {
        int x, y;
        std::cout << "Your turn! Enter coordinates (row and column): ";
        std::cin >> x >> y;

        if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
            std::cout << "Invalid coordinates! Try again." << std::endl;
            continue;
        }

        takeShot(computerGrid, x, y);
        displayGrid(computerGrid);

        if (allShipsSunk(computerGrid)) {
            std::cout << "Congratulations! You sank all enemy ships!" << std::endl;
            break;
        }

        x = std::rand() % GRID_SIZE;
        y = std::rand() % GRID_SIZE;
        std::cout << "Computer's turn: " << x << " " << y << std::endl;
        takeShot(playerGrid, x, y);
        displayGrid(playerGrid, true);

        if (allShipsSunk(playerGrid)) {
            std::cout << "Game over! The computer sank all your ships." << std::endl;
            break;
        }
    }
    return 0;
}